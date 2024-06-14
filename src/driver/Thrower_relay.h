#pragma once

#include <string>
#include <Arduino.h>

class Thrower_relay
{
    public:
        Thrower_relay(uint8_t pin = 23, uint8_t indicator = 2);
        bool init();
        bool on();
        bool off();
        bool onTillWait(uint16_t waitTimeInMilliseconds);

        std::string tag = "THROWER";

    private:
        void actuate(uint8_t state);

        uint8_t _pin;
        uint8_t _indicator;
};