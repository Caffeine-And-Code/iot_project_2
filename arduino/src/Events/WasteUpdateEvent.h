#ifndef __WASTE_UPDATE_EVENT__
#define __WASTE_UPDATE_EVENT__
#include "Event.h"

class WasteUpdateEvent : public Event
{
private:
    int percentage;

public:
    WasteUpdateEvent(int percentage) : percentage(percentage) {}

    int getPercentage()
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