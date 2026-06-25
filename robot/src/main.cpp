/*
Notes:
1. Comment semua kode debugging kalau mau jalanin robot
2. kalau mau debugging comment semua kode utama jalanin robot
*/

#include <Arduino.h>

#include "stateMachine.h"

// ===========================================
// Debugging code, comment kalau ga dipake
// ===========================================

// #include "debug.h" // pakai cuma pas debugging
// #include "motor.h" // pakai cuma pas debugging motor
// #include "config.h" //pakai cuma pas debugging ir
// #include "tof.h" // pakai cuma pas debugging tof

//===============================================

bool robotRun = false;
static bool lastRobotRun = false;
Robot robot;

// ===========================================
// Debugging code, comment kalau ga dipake
// ===========================================

// Motor motor; // motor
// TOF tof; // tof

// ============================================

void setup()
{
    Serial2.begin(115200);

    robotRun = false;
    lastRobotRun = false;

    robot.begin();
    robot.stop();

    // ===========================================
    // Debugging code, comment kalau ga dipake
    // ===========================================
    // Serial.begin(115200);

    // motor.begin(); // debug motor

    // // debug ir
    // pinMode(IR_FRONT_PIN, INPUT_PULLUP);
    // pinMode(IR_REAR_PIN, INPUT_PULLUP);
    
    // tof.begin(); // debug tof

    // ============================================
}

void loop()
{
    if (Serial2.available() > 0 )
    {
        char dataMasuk = Serial2.read();
        if (dataMasuk == '1')
        {
            robotRun = true;
        } else if (dataMasuk == '0') {
            robotRun = false;
        }
    }

    if(robotRun)
    {
        robot.update();
    }
    else
    {
        if(lastRobotRun)
        {
            robot.stop();
        }
    }
    lastRobotRun = robotRun;

    // ===========================================
    // Debugging code, comment kalau ga dipake
    // ===========================================

    // Debug::motor(motor); // debug motor
    
    // Debug::ir(); // debug ir

    // // debug tof
    // tof.update();
    // Debug::tof(tof);

    // ===========================================
}