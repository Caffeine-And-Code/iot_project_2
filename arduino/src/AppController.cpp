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

    this->addState(Available, availableRoutine);
    this->addState(Sleep, sleepRouting);
    this->addState(DoorOpen, doorOpenRoutine);
    this->addState(Full, fullRoutine);
    this->addState(MaxTemperature, maxTemperatureRoutine);
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
    temperatureAgent = new TemperatureAgent(this);

    sleepTimer = new Timer(this, new SleepTimerEvent());
    sleepTimer->init(SLEEP_TIMER_SECONDS * 1000, false);
    stillTimer = new Timer(this, new WasteStillEndEvent());
    stillTimer->init(T1, false);

    this->eventScheduler->addSchedule(ChangeStateEvent::EventID, new ChangeStateListener());
    this->eventScheduler->addSchedule(SleepTimerEvent::EventID, new SleepTimerListener());
    this->eventScheduler->addSchedule(WakeUpEvent::EventID, new WakeUpListener());
    this->eventScheduler->addSchedule(WasteStillEndEvent::EventID, new WasteStIllEndListener());
    this->eventScheduler->addSchedule(WasteUpdateEvent::EventID, new WasteUpdateListener());

    this->changeState(Available);

    this->addComponent(temperatureAgent);
    attachInterrupt(digitalPinToInterrupt(PIR_PIN), onPIRTrigger, RISING);
}

void availableRoutine()
{
    controller.sleepTimer->update();
    if (controller.btnOpen->isPressed())
    {
        controller.changeState(DoorOpen);
    }
    if (controller.peopleDetector->isPersonDetected())
    {
        controller.sleepTimer->restart();
    }
}
void sleepRouting()
{
    controller.userLCD->empty();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
    controller.triggerEvent(new WakeUpEvent());
    controller.userLCD->wakeUp();
    controller.changeState(Available);
}
void doorOpenRoutine()
{
    controller.sleepTimer->update();
    controller.door->open();
    if (controller.btnClose->isPressed())
    {
        controller.triggerEvent(new WasteStillEndEvent());
    }
    else
    {
        auto wasteLevelPercentage = controller.wasteDetector->getFullPercentage();
        controller.triggerEvent(new WasteUpdateEvent(wasteLevelPercentage));
        if (wasteLevelPercentage == 100)
        {
            controller.changeState(Full);
        }
    }
}
void fullRoutine()
{
    if (controller.serial->emptyContainer())
    {
        controller.door->reverseOpen();
        delay(T3);
        controller.changeState(Available);
    }
}
void maxTemperatureRoutine()
{
    if (controller.serial->fixTemperature())
    {
        controller.changeState(Available);
    }
}
void onPIRTrigger()
{
    controller.println("Triggered PIR interrupt");
}