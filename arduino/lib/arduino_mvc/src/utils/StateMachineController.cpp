#include "StateMachineController.h"

StateMachineController::StateMachineController(int currentState)
{
    this->stateMachine = new StateMachine(this, currentState);
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