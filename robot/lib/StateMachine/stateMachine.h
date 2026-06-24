#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "tof.h"
#include "motor.h"
#include "strategy.h"
#include "robotTypes.h"

class Robot
{
public:
    void begin();
    void update();

private:
    TOF tof;
    Motor motor;
    Strategy strategy{motor};

    RobotState state = SEARCH;

    Direction lastSeenDirection = NONE;
    unsigned long lastSeenTime = 0;

    void updateState();

    EdgeDirection getEdgeDirection();
    EdgeDirection edgeDirection = NO_EDGE;

    void search();
    void attack();
    void escape();

    StrategyID currentStrategy = STRATEGY_1;

    void readStrategy();

    Direction getTargetDirection();
    uint16_t getNearestDistance();
    bool hasRecentTarget();

    EscapeState escapeState = ESCAPE_BACK;
    unsigned long escapeTimer = 0;
    bool enteringEscape = false;

    // Simulation
    uint16_t simulatedDistance = 0;
    EdgeDirection simulatedEdge = NO_EDGE;
    void handleSimulation();
};

#endif