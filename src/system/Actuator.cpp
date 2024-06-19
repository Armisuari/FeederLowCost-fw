#include "Actuator.h"

Actuator::Actuator(LoadCell_Interface &lc, GateInterface &gate, ThrowerInterface &thrower) : _lc(lc), _gate(gate), _thrower(thrower)
{
}

bool Actuator::processCommand(FeedingMode &fm)
{
    float curLoad = _lc.readRaw();
    bool _res = handleFeedingMode(fm, curLoad);

    if (!_res)
    {
        log_e("failed to process feed command");
        return false;
    }

    return true;
}

bool Actuator::handleFeedingMode(FeedingMode fm, float prevLoad)
{
    int gatePosition;
    const char *logMessage;

    switch (fm)
    {
    case MINIMUM:
        gatePosition = 35;
        logMessage = "Feed with minimum amount";
        break;
    case MEDIUM:
        gatePosition = 75;
        logMessage = "Feed with medium amount";
        break;
    case MAXIMUM:
        gatePosition = 95;
        logMessage = "Feed with maximum amount";
        break;
    }

    log_d("%s", logMessage);
    _gate.open(gatePosition);
    delay(100);

    if (!isDispensing(prevLoad))
    {
        log_w("Thrower doesn't run");
        _thrower.stop();
        return false;
    }
    else
    {
        while (isDispensing(prevLoad))
        {
            log_i("Throwing feed");
            _thrower.run();
        }
    }

    log_i("feeding process done");
    _thrower.stop();

    return true;
}

bool Actuator::isDispensing(float prevLoad)
{
    delay(100);
    float curLoad = _lc.readRaw();
    // return curLoad > prevLoad;
    return curLoad > prevLoad + 10000.0;
}