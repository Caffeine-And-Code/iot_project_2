#ifndef __WASTE_DETECTOR__
#define __WASTE_DETECTOR__
#include "sensors/UltrasoundProximity.h"
#include "Events/WasteUpdateEvent.h"
#include "config/Config.h"
#include "ChangeNotifier.h"

class WasteDetector : UltrasoundProximity
{
private:
    short lastValue = -1;
    short currentValue = -2;

public:
    WasteDetector(unsigned char trigPin, unsigned char echoPint, Temperature *temperature) : UltrasoundProximity(trigPin, echoPint, temperature) {}
    short getFullPercentage()
    {
        return this->currentValue;
    }

    bool isFull()
    {
        return getFullPercentage() == 100;
    }

    bool hasChanged() override
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
        this->lastValue = this->currentValue;
        this->currentValue = value;
        return this->currentValue != this->lastValue;
    }
};

#endif