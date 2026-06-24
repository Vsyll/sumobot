#include <Arduino.h>

#include "stateMachine.h"

bool robotRun = false;
static bool lastRobotRun = false;
Robot robot;

void setup()
{
    Serial.begin(115200);
    Serial2.begin(115200);
    
    robotRun = false;
    lastRobotRun = false;

    robot.begin();
    robot.stop();
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
}