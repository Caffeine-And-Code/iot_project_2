#include "Event.h"

bool Event::isEvent(String name)
{
    return this->getEventName().compareTo(name) == 0;
}