#ifndef __SLEEP_TIMER_EVENT__
#define __SLEEP_TIMER_EVENT__
#include "Event.h"

class SleepTimerEvent : public Event
{
    String getEventName()
    {
        return "SleepTimerEvent";
    }
};

#endif