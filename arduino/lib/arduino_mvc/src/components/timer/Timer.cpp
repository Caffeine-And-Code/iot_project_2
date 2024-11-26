#include "Timer.h"

Timer::Timer(Controller *controller, Event *triggerEvent) : triggerEvent(triggerEvent),
                                                            Component(controller)
{
    this->lastCheckMillis = 0;
    this->running = false;
    this->shouldTrigger = true;
}

Timer::Timer(Controller *controller) : triggerEvent(triggerEvent),
                                       Component(controller)
{
    this->lastCheckMillis = 0;
    this->running = false;
    this->shouldTrigger = false;
}

void Timer::init(unsigned long time, bool loop)
{
    this->time = time;
    this->loop = loop;
}

bool Timer::isRunning()
{
    return this->running;
}

void Timer::start()
{
    this->restart();
}

void Timer::restart()
{
    this->running = true;
    this->lastCheckMillis = millis();
}

void Timer::stop()
{
    this->running = false;
}

void Timer::update()
{
    if (this->running && this->lastCheckMillis + this->time < millis())
    {
        if (!this->loop)
        {
            this->running = false;
        }
        this->lastCheckMillis = millis();
        this->trigger = true;
        if (this->shouldTrigger)
        {
            this->controller->triggerEvent(this->triggerEvent);
        }
    }
    else
    {
        this->trigger = false;
    }
}

bool Timer::runUpdateAndCheckTrigger()
{
    if (!this->isRunning())
    {
        this->restart();
    }
    this->update();
    return this->hasTriggered();
}

bool Timer::hasTriggered()
{
    return this->trigger;
}