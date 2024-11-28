#ifndef __APP_CONTROLLER__
#define __APP_CONTROLLER__

#include <Arduino.h>
#include "Controller.h"
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
#include "tasks/StateMachineTask.h"
#include "tasks/TemperatureTask.h"

class SerialAgent;

void onPIRTrigger();

class TemperatureTask;
class StateMachineTask;

class AppController : public Controller
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

    StateMachineTask *stateMachineTask;
    TemperatureTask *temperatureTask;

    void setup() override;
    void loop() override;
};

extern AppController controller;
#endif