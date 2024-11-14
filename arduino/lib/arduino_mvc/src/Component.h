#ifndef __COMPONENT__
#define __COMPONENT__
#include "Controller.h"
class Controller;
class Component
{
protected:
    Controller *controller;

public:
    Component(Controller *controller) : controller(controller) {}
    virtual void update() = 0;
};

#endif