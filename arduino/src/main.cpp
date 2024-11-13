#include <Arduino.h>
#include "Led.h"
#include "Button.h"
#include "sensors/PIR.h"
#include "sensors/Temperature.h"
#include "sensors/UltrasoundProximity.h"
#include "outputs/LCDMonitor.h"
#include "sensors/ServoMotor.h"

Led *led;
Button *button;
PIR *pir;
Temperature *temperature;
UltrasoundProximity *ultrasound;
LCDMonitor *monitor;
ServoMotor *motor;

void setup()
{
  // put your setup code here, to run once:
  // led = new Led(4);
  // button = new Button(5);
  // temperature = new Temperature(A0);
  // ultrasound = new UltrasoundProximity(7, 8, temperature);
  // monitor = new LCDMonitor(0x27, 4, 20);
  motor = new ServoMotor(9);
  Serial.begin(9600);
}

void loop()
{
  motor->open();
  delay(2000);
  motor->close();
}
