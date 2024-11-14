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
void onPIRTrigger();

class AppController : public StateMachineController
{

public:
    Led *L1;
    Led *L2;
    Door *door;
    UserLCD *userLCD;
    Timer *sleepTimer;

    void setup();
};

extern AppController controller;
#endif