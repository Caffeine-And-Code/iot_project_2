#include "StateMachineTask.h"
#include "enums/States.h"
#include "states/AvailableState.h"
#include "states/DoorOpenState.h"
#include "states/FullState.h"
#include "states/MaxTemperatureState.h"
#include "states/SleepState.h"

StateMachineTask::StateMachineTask(AppController *controller) : StateMachine(controller)
{
    this->addState(Available, new AvailableState(controller));
    this->addState(Sleep, new SleepState(controller));
    this->addState(DoorOpen, new DoorOpenState(controller));
    this->addState(Full, new FullState(controller));
    this->addState(MaxTemperature, new MaxTemperatureState(controller));
}