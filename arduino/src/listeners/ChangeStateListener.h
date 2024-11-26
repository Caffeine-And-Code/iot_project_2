#ifndef __CHANGE_STATE_LISTENER__
#define __CHANGE_STATE_LISTENER__
#include "Listener.h"
#include "components/StateMachine/ChangeStateEvent.h"
#include "components/timer/Timer.h"
#include "AppController.h"
#include "Event.h"
#include "Controller.h"

class ChangeStateListener : public Listener
{
public:
    void execute(Event *event, Controller *controller)
    {
        auto *changeStateEvent = static_cast<ChangeStateEvent *>(event);
        auto *appController = static_cast<AppController *>(controller);

        appController->print("Change state from ");
        appController->print(String(changeStateEvent->getLastState()));
        appController->print(", to ");
        appController->println(String(changeStateEvent->getNewState()));

        if (changeStateEvent->getNewState() == Available)
        {
            appController->sleepTimer->start();
            appController->L1->switchOn();
            appController->userLCD->printAvailableMessage();
            appController->door->close();
        }
        else
        {
            appController->sleepTimer->stop();
        }

        if (changeStateEvent->getNewState() == DoorOpen)
        {
            appController->stillTimer->start();
            appController->userLCD->printOnDoorOpenMessage();
            appController->door->open();
        }
        else
        {
            appController->stillTimer->stop();
        }

        if (changeStateEvent->getNewState() == Full)
        {
            appController->serial->wasteError();
            appController->L1->switchOff();
            appController->L2->switchOn();
            appController->userLCD->printContainerFull();
            appController->door->close();
        }

        if (changeStateEvent->getNewState() == MaxTemperature)
        {
            appController->userLCD->printProblemDetected();
            appController->L1->switchOff();
            appController->L2->switchOn();
            appController->door->close();
        }

        if (changeStateEvent->getNewState() != MaxTemperature && changeStateEvent->getNewState() != Full)
        {
            appController->L2->switchOff();
        }
    }
};

#endif