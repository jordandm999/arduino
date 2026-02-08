#include <Servo.h>

const int buttonPin = 2;
const int servoPin = 9;

Servo myServo;

int lastButtonState = HIGH;
bool gateOpen = false;
unsigned long startTime = 0;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(0);  // Start closed
  
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.println("Manual gate control ready.");
  Serial.println("Press 1: OPEN (logs start time)");
  Serial.println("Press 2: CLOSE (logs duration)");
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  
  // Detect button press (HIGH to LOW edge)
  if (buttonState == LOW && lastButtonState == HIGH) {
    if (!gateOpen) {
      // OPEN
      startTime = millis();
      Serial.print("GATE OPEN at: ");
      Serial.print(startTime);
      Serial.println(" ms");
      myServo.write(90);
      gateOpen = true;
    } else {
      // CLOSE
      unsigned long endTime = millis();
      unsigned long duration = endTime - startTime;
      Serial.print("GATE CLOSED at: ");
      Serial.print(endTime);
      Serial.print(" ms (TOTAL: ");
      Serial.print(duration);
      Serial.println(" ms)");
      myServo.write(0);
      gateOpen = false;
    }
    delay(200);  // Debounce for clean presses
  }
  
  lastButtonState = buttonState;
}
