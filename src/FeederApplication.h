#pragma once

#include <Arduino.h>

#include <interface/GateInterface.h>
#include <interface/ThrowerInterface.h>

#include <driver/LoadCell_HX71708.h>

#include <system/Actuator.h>

class FeederApplication
{
    public :
        FeederApplication(GateInterface &gate, ThrowerInterface &thrower);
        bool init();
        bool measureLoad();
        bool feeding();

        bool throwerTest(bool state);
        // bool gateTest(uint16_t percent);

    private:
        GateInterface &_gate;
        ThrowerInterface &_thrower;

        LoadCell_HX71708 _loadCell;

    public:
        Actuator _act{_gate, _thrower};
};