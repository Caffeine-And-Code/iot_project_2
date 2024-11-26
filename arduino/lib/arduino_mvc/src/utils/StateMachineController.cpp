#include "StateMachineController.h"
#include "Arduino.h"

StateMachineController::StateMachineController(unsigned long runDelay = 0)
{
    this->stateMachine = new StateMachine(this, runDelay);
}
void StateMachineController::addState(int stateId, void (*callback)())
{
    this->stateMachine->addState(stateId, callback);
}

void StateMachineController::changeState(int stateId)
{
    if (stateId != this->getCurrentState())
        this->stateMachine->changeState(stateId);
}

int StateMachineController::getCurrentState()
{
    return this->stateMachine->getCurrentState();
}

unsigned long StateMachineController::getCurrentStateIterationAmount()
{
    this->stateMachine->getCurrentStateIterationAmount();
}

void StateMachineController::setup() {}

void StateMachineController::loop()
{
    if (this->eventScheduler->hasEventToTrigger())
    {
        this->eventScheduler->trigger();
    }
    else
    {
        this->updateComponents();
        this->stateMachine->update();
    }
}