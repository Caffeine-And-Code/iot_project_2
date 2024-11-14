#ifndef __DOOR__
#define __DOOR__
#include "outputs/ServoMotor.h"

class Door : ServoMotor
{
public:
    Door(int pin) : ServoMotor(pin) {}

    void open()
    {
        this->move(SERVO_MOTOR_OPEN);
    }

    void close()
    {
        this->move(SERVO_MOTOR_OPEN / 2);
    }

    void reverseOpen()
    {
        this->move(SERVO_MOTOR_CLOSE);
    }
};

#endif