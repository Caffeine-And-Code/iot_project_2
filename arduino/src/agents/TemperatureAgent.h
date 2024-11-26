#ifndef __TEMPERATURE_AGENT__
#define __TEMPERATURE_AGENT__
#include "Component.h"
#include "AppController.h"

class AppController;

class TemperatureAgent : public Component
{
protected:
    unsigned long initialMillisecOverTemperature = 0;

public:
    TemperatureAgent(Controller *controller) : Component(controller) {}
    void update();
    void reset();
};

#endif