#ifndef __TEST_CONTROLLER__
#define __TEST_CONTROLLER__
#include "Controller.h"
#include "Led.h"
#include "Button.h"
#include "sensors/PIR.h"
#include "outputs/LCDMonitor.h"
#include "config/Config.h"
#include "sensors/Temperature.h"
#include "sensors/UltrasoundProximity.h"
#include "outputs/ServoMotor.h"

class TestController : Controller
{
public:
    Led *L1;
    Led *L2;
    Button *btnOpen;
    Button *btnClose;
    PIR *pir;
    LCDMonitor *monitor;
    Temperature *temperature;
    UltrasoundProximity *proximity;
    ServoMotor *servoMotor;

    void
    setup();
    void loop();
};
extern TestController controller;
#endif