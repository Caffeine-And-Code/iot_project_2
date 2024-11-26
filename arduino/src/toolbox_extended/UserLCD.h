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

    void printOnDoorOpenMessage()
    {
        this->printCentered("PRESS CLOSE", 1);
        this->printCentered("WHEN DONE", 2);
    }

    void printWasteReceiver()
    {
        this->printCentered("WASTE RECEIVED", 1);
        this->printCentered(" ", 2);
    }

    void printContainerFull()
    {
        this->printCentered("CONTAINER", 1);
        this->printCentered("FULL", 2);
    }

    void printProblemDetected()
    {
        this->printCentered("PROBLEM DETECTED", 1);
        this->printCentered(" ", 2);
    }

    void empty()
    {
        this->monitor->noBacklight();
        this->clean();
    }

    void wakeUp()
    {
        this->monitor->backlight();
    }
};

#endif