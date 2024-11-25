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
#include "agents/SerialAgent.h"
#include "toolbox_extended/PeopleDetector.h"
#include "Button.h"
#include "components/timer/Timer.h"
#include "toolbox_extended/WasteDetector.h"
#include "sensors/Temperature.h"
#include "agents/TemperatureAgent.h"

class SerialAgent;

void availableRoutine();
void sleepRouting();
void doorOpenRoutine();
void fullRoutine();
void emptyingRoutine();
void maxTemperatureRoutine();
void onPIRTrigger();

class TemperatureAgent;

class AppController : public StateMachineController
{

public:
    Led *L1;
    Led *L2;
    Door *door;
    UserLCD *userLCD;
    Timer *sleepTimer;
    SerialAgent *serial;
    PeopleDetector *peopleDetector;
    Button *btnOpen;
    Button *btnClose;
    Timer *stillTimer;
    WasteDetector *wasteDetector;
    Temperature *temperature;
    TemperatureAgent *temperatureAgent;

    AppController() : StateMachineController((long)STATE_MACHINE_FRESH_RATE) {}
    void setup();
};

extern AppController controller;
#endif