#pragma once

#include <Arduino.h>
#include <interface/LoadCell_Interface.h>
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
        Actuator(LoadCell_Interface &lc, GateInterface &gate, ThrowerInterface &thrower);
        bool processCommand(FeedingMode &fm);

    private:
        bool handleFeedingMode(FeedingMode fm, float prevLoad);
        bool isDispensing(float prevLoad);

        LoadCell_Interface &_lc;
        GateInterface &_gate;
        ThrowerInterface &_thrower;
};