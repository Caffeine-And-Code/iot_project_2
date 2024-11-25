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

    String getEventName()
    {
        return "WasteUpdate";
    }
};

#endif