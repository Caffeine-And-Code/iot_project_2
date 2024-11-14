#ifndef __APP_CONTROLLER__
#define __APP_CONTROLLER__

#include <Arduino.h>
#include "utils/StateMachineController.h"
#include "enums/States.h"
#include "Led.h"
#include "config/Config.h"
#include "toolbox_extended/Door.h"
#include "toolbox_extended/UserLCD.h"
#include "components/timer/Timer.h"
#include "Events/SleepTimerEvent.h"

void availableRoutine();
void sleepRouting();
void doorOpenRoutine();
void fullRoutine();
void emptyingRoutine();
void maxTemperatureRoutine();

class AppController : public StateMachineController
{

public:
    Led *L1;
    Led *L2;
    Door *door;
    UserLCD *userLCD;
    Timer *sleepTimer;

    AppController() : StateMachineController(Available) {}
    void setup()
    {
        this->addState(Available, availableRoutine);
        this->addState(Sleep, sleepRouting);
        this->addState(DoorOpen, doorOpenRoutine);
        this->addState(Full, fullRoutine);
        this->addState(Emptying, emptyingRoutine);
        this->addState(MaxTemperature, maxTemperatureRoutine);
        L1 = new Led(L1_PIN);
        L2 = new Led(L2_PIN);
        door = new Door(DOOR_PIN);
        userLCD = new UserLCD();
        sleepTimer = new Timer(this, new SleepTimerEvent());
        sleepTimer->init(SLEEP_TIMER_SECONDS, false);
    }
};

extern AppController controller;
#endif