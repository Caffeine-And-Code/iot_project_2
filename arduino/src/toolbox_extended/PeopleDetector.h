#ifndef __PEOPLE_DETECTOR__
#define __PEOPLE_DETECTOR__
#include "sensors/PIR.h"

class PeopleDetector : PIR
{
public:
    PeopleDetector(int pin) : PIR(pin) {}

    bool isPersonDetected()
    {
        return this->hasDetected();
    }
};

#endif