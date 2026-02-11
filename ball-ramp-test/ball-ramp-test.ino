#include <Servo.h>

const int buttonPin = 2;
const int servoPin = 9;
const unsigned long gateOpenDuration = 250; // ms to hold gate open

Servo myServo;

int lastButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(0);

  pinMode(buttonPin, INPUT_PULLUP);
  Serial.println("Gate control ready. Press button to open.");
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  // Detect button press (HIGH to LOW edge)
  if (buttonState == LOW && lastButtonState == HIGH) {
    Serial.println("GATE OPEN");
    myServo.write(45);
    delay(gateOpenDuration);
    myServo.write(0);
    Serial.println("GATE CLOSED");
    delay(200); // Debounce
  }

  lastButtonState = buttonState;
}
