#include "UltrasoundProximity.h"
#include "Arduino.h"

UltrasoundProximity::UltrasoundProximity(int trigPin, int echoPint, Temperature *temperature) : DoublePin(trigPin, echoPint)
{
    pinMode(this->firstPin, OUTPUT);
    pinMode(this->secondPin, INPUT);
    this->temperatureSensor = temperature;
    this->useSensor = true;
}

UltrasoundProximity::UltrasoundProximity(int trigPin, int echoPint, int temperature) : DoublePin(trigPin, echoPint)
{
    pinMode(this->firstPin, OUTPUT);
    pinMode(this->secondPin, INPUT);
    this->temperature = temperature;
    this->useSensor = false;
}

int UltrasoundProximity::getDistance()
{
    digitalWrite(this->firstPin, LOW);
    delayMicroseconds(3);
    digitalWrite(this->firstPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(this->firstPin, LOW);

    int temperature = this->temperature;
    if (this->useSensor)
    {
        temperature = this->temperatureSensor->getTemperature();
    }

    float vs = 331.45 + 0.62 * temperature;
    float tUS = pulseIn(this->secondPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t * vs;

    return d * 100;
}

bool UltrasoundProximity::hasChanged()
{
    bool checkValue = this->lastValue;
    this->lastValue = this->getDistance();
    return this->lastValue != checkValue;
}
