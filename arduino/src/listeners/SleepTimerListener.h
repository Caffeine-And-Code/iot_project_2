#ifndef __SLEEP_TIMER_LISTENER__
#define __SLEEP_TIMER_LISTENER__
#include "Listener.h"
#include "AppController.h"

class SleepTimerListener : Listener
{
    void execute(Event *event, AppController *controller);
};

#endif