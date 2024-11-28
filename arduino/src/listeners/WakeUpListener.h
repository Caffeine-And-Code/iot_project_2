#ifndef __WAKE_UP_LISTENER__
#define __WAKE_UP_LISTENER__
#include "Listener.h"
#include "AppController.h"
#include "Controller.h"

class WakeUpListener : public Listener
{
    void execute(Event *event, Controller *controller)
    {
        auto *appController = static_cast<AppController *>(controller);
        if (appController->stateMachineTask->getCurrentState() == Sleep)
        {
            appController->stateMachineTask->changeState(Available);
        }
    }
};

#endif