#include "SleepTimerListener.h"

void SleepTimerListener::execute(Event *event, AppController *controller)
{
    controller->changeState(Sleep);
}