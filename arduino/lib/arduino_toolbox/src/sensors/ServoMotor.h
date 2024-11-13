#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

#define SERVO_MOTOR_OPEN 1023
#define SERVO_MOTOR_CLOSE 0

#include "../MonoPin.h"
#include <Servo.h>

class ServoMotor : public MonoPin
{
protected:
    Servo servo;

public:
    ServoMotor(int pin);
    void move(int value);
    void open();
    void close();
};

#endif