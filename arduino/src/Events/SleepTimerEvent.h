#ifndef __SLEEP_TIMER_EVENT__
#define __SLEEP_TIMER_EVENT__
#include "components/timer/TimerEvent.h"

class SleepTimerEvent : public TimerEvent
{
    String getEventName()
    {
        return "SleepTimerEvent";
    }
};

#endif