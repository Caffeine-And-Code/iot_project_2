#ifndef __DOOR_OPEN_STATE__
#define __DOOR_OPEN_STATE__
#include "components/StateMachine/State.h"
#include "AppController.h"
#include "Events/WasteStillEndEvent.h"

class DoorOpenState : public State
{
private:
    AppController *controller;

public:
    DoorOpenState(AppController *controller) : controller(controller) {}
    void run() override
    {
        controller->stillTimer->update();
        if (controller->btnClose->isPressed())
        {
            controller->triggerEvent(new WasteStillEndEvent());
        }
        else
        {
            if (controller->wasteDetector->hasChanged())
            {
                auto wasteLevelPercentage = controller->wasteDetector->getFullPercentage();
                controller->triggerEvent(new WasteUpdateEvent(wasteLevelPercentage));
            }
        }
    }
};

#endif