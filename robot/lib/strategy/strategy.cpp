#include "strategy.h"

Strategy::Strategy(Motor& motor) : motor(motor) {}

void Strategy::searchBasic()
{
    motor.drive(-150, 150);
}

void Strategy::searchPatrol()
{
    static uint32_t timer = 0;
    if(timer == 0)
    {
        timer = millis();
    }

    static bool leftSweep = true;

    if (millis() - timer > 800)
    {
        timer = millis();
        leftSweep = !leftSweep;
    }

    if (leftSweep)
    {
        motor.drive(180, 255);
    }
    else
    {
        motor.drive(255, 180);
    }
}

void Strategy::searchAggressive()
{
    static uint32_t timer = 0;
    if(timer == 0)
    {
        timer = millis();
    }

    static bool forward = true;

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


void Strategy::searchSweep()
{
    static uint32_t timer = 0;
    if(timer == 0)
    {
        timer = millis();
    }

    static bool sweepForward = true;

    if (millis() - timer > 2500)
    {
        timer = millis();
        sweepForward = !sweepForward;
    }

    if (sweepForward)
    {
        motor.drive(220,255);
    }
    else
    {
        motor.drive(255,220);
    }
}


void Strategy::attackTracking(Direction target, uint16_t distance)
{
    int fast = 255;
    int slow = 180;

    if (distance > 250)
    {
        fast = 220;
        slow = 150;
    }

    switch(target)
    {
        case FRONT_DIR:
            motor.drive(fast, fast);
            break;

        case LEFT_DIR:
            motor.drive(slow, fast);
            break;

        case RIGHT_DIR:
            motor.drive(fast, slow);
            break;
         default:
            motor.drive(-100,100);
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
            motor.drive(50, 255);
            break;

        case RIGHT_DIR:
            motor.drive(255, 50);
            break;

        default:
            motor.drive(-100,100);
            break;
    }
}