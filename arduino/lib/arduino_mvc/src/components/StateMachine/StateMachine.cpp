#include "StateMachine.h"
#include "Arduino.h"

StateMachine::StateMachine(Controller *controller, unsigned long runDelay) : Component(controller)
{
    this->currentState = -1;
    this->currentStateIndex = 0;
    this->internalTimer = new Timer(controller);
    this->internalTimer->init(runDelay, true);
}

void StateMachine::addState(int stateId, void (*callback)())
{
    if (this->currentStateIndex < MAX_STATES)
    {
        this->states[this->currentStateIndex] = stateId;
        this->stateCallbacks[this->currentStateIndex] = callback;
        this->currentStateIndex++;
    }
}

void StateMachine::changeState(int stateId)
{
    int i = 0;
    while (i < this->currentStateIndex)
    {
        if (this->states[i] == stateId)
        {
            auto lastState = this->currentState;
            this->currentState = i;
            this->currentStateIterations = 0;
            this->controller->triggerEvent(new ChangeStateEvent(
                this->states[lastState], this->states[i]));
            break;
        }
        i++;
    }
}

int StateMachine::getCurrentState()
{
    return this->states[this->currentState];
}

unsigned long StateMachine::getCurrentStateIterationAmount()
{
    return this->currentStateIterations;
}

void StateMachine::update()
{
    if (this->internalTimer->runUpdateAndCheckTrigger())
    {
        if (this->currentState >= 0 && this->currentState < this->currentStateIndex)
        {
            this->currentStateIterations++;
            this->stateCallbacks[this->currentState]();
        }
    }
}