#include <Arduino.h>

#include "stateMachine.h"

const int remotePin = PA0;
Robot robot;

void setup()
{
    pinMode(remotePin, INPUT);
    Serial.begin(115200);

    robot.begin();
}

void loop()
{
    int statusRemote = digitalRead(remotePin);
    if (statusRemote == HIGH)
    {
        robot.update();
    }
}