#ifndef __OBSERVABLE__
#define __OBSERVABLE__
#include "Controller.h"
class Controller;

class Observable
{
public:
    virtual void update(Controller *controller) = 0;
};

#endif