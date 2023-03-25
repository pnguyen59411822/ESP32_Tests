#include <Arduino.h>

#define SM_PIN     34

#define SM_IN_MAX     4095
#define SM_IN_MIN     0

#define SM_OUT_MAX    100
#define SM_OUT_MIN    0

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.print(F("\n\n"));

  pinMode(SM_PIN, OUTPUT);
}

void loop() {
  float raw = analogRead(SM_PIN);
  float per = (raw-SM_IN_MIN) / (SM_IN_MAX-SM_IN_MIN) * (SM_OUT_MAX-SM_OUT_MIN) + SM_OUT_MIN;
  Serial.printf("raw: %7.2f | percent: %7.2f\n", raw, per);
  delay(1000);
}