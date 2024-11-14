#include "AppController.h"

AppController controller;

void availableRoutine()
{
    controller.L1->switchOn();
    controller.userLCD->printAvailableMessage();
    if (!controller.sleepTimer->isRunning())
    {
        controller.sleepTimer->start();
    }
}
void sleepRouting()
{
    controller.L1->switchOn();
    delay(1000);
    controller.L1->switchOff();
    delay(1000);
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