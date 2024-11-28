#ifndef __TEMPERATURE_TASK__
#define __TEMPERATURE_TASK__

#include "Task.h"
#include "AppController.h"

class AppController;

class TemperatureTask : public Task
{
private:
    AppController *controller;
    unsigned long initialMillisecOverTemperature = 0;

public:
    TemperatureTask(AppController *controller);
    void tick() override;
    void reset();
};

#endif
