#ifndef __CONFIG__
#define __CONFIG__
#include "Arduino.h"

#define L1_PIN 10
#define L2_PIN 11
#define BTN_OPEN_PIN 8
#define BTN_CLOSE_PIN 9
#define DOOR_PIN 6
#define PIR_PIN 3
#define TRIG_PIN 4
#define ECHO_PIN 5
#define TEMPERATURE_PIN A0

#define BAUDRATE 9600
#define SLEEP_TIMER_SECONDS 5
#define T1 5000
#define T2 5000
#define T3 5000

#define MAX_WASTE_CM 30
#define MIN_WASTE_CM 5

#define MAX_TEMP 20
#define MAX_TEMP_TIME_SECONDS 5

#define STATE_MACHINE_FRESH_RATE 100

#endif