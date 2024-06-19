#pragma once

#include <Arduino.h>

#include <interface/LoadCell_Interface.h>
#include <interface/GateInterface.h>
#include <interface/ThrowerInterface.h>

#include <system/Actuator.h>

class FeederApplication
{
public:
    FeederApplication(LoadCell_Interface &lc, GateInterface &gate, ThrowerInterface &thrower);
    bool init();
    bool measureLoad();
    bool feed(bool &state, FeedingMode fm);

    bool throwerTest(bool state);

private:
    LoadCell_Interface &_lc;
    GateInterface &_gate;
    ThrowerInterface &_thrower;

    const int triggOut = 5;

public:
    Actuator _act{_lc, _gate, _thrower};
};