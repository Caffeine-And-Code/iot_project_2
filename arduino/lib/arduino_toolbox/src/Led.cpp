#include "Led.h"
#include "Arduino.h"

Led::Led(int pin) : MonoPin(pin)
{
    pinMode(this->pin, OUTPUT);
}

void Led::switchOn()
{
    digitalWrite(this->pin, HIGH);
}

void Led::switchOff()
{
    digitalWrite(this->pin, LOW);
}