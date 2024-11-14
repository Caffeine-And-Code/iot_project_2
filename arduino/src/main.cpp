#include <Arduino.h>
#include "AppController.h"
#include "enums/States.h"

void setup()
{
    controller.setup();
}

void loop()
{
    controller.loop();
}