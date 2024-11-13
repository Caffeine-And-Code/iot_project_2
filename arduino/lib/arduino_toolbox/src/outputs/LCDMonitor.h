#ifndef __LCD_MONITOR__
#define __LCD_MONITOR__

#include "LiquidCrystal_I2C.h"

class LCDMonitor
{
private:
    int rows = 0;
    int columns = 0;

public:
    LiquidCrystal_I2C *monitor;
    LCDMonitor(uint8_t lcdAddr, int rows, int columns);
    void print(int row, int col, String chars, bool withClean = false);
    void clean();
    void printSlideShow(String toPrint, int row, int endCol, int animationDelay = 150);
    void printCentered(String toPrint, int row);
};

#endif