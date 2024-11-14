#ifndef __EVENT__
#define __EVENT__
#include "Arduino.h"

class Event
{
protected:
public:
    virtual ~Event() = default;
    virtual String getEventName() = 0;
    bool isEvent(String name);
};

#endif