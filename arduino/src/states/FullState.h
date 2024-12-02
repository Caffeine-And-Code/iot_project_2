#ifndef __FULL_STATE__
#define __FULL_STATE__
#include "components/StateMachine/State.h"
#include "AppController.h"

class FullState : public State
{
private:
    AppController *controller;

public:
    FullState(AppController *controller) : controller(controller) {}
    void run() override
    {
        if (controller->serial->emptyContainer())
        {
            controller->door->reverseOpen();
            delay(T3);
            Serial.print(String(0) + "W\n");
            controller->stateMachineTask->changeState(Available);
        }
    }
};

#endif