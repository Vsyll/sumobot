#include "stateMachine.h"

void Robot::begin()
{
    tof.begin();
    motor.begin();

    pinMode(IR_FRONT_LEFT_PIN, INPUT_PULLUP);
    pinMode(IR_FRONT_RIGHT_PIN, INPUT_PULLUP);
    pinMode(IR_REAR_PIN , INPUT_PULLUP);

    pinMode(DIP1_PIN, INPUT_PULLUP);
    pinMode(DIP2_PIN, INPUT_PULLUP);

    readStrategy();
}

void Robot::update()
{
    if (SIMULATION_MODE)
    {
        handleSimulation();
    }
    else
    {
        tof.update();
    }

    updateState();

    switch (state)
    {
        case SEARCH:
            search();
            break;

        case ATTACK:
            attack();
            break;

        case ESCAPE:
            escape();
            break;
    }
}

void Robot::updateState()
{
    EdgeDirection edge;
    uint16_t front1;
    uint16_t front2;

    if (SIMULATION_MODE)
    {
        edge = simulatedEdge;

        front1 = simulatedDistance;
        front2 = 0;
    }
    else
    {
        edge = getEdgeDirection();

        front1 = tof.getDistance(FRONT1);
        front2 = tof.getDistance(FRONT2);
    }

    // =========================
    // Edge Priority
    // =========================

    if (edge != NO_EDGE)
    {
        if (state != ESCAPE)
        {
            edgeDirection = edge;
            escapeState = ESCAPE_BACK;
            escapeTimer = millis();
        }
        state = ESCAPE;
        return;
    }

    // =========================
    // Last Seen Direction
    // =========================

    Direction target = getTargetDirection();

    if (target != NONE)
    {
        lastSeenDirection = target;
        lastSeenTime = millis();
    }

    // =========================
    // Attack Distance Check
    // =========================

    uint16_t nearest = getNearestDistance();
    if (nearest > 0 && nearest < ATTACK_DISTANCE)
    {
        state = ATTACK;
    }
    else
    {
        state = SEARCH;
    }
}

EdgeDirection Robot::getEdgeDirection()
{
    if (digitalRead(IR_FRONT_LEFT_PIN) == LOW)
    {
        return FRONT_LEFT_EDGE;
    }
    if (digitalRead(IR_FRONT_RIGHT_PIN) == LOW)
    {
        return FRONT_RIGHT_EDGE;
    }
    if (digitalRead(IR_REAR_PIN) == LOW)
    {
        return REAR_EDGE;
    }
    return NO_EDGE;
}


void Robot::search()
{
    if (hasRecentTarget())
    {
        switch(lastSeenDirection)
        {
            case LEFT_DIR:
                motor.drive(-150, 150);
                return;

            case RIGHT_DIR:
                motor.drive(150, -150);
                return;

            case FRONT_DIR:
                motor.drive(200, 200);
                return;

            default:
                break;
        }
    }

    switch(currentStrategy)
    {
        case STRATEGY_1:
            strategy.searchBasic();
            break;

        case STRATEGY_2:
            strategy.searchAggressive();
            break;

        case STRATEGY_3:
            strategy.searchSweep();
            break;

        case STRATEGY_4:
            strategy.searchAggressive();
            break;
    }
}


void Robot::attack()
{
    Direction target =
        getTargetDirection();

    uint16_t distance =
        getNearestDistance();

    switch(currentStrategy)
    {
        case STRATEGY_1:
            strategy.attackTracking(target, distance);
            break;

        case STRATEGY_2:
            strategy.attackTracking(target, distance);
            break;

        case STRATEGY_3:
            strategy.attackTracking(target, distance);
            break;

        case STRATEGY_4:
            strategy.attackAggressive(target, distance);
            break;
    }
}

void Robot::escape()
{
    switch (escapeState)
    {
        case ESCAPE_BACK:

            switch(edgeDirection)
            {
                case REAR_EDGE:
                    motor.drive(255, 255);
                    break;

                default:
                    motor.drive(-255, -255);
                    break;
            }

            if (millis() - escapeTimer > 300)
            {
                escapeState = ESCAPE_TURN;
                escapeTimer = millis();
            }
            break;

        case ESCAPE_TURN:

            switch(edgeDirection)
            {
                case FRONT_LEFT_EDGE: 
                    motor.drive(255, -255);
                    break;

                case FRONT_RIGHT_EDGE: 
                    motor.drive(-255, 255);
                    break;

                case REAR_EDGE:
                    motor.drive(255, -255);
                    break;

                default:
                    motor.drive(255, -255);
                    break;
            }

            if (millis() - escapeTimer > 250)
            {
                escapeState = ESCAPE_BACK;
                state = SEARCH;
            }
            break;
    }
}

void Robot::readStrategy()
{
    if constexpr (MANUAL_STRATEGY)
    {
        currentStrategy = TEST_STRATEGY;
        return;
    }

    
    uint8_t dip = (!digitalRead(DIP1_PIN) << 0) | (!digitalRead(DIP2_PIN) << 1);

    switch (dip)
    {
        case 0:
            currentStrategy = STRATEGY_1;
            break;

        case 1:
            currentStrategy = STRATEGY_2;
            break;

        case 2:
            currentStrategy = STRATEGY_3;
            break;

        case 3:
            currentStrategy = STRATEGY_4;
            break;
    }
}

Direction Robot::getTargetDirection()
{
    if (SIMULATION_MODE)
    {
        return simulatedDistance > 0 ? FRONT_DIR : NONE;
    }

    bool left =
        tof.getDistance(FRONT1) > 0;

    bool right =
        tof.getDistance(FRONT2) > 0;

    if (left && right)
        return FRONT_DIR;

    if (left)
        return LEFT_DIR;

    if (right)
        return RIGHT_DIR;

    return NONE;
}

uint16_t Robot::getNearestDistance()
{
    if (SIMULATION_MODE)
    {
        return simulatedDistance;
    }

    uint16_t front1 =
        tof.getDistance(FRONT1);

    uint16_t front2 =
        tof.getDistance(FRONT2);

    if (front1 == 0)
        return front2;

    if (front2 == 0)
        return front1;

    return min(front1, front2);
}

bool Robot::hasRecentTarget()
{
    return
        millis() - lastSeenTime <
        LAST_SEEN_TIMEOUT;
}


// Simulasi
void Robot::handleSimulation()
{
    if (!Serial.available())
        return;

    char cmd = Serial.read();

    switch(cmd)
    {
        case 'a':
            simulatedDistance = 300;
            Serial.println("Enemy");
            break;

        case 's':
            simulatedDistance = 0;
            Serial.println("Lost");
            break;

        case 'e':
            simulatedEdge = FRONT_LEFT_EDGE;
            Serial.println("Edge");
            break;

        case 'r':
            simulatedEdge = NO_EDGE;
            Serial.println("Reset");
            break;
    }
}