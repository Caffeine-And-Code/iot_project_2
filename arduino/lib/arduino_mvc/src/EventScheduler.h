#ifndef __EVENT_SCHEDULER__
#define __EVENT_SCHEDULER__
#define MAX_SCHEDULER 50
#include "Controller.h"
#include "EventAssociation.h"
#include "Listener.h"
class Controller;
class EventAssociation;
class Listener;
class EventScheduler
{
private:
    EventAssociation *scheduler[MAX_SCHEDULER];
    Controller *controller;
    int currentIndex = 0;

public:
    EventScheduler(Controller *controller);
    void addSchedule(String eventName, Listener *listener);
    void trigger(Event *event);
};

#endif