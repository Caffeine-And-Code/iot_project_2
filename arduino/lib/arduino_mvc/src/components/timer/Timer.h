#ifndef __TIMER__
#define __TIMER__
#include "Controller.h"
#include "Arduino.h"
#include "TimerEvent.h"
#include "Component.h"

class Timer : public Component
{
    bool loop;
    long time;
    long lastCheckMillis;
    bool running;
    TimerEvent *triggerEvent;

public:
    Timer(Controller *controller, TimerEvent *triggerEvent);
    void init(long time, bool loop);

    bool isRunning();

    void start();

    void restart();

    void update();
};

#endif