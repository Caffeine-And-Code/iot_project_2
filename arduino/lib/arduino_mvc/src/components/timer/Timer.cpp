#include "Timer.h"

Timer::Timer(Controller *controller, TimerEvent *triggerEvent) : triggerEvent(triggerEvent),
                                                                 Component(controller)
{
    this->lastCheckMillis = 0;
    this->running = false;
}

void Timer::init(long time, bool loop)
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

void Timer::update()
{
    if (this->running && this->lastCheckMillis + this->time < millis())
    {
        if (!this->loop)
        {
            this->running = false;
        }
        this->lastCheckMillis = millis();
        this->controller->triggerEvent(this->triggerEvent);
    }
}