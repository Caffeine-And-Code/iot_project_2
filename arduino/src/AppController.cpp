#include "AppController.h"
#include "Arduino.h"
#include "listeners/ChangeStateListener.h"
#include "listeners/SleepTimerListener.h"
#include "listeners/WakeUpListener.h"
#include <avr/sleep.h>
#include "events/WakeUpEvent.h"
#include "events/WasteStillEndEvent.h"
#include "listeners/WasteStIllEndListener.h"
#include "events/WasteUpdateEvent.h"
#include "listeners/WasteUpdateListener.h"

AppController controller;

void AppController::setup()
{
    this->disableVerbose();

    L1 = new Led(L1_PIN);
    L2 = new Led(L2_PIN);
    door = new Door(DOOR_PIN);
    userLCD = new UserLCD();
    serial = new SerialAgent();
    peopleDetector = new PeopleDetector(PIR_PIN);
    btnOpen = new Button(BTN_OPEN_PIN);
    btnClose = new Button(BTN_CLOSE_PIN);
    temperature = new Temperature(TEMPERATURE_PIN);
    wasteDetector = new WasteDetector(TRIG_PIN, ECHO_PIN, temperature);

    sleepTimer = new Timer(this, new SleepTimerEvent());
    sleepTimer->init(SLEEP_TIMER_SECONDS * 1000, false);
    stillTimer = new Timer(this, new WasteStillEndEvent());
    stillTimer->init(T1, false);

    this->eventScheduler->addSchedule(ChangeStateEvent::EventID, new ChangeStateListener());
    this->eventScheduler->addSchedule(SleepTimerEvent::EventID, new SleepTimerListener());
    this->eventScheduler->addSchedule(WakeUpEvent::EventID, new WakeUpListener());
    this->eventScheduler->addSchedule(WasteStillEndEvent::EventID, new WasteStIllEndListener());
    this->eventScheduler->addSchedule(WasteUpdateEvent::EventID, new WasteUpdateListener());

    attachInterrupt(digitalPinToInterrupt(PIR_PIN), onPIRTrigger, RISING);

    stateMachineTask = new StateMachineTask(this);
    stateMachineTask->init(100);
    temperatureTask = new TemperatureTask(this);
    temperatureTask->init(1000);

    this->stateMachineTask->changeState(Available);

    this->scheduler->init(100);
    this->scheduler->addTask(stateMachineTask);
    this->scheduler->addTask(temperatureTask);
}

void AppController::loop()
{
    if (this->eventScheduler->hasEventToTrigger())
    {
        this->eventScheduler->trigger();
    }
    else
    {
        this->scheduler->schedule();
    }
}

void onPIRTrigger()
{
    controller.println("Triggered PIR interrupt");
}