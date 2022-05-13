#include <Servo.h>
Servo myServo;
unsigned long MOVING_TIME = 5000; // moving time is 3 seconds
unsigned long moveStartTime;
int startAngle = 90; // 180°
int stopAngle  = 250; // 70°

int LED1 = 3;
int LED2 = 4;
int LED3 = 5;
int BTN = 2;
int SERVO = 6;

int buttonState = 0;

bool firstRotationDone = false;
bool secondRotationDone = false;
bool BtnPressed = false;

void setup() {
  myServo.attach(SERVO);
  moveStartTime = millis(); // start moving
  Serial.begin(9600);
  
  // LED Code
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED2, OUTPUT);

  //Button Code
  pinMode(BTN, INPUT);
}

void loop() {
  if (BtnPressed) {

    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    if (!firstRotationDone) {
      for (int i = startAngle ; i != stopAngle; i++) {
        myServo.write(i);
        delay(100);
        if (i >= stopAngle - 5) {
          firstRotationDone = true;
        }
      }
    }

    if (firstRotationDone && !secondRotationDone) {
      for (int i = stopAngle ; i != startAngle; i--) {
        myServo.write(i);
        delay(100);
        if (i >= startAngle + 5) {
          secondRotationDone = true;
          digitalWrite(LED1, LOW);
          digitalWrite(LED2, LOW);
          digitalWrite(LED3, LOW);
          firstRotationDone = false;
          secondRotationDone = false;
          BtnPressed = false;
        }
      }
    }
  }
  //Button code
  buttonState = digitalRead(BTN);

  if (buttonState == 1) {
    // turn LED on:
    BtnPressed = true;
    //digitalWrite(LED1, HIGH);
    //digitalWrite(LED2, HIGH);
    //digitalWrite(LED3, HIGH);
  }
}
