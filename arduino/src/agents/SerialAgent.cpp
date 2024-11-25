#include "SerialAgent.h"

void SerialAgent::updateWasteLevel(int percentageLevel)
{
    String message = "{\"wasteLevel\":" + String(percentageLevel) + "}";
    Serial.print(message);
}
void SerialAgent::updateTemperature(int temperature)
{
    String message = "{\"temperature\":" + String(temperature) + "}";
    Serial.print(message);
}
bool SerialAgent::emptyContainer()
{
    return false;
}
bool SerialAgent::fixTemperature()
{
    return false;
}