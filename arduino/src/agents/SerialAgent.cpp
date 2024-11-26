#include "SerialAgent.h"

void SerialAgent::updateWasteLevel(short percentageLevel)
{
    String message = String(percentageLevel) + "W\n";
    Serial.print(message);
}
void SerialAgent::updateTemperature(short temperature)
{
    String message = String(temperature) + "T\n";
    Serial.print(message);
}

bool SerialAgent::emptyContainer()
{
    if (Serial.available() > 0)
    {
        int msg = Serial.parseInt();
        return msg == 1;
    }
    return false;
}
bool SerialAgent::fixTemperature()
{
    if (Serial.available() > 0)
    {
        int msg = Serial.parseInt();
        return msg == 2;
    }
    return false;
}