#pragma once

#include <Arduino.h>
#include <ESP32Servo.h>

#include <interface/GateInterface.h>

class Gate_servo : public GateInterface
{
public:
    explicit Gate_servo(int pin = 5) noexcept;
    bool init() noexcept;
    bool open(int percent) noexcept;

private:
    static int percentToDegree(int percent) noexcept;

    Servo servo;
    const int _pin;
};