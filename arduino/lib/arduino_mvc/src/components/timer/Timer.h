#ifndef __TIMER__
#define __TIMER__
#include "Controller.h"
#include "Arduino.h"
#include "Event.h"
#include "Component.h"

class Timer : public Component
{
    bool loop;
    long time;
    long lastCheckMillis;
    bool running;
    Event *triggerEvent;
    bool shouldTrigger;
    bool trigger;

public:
    Timer(Controller *controller, Event *triggerEvent);
    Timer(Controller *controller);
    void init(long time, bool loop);

    bool isRunning();

    void start();

    void restart();
    void stop();

    void update();
    bool runUpdateAndCheckTrigger();
    bool hasTriggered();
};

#endif