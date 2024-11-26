#ifndef __WASTE_DETECTOR__
#define __WASTE_DETECTOR__
#include "sensors/UltrasoundProximity.h"
#include "Events/WasteUpdateEvent.h"
#include "config/Config.h"

class WasteDetector : UltrasoundProximity
{
public:
    WasteDetector(unsigned char trigPin, unsigned char echoPint, Temperature *temperature) : UltrasoundProximity(trigPin, echoPint, temperature) {}
    short getFullPercentage()
    {
        short distance = this->getDistance();
        if (distance < MIN_WASTE_CM)
        {
            distance = MIN_WASTE_CM;
        }
        else if (distance > MAX_WASTE_CM)
        {
            distance = MAX_WASTE_CM;
        }

        distance -= MIN_WASTE_CM;
        short interval = MAX_WASTE_CM - MIN_WASTE_CM;
        distance = interval - distance;

        short value = ceil(distance * 100 / interval);
        return value;
    }

    bool isFull()
    {
        return getFullPercentage() == 100;
    }
};

#endif