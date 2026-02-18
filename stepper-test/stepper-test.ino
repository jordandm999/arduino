#include <Stepper.h>

// 28BYJ-48 has 2048 steps per full revolution in half-step mode.
// The Arduino Stepper library uses full steps, so 2048/2 = 1024 steps/rev.
const int STEPS_PER_REV = 2048;
const int QUARTER_TURN   = STEPS_PER_REV / 4; // 512 steps

// ULN2003 driver board pins (IN1, IN2, IN3, IN4)
// Wire these to any four digital output pins.
const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

const int buttonPin = 2;

// Medium speed: ~10 RPM (max reliable for 28BYJ-48 is ~15 RPM)
const int MOTOR_RPM = 10;

// Debounce
const unsigned long DEBOUNCE_MS = 50;

Stepper motor(STEPS_PER_REV, IN1, IN3, IN2, IN4); // pin order matters for correct step sequence

bool      motorBusy       = false;
bool      lastButtonState  = HIGH; // INPUT_PULLUP idles HIGH
unsigned long lastDebounceTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  motor.setSpeed(MOTOR_RPM);
  Serial.println("Stepper test ready. Press button to rotate 1/4 turn.");
}

void loop() {
  if (motorBusy) return; // ignore input while turning

  bool reading = digitalRead(buttonPin);

  // Detect falling edge (HIGH -> LOW = button pressed)
  if (reading == LOW && lastButtonState == HIGH) {
    unsigned long now = millis();
    if (now - lastDebounceTime >= DEBOUNCE_MS) {
      lastDebounceTime = now;
      Serial.println("Button pressed — rotating 1/4 turn.");
      motorBusy = true;
      motor.step(QUARTER_TURN);
      motorBusy = false;
      Serial.println("Done.");
    }
  }

  lastButtonState = reading;
}
