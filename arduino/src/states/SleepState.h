#ifndef __SLEEP_STATE__
#define __SLEEP_STATE__
#include "components/StateMachine/State.h"
#include "AppController.h"
#include <avr/sleep.h>
#include "Arduino.h"
#include "Events/WakeUpEvent.h"

class SleepState : public State
{
private:
    AppController *controller;

public:
    SleepState(AppController *controller) : controller(controller) {}
    void run() override
    {
        controller->userLCD->empty();
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
        sleep_mode();
        sleep_disable();
        controller->triggerEvent(new WakeUpEvent());
        controller->userLCD->wakeUp();
        controller->stateMachineTask->changeState(Available);
    }
};

#endif