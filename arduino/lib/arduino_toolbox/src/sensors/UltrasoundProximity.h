#ifndef __ULTRASOUND_PROXIMITY__
#define __ULTRASOUND_PROXIMITY__

#include "../DoublePin.h"
#include "Temperature.h"
#include "../ChangeNotifier.h"

class UltrasoundProximity : public DoublePin, public ChangeNotifier
{
private:
    Temperature *temperatureSensor;
    int temperature = 0;
    bool useSensor = false;
    int lastValue = 0;

public:
    UltrasoundProximity(int trigPin, int echoPint, Temperature *temperature);
    UltrasoundProximity(int trigPin, int echoPint, int temperature);
    // Return the distance in cm centimeters
    int getDistance();
    bool hasChanged();
};

#endif