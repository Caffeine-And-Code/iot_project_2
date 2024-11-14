#ifndef __CHANGE_STATE_LISTENER__
#define __CHANGE_STATE_LISTENER__
#include "Listener.h"
#include "components/StateMachine/ChangeStateEvent.h"
#include "components/timer/Timer.h"
#include "AppController.h"
#include "Event.h"
#include "Controller.h"

class ChangeStateListener : public Listener
{
public:
    void execute(Event *event, Controller *controller)
    {
        auto *realEvent = static_cast<ChangeStateEvent *>(event);
        auto *realController = static_cast<AppController *>(controller);
        if (realEvent->getNewState() == Available)
        {
            realController->sleepTimer->start();
        }
    }
};

#endif