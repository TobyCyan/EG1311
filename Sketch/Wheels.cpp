#include "Wheels.h"
#include <Arduino.h>

namespace {
  const int LEFT_MOTOR_PIN = 6;
    const int RIGHT_MOTOR_PIN = 5;
    const int FRONT_MOTOR_PIN = 3;
    const int MOTOR_SPEED = 210;
}

void Wheels::move() {
  analogWrite(LEFT_MOTOR_PIN, MOTOR_SPEED);
  analogWrite(RIGHT_MOTOR_PIN, MOTOR_SPEED);
  analogWrite(FRONT_MOTOR_PIN, MOTOR_SPEED);
}

void Wheels::stop() {
  analogWrite(LEFT_MOTOR_PIN, 0);
  analogWrite(RIGHT_MOTOR_PIN, 0);
  analogWrite(FRONT_MOTOR_PIN, 0);
}

void Wheels::setup() {
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
  pinMode(FRONT_MOTOR_PIN, OUTPUT);
  stop();
}
