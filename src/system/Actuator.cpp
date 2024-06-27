#include "Actuator.h"

Actuator::Actuator(LoadCell_Interface &lc, GateInterface &gate, ThrowerInterface &thrower) : _lc(lc), _gate(gate), _thrower(thrower)
{
}

bool Actuator::processCommand(FeedingMode &fm, FeedingState &fs)
{
    log_d("Received command");
    bool inProcess = handleFeedingMode(fm);

    log_d("inProcess = %s", inProcess ? "true" : "false");
    fs = inProcess ? FeedingState::IDLE : FeedingState::FAILED;

    if (currentCycle >= cycleCount)
    {
        resetCycle();
        _gate.open(5);
        _thrower.stop();
        fs = FeedingState::SUCCESS;
    }

    return true;
}

bool Actuator::handleFeedingMode(FeedingMode fm)
{
    switch (fm)
    {
    case FeedingMode::LOW_DOSE:
        gatePosition = 32; // Percent open for low dose
        cycleCount = lowDuration / period * 2 + 2;
        logDuration(fm, lowDuration);
        break;
    case FeedingMode::HIGH_DOSE:
        gatePosition = 35; // Percent open for high dose
        cycleCount = highDuration / period * 2 + 2;
        logDuration(fm, highDuration);
        break;
    }

    static bool cycleLapsed = false;

    // Perform the action based on the current state
    if (gateState == 0)
    {
        log_d("Gate open");
        _gate.open(gatePosition);
        gateState = 1; // Move to the next state
        cycleLapsed = false;
    }
    else if (gateState == 1)
    {
        log_d("Gate close");
        _gate.open(5); // Close the gate
        gateState = 0; // Move back to the initial state
        cycleLapsed = true;
    }

    log_d("Cycle count = %d", cycleCount);
    log_d("current cycle = %d", currentCycle);

    if (!isDispensing())
    {
        return false;
    }

    if (cycleLapsed)
        currentCycle++; // Increment the cycle count
    log_i("Throwing feed");
    _thrower.run();

    return true;
}

void Actuator::resetCycle()
{
    currentCycle = 0;
    gateState = 0;
}

void Actuator::logDuration(FeedingMode fm, int duration)
{
    int durationInMinutes = duration / 60;
    if (fm == LOW_DOSE)
    {
        log_i("Feed with low amount takes duration for %d minutes", durationInMinutes);
    }
    else if (fm == HIGH_DOSE)
    {
        log_i("Feed with maximum amount takes duration for %d minutes", durationInMinutes);
    }
}

bool Actuator::isDispensing()
{
    return _lc.getLoad() < 4200;
}