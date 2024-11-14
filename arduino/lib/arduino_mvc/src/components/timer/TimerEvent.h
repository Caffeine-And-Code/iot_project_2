#ifndef __TIMER_EVENT__
#define __TIMER_EVENT__
#include "Event.h"
#include "Arduino.h"
#include "Timer.h"

class Timer;

class TimerEvent : public Event
{
private:
    Timer *timer;

public:
    Timer *getTimer()
    {
        return this->timer;
    }
    String getEventName()
    {
        return "TimerEvent";
    }
};

#endif