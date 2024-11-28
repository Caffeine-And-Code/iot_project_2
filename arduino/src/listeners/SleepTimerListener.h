#ifndef __SLEEP_TIMER_LISTENER__
#define __SLEEP_TIMER_LISTENER__
#include "Listener.h"
#include "AppController.h"
#include "Controller.h"

class SleepTimerListener : public Listener
{
    void execute(Event *event, Controller *controller)
    {
        auto *appController = static_cast<AppController *>(controller);
        appController->stateMachineTask->changeState(Sleep);
    }
};

#endif