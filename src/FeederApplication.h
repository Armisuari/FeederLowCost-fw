#pragma once

#include <Arduino.h>

#include <driver/LoadCell_HX71708.h>

#define DOUT 17
#define DSCK 16

class FeederApplication
{
    public :
        // FeederApplication();
        bool init();
        bool measureLoad();

    private:
        LoadCell_HX71708 _loadCell{DOUT, DSCK};
};