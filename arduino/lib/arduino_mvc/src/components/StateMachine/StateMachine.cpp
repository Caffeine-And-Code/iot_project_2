#include "StateMachine.h"

StateMachine::StateMachine(Controller *controller, int currentState = 0) : Component(controller)
{
    this->currentState = currentState;
}

void StateMachine::addState(int stateId, void (*callback)())
{
    if (this->currentStateIndex < MAX_STATES)
    {
        this->states[this->currentStateIndex] = stateId;
        this->stateCallbacks[this->currentStateIndex] = callback;
    }
}

void StateMachine::changeState(int stateId)
{
    int i = 0;
    while (i < this->currentStateIndex)
    {
        if (this->states[i] == stateId)
        {
            this->controller->triggerEvent(new ChangeStateEvent(
                this->states[this->currentState], this->states[i]));
            this->currentState = i;
            break;
        }
        i++;
    }
}

void StateMachine::update()
{
    this->stateCallbacks[this->currentState]();
}