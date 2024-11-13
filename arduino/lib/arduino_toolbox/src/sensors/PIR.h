#ifndef __PIR__
#define __PIR__

#include "../MonoPin.h"
#include "../ChangeNotifier.h"

class PIR : public MonoPin, ChangeNotifier
{
protected:
    bool lastValue;

public:
    PIR(int pin);
    void calibrate(int calibrationSeconds);
    // True if someone is detected from the sensor
    bool hasDetected();
    bool hasChanged();
};

#endif