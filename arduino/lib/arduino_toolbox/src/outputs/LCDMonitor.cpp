#include "LCDMonitor.h"
#include "Arduino.h"

LCDMonitor::LCDMonitor(uint8_t lcdAddr, int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;
    this->monitor = new LiquidCrystal_I2C(lcdAddr, rows, columns);
    this->monitor->init();
    this->monitor->backlight();
}

void LCDMonitor::print(int row, int col, String chars, bool withClean = false)
{
    Serial.println(row);
    Serial.println(col);
    Serial.println(chars);
    for (int i = 0; i < col && withClean; i++)
    {
        this->monitor->setCursor(i, row);
        this->monitor->print(" ");
    }
    this->monitor->setCursor(col, row);
    this->monitor->print(chars);
    int length = chars.length();
    for (int i = col + length + 1; i < this->columns && withClean; i++)
    {
        this->monitor->setCursor(i, row);
        this->monitor->print(" ");
    }
}

void LCDMonitor::clean()
{
    for (int i = 0; i < this->rows; i++)
    {
        this->print(i, 0, "", true);
    }
}

void LCDMonitor::printSlideShow(String toPrint, int row, int endCol, int animationDelay = 150)
{
    auto strLen = toPrint.length();
    for (unsigned int i = 0; i < strLen; i++)
    {
        for (unsigned int j = 0; j <= endCol - i; j++)
        {
            int prev = j - 1 > 0 ? j - 1 : 0;
            this->monitor->setCursor(prev, row);
            this->monitor->print(" ");
            this->monitor->setCursor(j, row);
            this->monitor->print(toPrint.charAt(strLen - 1 - i));
            delay(animationDelay);
        }
    }
}

void LCDMonitor::printCentered(String toPrint, int row)
{
    int len = toPrint.length();
    int start = (this->columns - len) / 2;
    this->print(row, start, toPrint, true);
}