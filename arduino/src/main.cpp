#include <Arduino.h>
//#define DEBUG
#ifndef DEBUG
#include "AppController.h"
#else
#include "TestController.h"
#endif
#include "config/Config.h"

// int freeMemory() {
//     extern int __heap_start, *__brkval;
//     int v;
//     return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
// }

void setup()
{
    Serial.begin(BAUDRATE);
    controller.setup();
}

void loop()
{
    // int memoriaLibera = freeMemory();
    // Serial.print("Memoria libera: ");
    // Serial.print(memoriaLibera);
    // Serial.println(" byte");

    controller.loop();
}