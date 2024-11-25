#include "Controller.h"
#include "Arduino.h"

Controller::Controller()
{
    this->eventScheduler = new EventScheduler(this);
    this->observableManager = new ObservableManager(this);
}

void Controller::updateComponents()
{
    for (int i = 0; i < this->currentComponentIndex; i++)
    {
        this->components[i]->update();
    }
}

void Controller::addComponent(Component *component)
{
    if (this->currentComponentIndex < MAX_COMPONENTS)
    {
        this->components[this->currentComponentIndex++] = component;
    }
}

void Controller::triggerEvent(Event *event)
{
    this->eventScheduler->trigger(event);
}

void Controller::print(String logWrite)
{
    if (verbose)
    {
        Serial.print(logWrite);
    }
}

void Controller::println(String logWrite)
{
    if (verbose)
    {
        Serial.println(logWrite);
    }
}

void Controller::enableVerbose()
{
    verbose = true;
}
void Controller::disableVerbose()
{
    verbose = false;
}