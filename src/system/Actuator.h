#pragma once

#include <Arduino.h>
#include <interface/GateInterface.h>
#include <interface/ThrowerInterface.h>
#include <string>

typedef enum
{
    MINIMUM,
    MEDIUM,
    MAXIMUM
}FeedingMode;

class Actuator
{
    public:
        Actuator(GateInterface &gate, ThrowerInterface &thrower);
        bool processCommand(FeedingMode &fm);

    private:
        GateInterface &_gate;
        ThrowerInterface &_thrower;
};