#include "StateMachineController.h"
#include "Arduino.h"

StateMachineController::StateMachineController(long runDelay = 0)
{
    this->stateMachine = new StateMachine(this, runDelay);
}
void StateMachineController::addState(int stateId, void (*callback)())
{
    this->stateMachine->addState(stateId, callback);
}

void StateMachineController::changeState(int stateId)
{
    this->stateMachine->changeState(stateId);
}

int StateMachineController::getCurrentState()
{
    return this->stateMachine->getCurrentState();
}

void StateMachineController::setup() {}

void StateMachineController::loop()
{
    this->updateComponents();
    this->stateMachine->update();
}