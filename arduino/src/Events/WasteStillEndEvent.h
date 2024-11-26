#ifndef __WASTE_STILL_END_EVENT__
#define __WASTE_STILL_END_EVENT__
#include "Event.h"

class WasteStillEndEvent : public Event
{
public:
    static const short EventID = 12;
    short getEventID() override
    {
        return this->EventID;
    }
};

#endif