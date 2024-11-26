#ifndef __SLEEP_TIMER_EVENT__
#define __SLEEP_TIMER_EVENT__
#include "Event.h"

class SleepTimerEvent : public Event
{
public:
    static const short EventID = 10;
    short getEventID() override
    {
        return this->EventID;
    }
};

#endif