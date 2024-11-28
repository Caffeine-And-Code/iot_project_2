#ifndef __WASTE_UPDATE_LISTENER__
#define __WASTE_UPDATE_LISTENER__
#include "Listener.h"
#include "events/WasteUpdateEvent.h"
#include "AppController.h"

class WasteUpdateListener : public Listener
{
    void execute(Event *event, Controller *controller)
    {
        WasteUpdateEvent *wasteEvent = static_cast<WasteUpdateEvent *>(event);
        AppController *appController = static_cast<AppController *>(controller);
        if (appController->stateMachineTask->getCurrentState() == DoorOpen)
            appController->serial->updateWasteLevel(wasteEvent->getPercentage());
    }
};

#endif
