#ifndef __WASTE_DETECTOR__
#define __WASTE_DETECTOR__
#include "sensors/UltrasoundProximity.h"
#include "Events/WasteUpdateEvent.h"
#include "config/Config.h"

class WasteDetector : UltrasoundProximity
{
public:
    WasteDetector(int trigPin, int echoPint, Temperature *temperature) : UltrasoundProximity(trigPin, echoPint, temperature) {}
    int getFullPercentage()
    {
        auto distance = this->getDistance();
        if (distance < MIN_WASTE_CM)
        {
            distance = MIN_WASTE_CM;
        }
        else if (distance > MAX_WASTE_CM)
        {
            distance = MAX_WASTE_CM;
        }

        distance -= MIN_WASTE_CM;
        auto interval = MAX_WASTE_CM - MIN_WASTE_CM;

        return ceil(distance * 100 / interval);
    }

    bool isFull()
    {
        return getFullPercentage() == 100;
    }
};

#endif