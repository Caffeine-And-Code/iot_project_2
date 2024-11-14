#ifndef __OBSERVABLE_MANAGER__
#define __OBSERVABLE_MANAGER__
#define MAX_OBSERVABLE 50
#include "Observable.h"
#include "Controller.h"

class Controller;

class ObservableManager
{
    Observable *observables[MAX_OBSERVABLE];
    Controller *controller;
    int currentIndex = 0;

public:
    ObservableManager(Controller *Controller) : controller(controller) {}
    void addObservable(Observable *observable);
    void update();
};

#endif