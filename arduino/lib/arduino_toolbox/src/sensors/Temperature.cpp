#include "Temperature.h"
#include "Arduino.h"

Temperature::Temperature(int pin) : MonoPin(pin)
{
    pinMode(pin, INPUT);
}

int Temperature::getTemperature()
{
    return analogRead(this->pin) * TEMPERATURE_CONSTANT;
}

bool Temperature::hasChanged()
{
    int checkValue = this->lastValue;
    this->lastValue = this->getTemperature();
    return this->lastValue != checkValue;
}