#include "SerialAgent.h"
#include "config/Config.h"

void SerialAgent::updateWasteLevel(short percentageLevel)
{
    Serial.print(String(percentageLevel) + "W\n");
}
void SerialAgent::updateTemperature(short temperature)
{
    Serial.print(String(temperature) + "T\n");
}

void SerialAgent::wasteError()
{
    Serial.print("EW\n");
}

void SerialAgent::temperatureError()
{
    Serial.print("ET\n");
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