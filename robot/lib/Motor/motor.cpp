#include "motor.h"

void Motor::begin()
{
    pinMode(MOTOR_STBY_PIN, OUTPUT);

    pinMode(LEFT_IN1_PIN, OUTPUT);
    pinMode(LEFT_IN2_PIN, OUTPUT);
    pinMode(LEFT_PWM_PIN, OUTPUT);

    pinMode(RIGHT_IN1_PIN, OUTPUT);
    //pinMode(RIGHT_IN2_PIN, OUTPUT);
    pinMode(RIGHT_PWM_PIN, OUTPUT);

    analogWriteFrequency(MOTOR_PWM_FREQUENCY);
    digitalWrite(MOTOR_STBY_PIN,HIGH);

    stop();
}

void Motor::drive(int16_t leftSpeed, int16_t rightSpeed)
{
    setMotor(LEFT_PWM_PIN, LEFT_IN1_PIN, LEFT_IN2_PIN, leftSpeed);
    //setMotor(RIGHT_PWM_PIN, RIGHT_IN1_PIN, RIGHT_IN2_PIN, rightSpeed);
}

void Motor::stop()
{
    analogWrite(LEFT_PWM_PIN, 0);
    analogWrite(RIGHT_PWM_PIN, 0);
}

void Motor::setMotor(   uint8_t pwmPin,
                        uint8_t in1Pin,
                        uint8_t in2Pin,
                        int16_t speed
)
{
    speed = constrain(speed, -MOTOR_MAX_PWM, MOTOR_MAX_PWM);

    if (speed > 0)
    {
        digitalWrite(in1Pin, HIGH);
        digitalWrite(in2Pin, LOW);
        analogWrite(pwmPin, speed);
    }
    else if (speed < 0)
    {
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, HIGH);
        analogWrite(pwmPin, -speed);
    }
    else
    {
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, LOW);
        analogWrite(pwmPin, 0);
    }
}