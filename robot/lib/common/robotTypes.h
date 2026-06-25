#pragma once

enum RobotState
{
    SEARCH,
    ATTACK,
    ESCAPE
};

enum Direction
{
    NONE,
    LEFT_DIR,
    RIGHT_DIR,
    FRONT_DIR
};

enum EdgeDirection
{
    NO_EDGE,
    FRONT_EDGE,
    REAR_EDGE
};

enum EscapeState
{
    ESCAPE_BACK,
    ESCAPE_TURN
};