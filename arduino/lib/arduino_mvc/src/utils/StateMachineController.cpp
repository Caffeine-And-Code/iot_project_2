#include "StateMachineController.h"
#include "Arduino.h"

StateMachineController::StateMachineController()
{
    this->stateMachine = new StateMachine(this);
}
void StateMachineController::addState(int stateId, void (*callback)())
{
    this->stateMachine->addState(stateId, callback);
}

void StateMachineController::changeState(int stateId)
{
    this->stateMachine->changeState(stateId);
}

void StateMachineController::setup() {}

void StateMachineController::loop()
{
    this->updateComponents();
    this->stateMachine->update();
}