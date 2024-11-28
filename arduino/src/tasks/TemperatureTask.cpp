#include "TemperatureTask.h"

TemperatureTask::TemperatureTask(AppController *controller) : controller(controller) {}

void TemperatureTask::tick()
{
    auto appController = static_cast<AppController *>(this->controller);
    if (appController->stateMachineTask->getCurrentState() == MaxTemperature)
    {
        return;
    }
    
    if (appController->temperature->getTemperature() < MAX_TEMP)
    {
        this->initialMillisecOverTemperature = millis();
    }

    if (this->initialMillisecOverTemperature + (MAX_TEMP_TIME_SECONDS * 1000) <= millis())
    {
        appController->stateMachineTask->changeState(MaxTemperature);
    }
}

void TemperatureTask::reset()
{
    this->initialMillisecOverTemperature = millis();
}