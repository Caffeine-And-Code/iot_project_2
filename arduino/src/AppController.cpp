#include "AppController.h"
#include "Arduino.h"
#include "listeners/ChangeStateListener.h"
#include "listeners/SleepTimerListener.h"
#include "listeners/WakeUpListener.h"
#include <avr/sleep.h>
#include "events/WakeUpEvent.h"

AppController controller;

void AppController::setup()
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
    sleepTimer->init(SLEEP_TIMER_SECONDS * 1000, false);

    this->eventScheduler->addSchedule("ChangeStateEvent", new ChangeStateListener());
    this->eventScheduler->addSchedule("SleepTimerEvent", new SleepTimerListener());
    this->eventScheduler->addSchedule("WakeUpEvent", new WakeUpListener());

    this->addComponent(sleepTimer);
    this->changeState(Available);

    attachInterrupt(digitalPinToInterrupt(PIR_PIN), onPIRTrigger, RISING);
}

void availableRoutine()
{
    controller.L1->switchOn();
    controller.userLCD->printAvailableMessage();
}
void sleepRouting()
{
    controller.userLCD->empty();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
    controller.userLCD->wakeUp();
    controller.changeState(Available);
}
void doorOpenRoutine()
{
}
void fullRoutine()
{
}
void emptyingRoutine()
{
}
void maxTemperatureRoutine()
{
}
void onPIRTrigger()
{
    controller.triggerEvent(new WakeUpEvent());
}