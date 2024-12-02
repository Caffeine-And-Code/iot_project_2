#include "SerialAgent.h"
#include "config/Config.h"

void SerialAgent::updateWasteLevel(short percentageLevel)
{
    Serial.print(String(percentageLevel));
    Serial.println("W");
}
void SerialAgent::updateTemperature(short temperature)
{
    Serial.print(temperature);
    Serial.println("T");
}

void SerialAgent::wasteError()
{
    Serial.println("EW");
}

void SerialAgent::temperatureError()
{
    Serial.println("ET");
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