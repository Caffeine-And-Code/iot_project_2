#ifndef __WAKE_UP_EVENT__
#define __WAKE_UP_EVENT__
#include "Event.h"

class WakeUpEvent : public Event
{
    String getEventName()
    {
        return "WakeUpEvent";
    }
};

#endif