#ifndef __WASTE_STILL_END_EVENT__
#define __WASTE_STILL_END_EVENT__
#include "Event.h"

class WasteStillEndEvent : public Event
{
    String getEventName()
    {
        return "WasteStillEndEvent";
    }
};

#endif