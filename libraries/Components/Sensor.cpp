#include "Sensor.h"
#include <Arduino.h>

namespace {
  const int TRIG_PIN = 13;
  const int ECHO_PIN = 12;

  const float SPEED_OF_SOUND = 0.0343; // cm per microsecond
  const unsigned long ECHO_TIMEOUT_US = 25000;
  const unsigned long READ_INTERVAL_MS = 40;
}

const float Sensor::OFFSET_CM = 4.0;
const float Sensor::NO_ECHO_CM = 999.0;

void Sensor::setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  clearReadings();
}

float Sensor::readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long echoTime =
    pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT_US);

  if (echoTime == 0) {
    return NO_ECHO_CM;
  }

  return echoTime * SPEED_OF_SOUND / 2.0;
}

float Sensor::distanceAhead() {
  unsigned long now = millis();

  if (now - lastReadTime >= READ_INTERVAL_MS) {
    lastReadTime = now;

    readings[readingIndex] = readDistance();
    readingIndex = (readingIndex + 1) % 3;
  }

  float distance = medianOfThree(
    readings[0],
    readings[1],
    readings[2]
  );

  return distance - OFFSET_CM;
}

void Sensor::clearReadings() {
  for (int i = 0; i < 3; i++) {
    readings[i] = NO_ECHO_CM;
  }

  readingIndex = 0;
}

float Sensor::medianOfThree(float a, float b, float c) {
  if ((a <= b && b <= c) || (c <= b && b <= a)) {
    return b;
  }

  if ((b <= a && a <= c) || (c <= a && a <= b)) {
    return a;
  }

  return c;
}
