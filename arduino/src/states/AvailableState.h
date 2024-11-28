#ifndef __AVAILABLE_STATE__
#define __AVAILABLE_STATE__
#include "components/StateMachine/State.h"
#include "AppController.h"

class AvailableState : public State
{
private:
    AppController *controller;

public:
    AvailableState(AppController *controller) : controller(controller) {}
    void run() override
    {
        controller->sleepTimer->update();
        if (controller->btnOpen->isPressed())
        {
            controller->stateMachineTask->changeState(DoorOpen);
        }
        if (controller->peopleDetector->isPersonDetected())
        {
            controller->sleepTimer->restart();
        }
    }
};

#endif