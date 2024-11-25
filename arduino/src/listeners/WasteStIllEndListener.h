#ifndef __WASTE_STILL_END_LISTENER__
#define __WASTE_STILL_END_LISTENER__
#include "Listener.h"
#include "AppController.h"
#include "config/Config.h"
class AppController;

class WasteStIllEndListener : public Listener
{
    void execute(Event *event, Controller *controller)
    {
        auto *appController = static_cast<AppController *>(controller);
        appController->stillTimer->stop();
        appController->userLCD->printWasteReceiver();
        appController->door->close();
        delay(T2);
        appController->changeState(Available);
    }
};

#endif