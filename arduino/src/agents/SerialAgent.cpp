#include "SerialAgent.h"

void SerialAgent::updateWasteLevel(int percentageLevel)
{
    String message = "{\"fluidLevel\":" + String(percentageLevel) + "}";
    Serial.print(message);
}
void SerialAgent::updateTemperature(int temperature)
{
    String message = "{\"temperature\":" + String(temperature) + "}";
    Serial.print(message);
}

bool SerialAgent::emptyContainer()
{
    if(Serial.available() > 0)
    {
        int msg = Serial.parseInt();
        return msg == 1;
    }
    return false;
}
bool SerialAgent::fixTemperature()
{
    if(Serial.available() > 0)
    {
        int msg = Serial.parseInt();
        return msg == 2;
    }
    return false;
}