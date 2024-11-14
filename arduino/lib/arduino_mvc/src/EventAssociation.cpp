#include "EventAssociation.h"

EventAssociation::EventAssociation(String eventName, Listener *listener)
{
    this->eventName = eventName;
    this->listener = listener;
}