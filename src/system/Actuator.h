#pragma once

#include <Arduino.h>
#include <interface/LoadCell_Interface.h>
#include <interface/GateInterface.h>
#include <interface/ThrowerInterface.h>
#include <string>

typedef enum
{
    LOW_DOSE,
    HIGH_DOSE
} FeedingMode;

typedef enum {
    IDLE,
    SUCCESS,
    FAILED
}FeedingState;

class Actuator
{
public:
    Actuator(LoadCell_Interface &lc, GateInterface &gate, ThrowerInterface &thrower);
    bool processCommand(FeedingMode &fm, FeedingState &fs);

private:
    bool handleFeedingMode(FeedingMode fm);
    void resetCycle();                              // Helper method to reset cycles
    void logDuration(FeedingMode fm, int duration); // Helper method for logging duration
    bool isDispensing();

    LoadCell_Interface &_lc;
    GateInterface &_gate;
    ThrowerInterface &_thrower;

    int targetFeed = 524; // gram
    int gatePosition = 5;                           // Initial gate position
    const int period = 2;                           // Intermittent period in seconds
    const int lowRate = 19;                         // Low feed rate in g/s
    const int highRate = 29;                        // High feed rate in g/s
    const int lowDuration = targetFeed / lowRate;   // Duration for low feed in seconds
    const int highDuration = targetFeed / highRate; // Duration for high feed in seconds
    int cycleCount = 0;                             // Count of completed cycles
    int currentCycle = 0;                           // Number of cycles required
    int gateState = 0;                              // 0 for closed, 1 for open
};