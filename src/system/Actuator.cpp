#include "Actuator.h"

Actuator::Actuator(GateInterface &gate, ThrowerInterface &thrower) : _gate(gate), _thrower(thrower)
{
}

bool Actuator::processCommand(FeedingMode &fm)
{


    return true;
}