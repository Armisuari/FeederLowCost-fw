#include "Thrower_relay.h"

Thrower_relay::Thrower_relay(uint8_t pin, uint8_t indicator) : _pin(pin),
                                                               _indicator(indicator)
{
}

bool Thrower_relay::init()
{
    pinMode(_pin, OUTPUT);
    pinMode(_indicator, OUTPUT);
    return true;
}

bool Thrower_relay::on()
{
    actuate(HIGH);
    return true;
}

bool Thrower_relay::off()
{
    actuate(LOW);
    return true;
}

void Thrower_relay::actuate(uint8_t state)
{
    digitalWrite(_pin, state);
    digitalWrite(_indicator, state);
}