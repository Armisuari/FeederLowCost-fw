#include "Gate_servo.h"

Gate_servo::Gate_servo(int pin) noexcept : _pin(pin)
{
}

bool Gate_servo::init() noexcept
{
    servo.setPeriodHertz(50);           // Standard 50hz servo
    servo.attach(_pin, 500, 2400);     // Attaches the servo on the pin to the servo object
                                        // using MG995 large servo min/max of 1000us and 2000us.
    return true;
}

bool Gate_servo::open(int percent) noexcept
{
    int degree = percentToDegree(percent);
    log_d("servo move to: %d", degree);
    servo.write(degree);
    return true;
}

int Gate_servo::percentToDegree(int percent) noexcept
{
    return map(percent, 0, 100, 35, 0);
}
