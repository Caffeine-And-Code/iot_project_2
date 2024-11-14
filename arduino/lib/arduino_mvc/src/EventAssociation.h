#ifndef __EVENT_ASSOCIATION__
#define __EVENT_ASSOCIATION__
#include "Event.h"
#include "Listener.h"
class Listener;

class EventAssociation
{
public:
    String eventName;
    Listener *listener;
    EventAssociation(String eventName, Listener *listener);
};

#endif