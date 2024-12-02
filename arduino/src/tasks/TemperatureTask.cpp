#include "TemperatureTask.h"

TemperatureTask::TemperatureTask(AppController *controller) : controller(controller) {}

void TemperatureTask::tick()
{
    auto appController = static_cast<AppController *>(this->controller);
    if (appController->stateMachineTask->getCurrentState() == MaxTemperature)
    {
        return;
    }
    
    auto temperature = appController->temperature->getTemperature();
    if (temperature < MAX_TEMP)
    {
        this->initialMillisecOverTemperature = millis();
        this->temp_capper = 0;
    }
    else if (temperature - this->temp_capper < MAX_TEMP)
    {
        this->initialMillisecOverTemperature = millis();
        temperature -= this->temp_capper;
    }

    if (this->initialMillisecOverTemperature + (MAX_TEMP_TIME_SECONDS * 1000) <= millis())
    {
        appController->stateMachineTask->changeState(MaxTemperature);
        appController->serial->temperatureError();
    }

    appController->serial->updateTemperature(temperature);
}

void TemperatureTask::reset()
{
    auto appController = static_cast<AppController *>(this->controller);
    this->temp_capper = (appController->temperature->getTemperature() - MAX_TEMP) + 3;

    this->initialMillisecOverTemperature = millis();
}