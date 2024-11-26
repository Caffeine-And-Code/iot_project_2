#ifndef __WAKE_UP_EVENT__
#define __WAKE_UP_EVENT__
#include "Event.h"

class WakeUpEvent : public Event
{
public:
    static const short EventID = 11;
    short getEventID() override
    {
        return this->EventID;
    }
};

#endif