#ifndef __USER_LCD__
#define __USER_LCD__
#include "outputs/LCDMonitor.h"

class UserLCD : LCDMonitor
{
public:
    UserLCD() : LCDMonitor(0x27, 4, 20) {}

    void printAvailableMessage()
    {
        this->printCentered("PRESS OPEN", 1);
        this->printCentered("TO ENTER WASTE", 2);
    }
};

#endif