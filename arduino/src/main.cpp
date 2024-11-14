#include <Arduino.h>
#include "AppController.h"
#include "config/Config.h"

void setup()
{
    Serial.begin(BAUDRATE);
    controller.setup();
}

void loop()
{
    controller.loop();
}