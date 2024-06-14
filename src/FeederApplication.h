#pragma once

#include <Arduino.h>

#include <driver/LoadCell_HX71708.h>
#include <driver/Thrower_relay.h>

#define DOUT 17
#define DSCK 16

class FeederApplication
{
    public :
        // FeederApplication();
        bool init();
        bool measureLoad();
        bool feeding(bool state);

    private:
        LoadCell_HX71708 _loadCell;
        Thrower_relay _thrower;
};