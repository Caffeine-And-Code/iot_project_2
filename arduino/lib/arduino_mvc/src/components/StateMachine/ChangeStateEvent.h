#ifndef __CHANGE_STATE_EVENT__
#define __CHANGE_STATE_EVENT__

#include "Event.h"

class ChangeStateEvent : public Event
{
protected:
    int lastState;
    int newState;

public:
    ChangeStateEvent(int lastState, int newState);

    String getEventName();
    int getLastState();
    int getNewState();
};

#endif