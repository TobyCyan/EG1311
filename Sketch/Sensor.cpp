#include "Sensor.h"
#include <Arduino.h>

namespace {
  const int TRIG_PIN = 13;
  const int ECHO_PIN = 12;
  const float SPEED_OF_SOUND = 0.0345;
  const float STOP_DISTANCE_CM = 12.0;
}

void Sensor::setup() {
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
}

bool Sensor::isCloseToObstacle() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int microsecs = pulseIn(ECHO_PIN, HIGH);
  float cms = microsecs * SPEED_OF_SOUND / 2;
  Serial.println(cms);
  return cms > 0 && cms < STOP_DISTANCE_CM;
}
