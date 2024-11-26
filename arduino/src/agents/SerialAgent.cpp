#include "SerialAgent.h"
#include "config/Config.h"

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

void SerialAgent::wasteError()
{
    String message = "EW\n";
    Serial.print(message);
}

void SerialAgent::temperatureError()
{
    String message = "ET\n";
    Serial.print(message);
}

bool SerialAgent::emptyContainer()
{
#ifndef DEBUG_APP
    if (Serial.available() > 0)
    {
        int msg = Serial.parseInt();
        return msg == 1;
    }
    return false;
#else
    return true;
#endif
}
bool SerialAgent::fixTemperature()
{
#ifndef DEBUG_APP
    if (Serial.available() > 0)
    {
        int msg = Serial.parseInt();
        return msg == 2;
    }
    return false;
#else
    return true;
#endif
}