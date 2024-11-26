#ifndef __WASTE_UPDATE_EVENT__
#define __WASTE_UPDATE_EVENT__
#include "Event.h"

class WasteUpdateEvent : public Event
{
private:
    short percentage;

public:
    WasteUpdateEvent(short percentage) : percentage(percentage) {}

    short getPercentage()
    {
        return percentage;
    }

    static const short EventID = 13;
    short getEventID() override
    {
        return this->EventID;
    }
};

#endif