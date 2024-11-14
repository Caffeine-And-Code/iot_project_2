#include "ChangeStateEvent.h"

ChangeStateEvent::ChangeStateEvent(int lastState, int newState) : lastState(lastState),
                                                                  newState(newState) {}

String ChangeStateEvent::getEventName()
{
    return "ChangeStateEvent";
}
int ChangeStateEvent::getLastState()
{
    return this->lastState;
}
int ChangeStateEvent::getNewState()
{
    return this->newState;
}