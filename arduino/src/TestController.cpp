#include "TestController.h"

void TestController::setup()
{
    L1 = new Led(L1_PIN);
    L2 = new Led(L2_PIN);
    btnOpen = new Button(BTN_OPEN_PIN);
    btnClose = new Button(BTN_CLOSE_PIN);
    pir = new PIR(PIR_PIN);
    monitor = new LCDMonitor(0x27, 4, 20);
    temperature = new Temperature(TEMPERATURE_PIN);
    proximity = new UltrasoundProximity(TRIG_PIN, ECHO_PIN, temperature);
    servoMotor = new ServoMotor(DOOR_PIN);
}

void TestController::loop()
{
    L1->switchOn();
    L2->switchOn();
    String btnString = "Buttons: ";
    if (btnOpen->isPressed())
    {
        btnString.concat(" 1 ");
    }
    if (btnClose->isPressed())
    {
        btnString.concat(" 2 ");
    }
    monitor->printCentered(btnString, 0);
    monitor->printCentered(String(temperature->getTemperature()), 1);
    monitor->printCentered(pir->hasDetected() ? "Moving" : "Quiet", 2);
    monitor->printCentered("Distance: " + String(proximity->getDistance()), 3);
    servoMotor->open();
    delay(1000);
    servoMotor->close();
    delay(1000);
}