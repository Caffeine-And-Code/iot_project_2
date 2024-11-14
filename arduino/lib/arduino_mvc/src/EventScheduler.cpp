#include "EventScheduler.h"

EventScheduler::EventScheduler(Controller *controller)
{
    this->controller = controller;
}
void EventScheduler::addSchedule(String eventName, Listener *listener)
{
    if (currentIndex < MAX_SCHEDULER)
    {
        EventAssociation *association = new EventAssociation(eventName, listener);
        this->scheduler[currentIndex++] = association;
    }
}

void EventScheduler::trigger(Event *event)
{
    for (int i = 0; i < currentIndex; i++)
    {
        if (event->isEvent(this->scheduler[i]->eventName))
        {
            this->scheduler[i]->listener->execute(event, this->controller);
        }
    }
}