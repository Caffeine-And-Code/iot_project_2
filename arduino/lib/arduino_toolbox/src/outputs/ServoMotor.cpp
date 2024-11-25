#include "ServoMotor.h"

ServoMotor::ServoMotor(int pin) : MonoPin(pin)
{
    this->servo.attach(this->pin);
}

void ServoMotor::move(int value)
{
    if (lastValue < 0 || lastValue != value)
    {
        lastValue = value;
        this->servo.write(value);
    }
}

void ServoMotor::open()
{
    this->move(SERVO_MOTOR_OPEN);
}

void ServoMotor::close()
{
    this->move(SERVO_MOTOR_CLOSE);
}