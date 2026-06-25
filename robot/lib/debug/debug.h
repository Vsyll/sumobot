#pragma once

#include "tof.h"
#include "motor.h"

namespace Debug
{
    void motor(Motor& motor);
    void tof(TOF& tof);
    void ir();
}