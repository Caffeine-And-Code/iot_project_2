#ifndef __MAX_TEMPERATURE_STATE__
#define __MAX_TEMPERATURE_STATE__
#include "components/StateMachine/State.h"
#include "AppController.h"

class MaxTemperatureState : public State
{
private:
    AppController *controller;

public:
    MaxTemperatureState(AppController *controller) : controller(controller) {}
    void run() override
    {
        if (controller->serial->fixTemperature())
        {
            controller->stateMachineTask->changeState(Available);
            controller->temperatureTask->reset();
        }
    }
};

#endif