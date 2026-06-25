#include "debug.h"
#include "config.h"

namespace Debug
{

void motor(Motor& motor)
{
    if(!Serial.available())
        return;

    char cmd = Serial.read();

    switch(cmd)
    {
        case 'w':
            Serial.println("Forward");
            motor.drive(200,200);
            break;

        case 's':
            Serial.println("Backward");
            motor.drive(-200,-200);
            break;

        case 'a':
            Serial.println("Left");
            motor.drive(-200,200);
            break;

        case 'd':
            Serial.println("Right");
            motor.drive(200,-200);
            break;

        case 'x':
            Serial.println("Stop");
            motor.drive(0,0);
            break;
    }
}

void ir()
{
    Serial.print("Front=");
    Serial.print(digitalRead(IR_FRONT_PIN));

    Serial.print(" Rear=");
    Serial.println(digitalRead(IR_REAR_PIN));

    delay(100);
}

void tof(TOF& tof)
{
    static uint32_t timer = millis();

    if(millis() - timer < 100)
        return;

    timer = millis();

    Serial.print("F1=");
    Serial.print(tof.getDistance(FRONT1));

    Serial.print(" F2=");
    Serial.print(tof.getDistance(FRONT2));

    Serial.print(" R=");
    Serial.print(tof.getDistance(RIGHT));

    Serial.print(" L=");
    Serial.println(tof.getDistance(LEFT));
}

}