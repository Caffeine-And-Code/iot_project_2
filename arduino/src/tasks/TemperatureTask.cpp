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
    this->initialMillisecOverTemperature = millis();
}