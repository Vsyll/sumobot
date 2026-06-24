#ifndef STRATEGY_H
#define STRATEGY_H

#include "motor.h"
#include "robotTypes.h"

class Strategy
{
public:

    Strategy(Motor& motor);

    // Search
    void searchBasic();
    void searchPatrol();
    void searchAggressive();
    void searchSweep();

    // Attack
    void attackTracking(Direction target, uint16_t distance);
    void attackAggressive(Direction target, uint16_t distance);

private:

    Motor& motor;
};

#endif