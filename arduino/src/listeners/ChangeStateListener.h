#ifndef __CHANGE_STATE_LISTENER__
#define __CHANGE_STATE_LISTENER__
#include "Listener.h"
#include "components/StateMachine/ChangeStateEvent.h"
#include "AppController.h"
#include "enums/States.h"
#include "components/timer/Timer.h"

class ChangeStateListener : Listener
{
    void execute(ChangeStateEvent event, AppController *controller)
    {
        if (event.getNewState() == Available)
        {
        }
    }
};

#endif