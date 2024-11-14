#ifndef __STATE_MACHINE__
#define __STATE_MACHINE__
#define MAX_STATES 50
#include "Component.h"
#include "ChangeStateEvent.h"
#include "Controller.h"

class StateMachine : public Component
{
protected:
    int currentState;
    int states[MAX_STATES];
    void (*stateCallbacks[MAX_STATES])();
    int currentStateIndex = 0;

public:
    StateMachine(Controller *controller);

    void addState(int stateId, void (*callback)());

    void changeState(int stateId);

    void update();
};

#endif