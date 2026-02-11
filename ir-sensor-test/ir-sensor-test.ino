#include <Servo.h>

const int irReceiverPin = A0; // Analog pin for IR receiver
const int irLedPin = 7;       // Digital pin for IR LED
const int threshold = 300;    // Adjust this based on serial readings

void setup() {
  Serial.begin(9600);
  pinMode(irLedPin, OUTPUT);
  digitalWrite(irLedPin, HIGH); // IR LED always on

  Serial.println("IR beam-break sensor ready.");
  Serial.println("Watch the analog value — it drops when the beam is broken.");
}

void loop() {
  int sensorValue = analogRead(irReceiverPin);

  Serial.print("IR: ");
  Serial.print(sensorValue);

  if (sensorValue < threshold) {
    Serial.println(" — BEAM BROKEN (tab detected!)");
  } else {
    Serial.println();
  }

  delay(50);
}
