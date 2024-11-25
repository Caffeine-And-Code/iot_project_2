#ifndef __STATE_MACHINE_CONTROLLER__
#define __STATE_MACHINE_CONTROLLER__
#define MAX_STATES 50
#include "Controller.h"
#include "Component.h"
#include "components/StateMachine/StateMachine.h"

class StateMachineController : public Controller
{
protected:
    StateMachine *stateMachine;

public:
    StateMachineController(long runDelay);
    void addState(int stateId, void (*callback)());

    void changeState(int stateId);
    int getCurrentState();

    void setup();

    void loop();
};

#endif