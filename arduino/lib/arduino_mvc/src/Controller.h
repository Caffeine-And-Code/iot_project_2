#ifndef __CONTROLLER__
#define __CONTROLLER__
#define MAX_COMPONENTS 50

#include "Arduino.h"
#include "Component.h"
#include "EventScheduler.h"

class EventScheduler;
class Event;
class Component;

class Controller
{
protected:
    Component *components[MAX_COMPONENTS];
    int currentComponentIndex = 0;
    bool verbose = false;

public:
    EventScheduler *
        eventScheduler;
    Controller();
    virtual void setup() = 0;
    virtual void loop() = 0;

    void updateComponents();

    void addComponent(Component *component);

    void triggerEvent(Event *event);
    void print(String logText);
    void println(String logText);
    void enableVerbose();
    void disableVerbose();
};

#endif