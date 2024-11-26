#include "TemperatureAgent.h"
#include "config/Config.h"

void TemperatureAgent::update()
{
    auto appController = static_cast<AppController *>(this->controller);
    if (appController->temperature->getTemperature() < MAX_TEMP)
    {
        this->initialMillisecOverTemperature = millis();
    }

    if (this->initialMillisecOverTemperature + MAX_TEMP_TIME_SECONDS * 1000 <= millis())
    {
        appController->changeState(MaxTemperature);
    }
}

void TemperatureAgent::reset()
{
    this->initialMillisecOverTemperature = millis();
}