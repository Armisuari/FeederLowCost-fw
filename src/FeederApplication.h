#pragma once

#include <memory>
#include <atomic>
#include <thread>
#include <chrono>

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

private:
    LoadCell_Interface &_lc;
    GateInterface &_gate;
    ThrowerInterface &_thrower;

    void taskSensor();

    std::atomic<bool> _running{true};
    std::thread _sensorThread;

    static constexpr int triggOut = 5;

public:
    Actuator _act{_lc, _gate, _thrower};
};