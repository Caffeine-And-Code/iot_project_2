#ifndef __SERIAL_AGENT__
#define __SERIAL_AGENT__
#include "Arduino.h"
#include "AppController.h"

class AppController;

class SerialAgent
{
public:
    void updateWasteLevel(short percentageLevel);
    void updateTemperature(short temperature);
    bool emptyContainer();
    bool fixTemperature();
};

#endif