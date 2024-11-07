#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define GREEN_LGT_PIN 11
#define RED_LIGHT_PIN 10

#define OPEN_BTN_PIN 13
#define CLOSE_BTN_PIN 12

#define TEMP_PIN 0
#define SERVO_PIN 6
#define MOTION_PIN 4

#define ECHO_PIN 2
#define TRIG_PIN 3

LiquidCrystal_I2C lcd(0x27, 20, 4);
Servo myservo;
unsigned long lastUpdate = millis();

int servoPos = 0;
int motion = 0;
float distance = 0;
float temperature = 0;

void cleanScreen()
{
  int rows[] = {0, 1, 2, 3};
  for (int row : rows)
  {
    lcd.setCursor(0, row);
    lcd.print("                   ");
  }
}

void printData() {
  if (millis() - lastUpdate > 500) {
    lastUpdate = millis();

    cleanScreen();

    lcd.setCursor(0, 0);
    motion = digitalRead(MOTION_PIN);
    if (motion == HIGH) {
      lcd.print("motion");
    }
    else {
      lcd.print("no motion");
    }

    lcd.setCursor(0, 1);
    lcd.print(distance);
    lcd.print("  ");

    lcd.setCursor(0, 2);
    lcd.print(temperature);
    lcd.print("  ");
  }
}

float readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(GREEN_LGT_PIN, OUTPUT);
  pinMode(RED_LIGHT_PIN, OUTPUT);
  pinMode(OPEN_BTN_PIN, INPUT);
  pinMode(CLOSE_BTN_PIN, INPUT);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(TEMP_PIN, INPUT);

  myservo.attach(SERVO_PIN);
}

void loop() {
  int openBtnState = digitalRead(OPEN_BTN_PIN);
  int closeBtnState = digitalRead(CLOSE_BTN_PIN);

  if (openBtnState == HIGH) {
    digitalWrite(GREEN_LGT_PIN, HIGH);
    digitalWrite(RED_LIGHT_PIN, LOW);
    servoPos = 0;
  }
  else if (closeBtnState == HIGH) {
    digitalWrite(RED_LIGHT_PIN, HIGH); 
    digitalWrite(GREEN_LGT_PIN, LOW);
    servoPos = 180;
  }
  else {
    digitalWrite(GREEN_LGT_PIN, LOW);
    digitalWrite(RED_LIGHT_PIN, LOW);
    servoPos = 90;
  }

  myservo.write(servoPos);
  
  distance = readDistanceCM();

  temperature = analogRead(TEMP_PIN);
  temperature = ((temperature * 0.00488) - 0.5) / 0.01;

  printData();
}
