#include <Servo.h>

const int sensorPin = 2;
const int servoPin = 9;
const unsigned long sweepDuration = 2000; // ms to sweep 180 degrees
const unsigned long holdDuration = 2000;  // ms to hold at 180

Servo myServo;

void sweepTo(int target, int current) {
  int steps = abs(target - current);
  int dir = (target > current) ? 1 : -1;
  unsigned long stepDelay = sweepDuration / steps;

  for (int pos = current; pos != target; pos += dir) {
    myServo.write(pos);
    delay(stepDelay);
  }
  myServo.write(target);
}

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT_PULLUP);
  myServo.attach(servoPin);
  myServo.write(0);
  Serial.println("Slot sensor ready.");
}

void loop() {
  int val = digitalRead(sensorPin);
  if (val == LOW) {
    Serial.println("TAB DETECTED");
    sweepTo(180, 0);
    delay(holdDuration);
    sweepTo(0, 180);
    Serial.println("RESET");
  }
}
