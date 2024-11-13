#ifndef __LED__
#define __LED__

#include "MonoPin.h"

class Led : public MonoPin
{
public:
    Led(int pin);
    void switchOn();
    void switchOff();
};

#endif