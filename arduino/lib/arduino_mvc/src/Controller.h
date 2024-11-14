#ifndef __CONTROLLER__
#define __CONTROLLER__
#define MAX_COMPONENTS 50

#include "Component.h"
#include "EventScheduler.h"
#include "ObservableManager.h"

class EventScheduler;
class Event;
class ObservableManager;
class Component;

class Controller
{
protected:
    Component *components[MAX_COMPONENTS];
    int currentComponentIndex = 0;

public:
    EventScheduler *eventScheduler;
    ObservableManager *observableManager;
    Controller();
    virtual void setup() = 0;
    virtual void loop() = 0;

    void updateComponents();

    void addComponent(Component *component);

    void triggerEvent(Event *event);
};

#endif