#include "strategy.h"

Strategy::Strategy(Motor& motor) : motor(motor) {}

void Strategy::searchBasic()
{
    motor.drive(-150, 150);
}

void Strategy::searchAggressive()
{
    static uint32_t timer =
        millis();

    static bool forward =
        true;

    if (millis() - timer > 500)
    {
        timer = millis();
        forward = !forward;
    }

    if (forward)
    {
        motor.drive(180, 180);
    }
    else
    {
        motor.drive(-150, 150);
    }
}

// strategy.cpp

void Strategy::searchSweep()
{
    motor.drive(150, 150);
}


void Strategy::attackTracking(Direction target, uint16_t distance)
{
    if (distance > 300)
    {
        return;
    }

    switch(target)
    {
        case FRONT_DIR:
            motor.drive(255, 255);
            break;

        case LEFT_DIR:
            motor.drive(180, 255);
            break;

        case RIGHT_DIR:
            motor.drive(255, 180);
            break;

        default:
            break;
    }
}

void Strategy::attackAggressive(Direction target, uint16_t distance)
{
    switch(target)
    {
        case FRONT_DIR:
            motor.drive(255, 255);
            break;

        case LEFT_DIR:
            motor.drive(220, 255);
            break;

        case RIGHT_DIR:
            motor.drive(255, 220);
            break;

        default:
            break;
    }
}