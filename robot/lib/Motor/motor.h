#pragma once

#include <Arduino.h>
#include "config.h"

class Motor
{
public:
    void begin();
    void drive(int16_t leftSpeed, int16_t rightSpeed);
    void stop();

private:
    void setMotor(
        uint8_t pwmPin,
        uint8_t in1Pin,
        uint8_t in2Pin,
        int16_t speed
    );
};