#ifndef __STATE_MACHINE__
#define __STATE_MACHINE__
#define MAX_STATES 50
#include "Component.h"
#include "ChangeStateEvent.h"
#include "Controller.h"
#include "components/timer/Timer.h"

class StateMachine : public Component
{
protected:
    int currentState;
    int states[MAX_STATES];
    void (*stateCallbacks[MAX_STATES])();
    int currentStateIndex = 0;
    Timer *internalTimer;
    unsigned long currentStateIterations = 0;

public:
    StateMachine(Controller *controller, unsigned long runDelay);

    void addState(int stateId, void (*callback)());

    void changeState(int stateId);
    int getCurrentState();
    unsigned long getCurrentStateIterationAmount();

    void update();
};

#endif