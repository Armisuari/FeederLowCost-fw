#pragma once

#include <Arduino.h>
#include <interface/ThrowerInterface.h>

class Thrower_relay : public ThrowerInterface
{
    public:
        Thrower_relay(uint8_t pin = 23, uint8_t indicator = 2);
        bool init();
        bool run();
        bool stop();

    private:
        void _actuate(uint8_t state);

        uint8_t _pin;
        uint8_t _indicator;
};