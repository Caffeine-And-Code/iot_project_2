#include "StateMachine.h"
#include "Arduino.h"

StateMachine::StateMachine(Controller *controller) : Component(controller)
{
    this->currentState = -1;
    this->currentStateIndex = 0;
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
            this->controller->triggerEvent(new ChangeStateEvent(
                this->states[lastState], this->states[i]));
            break;
        }
        i++;
    }
}

void StateMachine::update()
{
    if (this->currentState >= 0 && this->currentState < this->currentStateIndex)
        this->stateCallbacks[this->currentState]();
}