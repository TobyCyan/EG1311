#include "Wheels.h"
#include <Arduino.h>

namespace {
  // Front motor
  const int FRONT_SPEED_PIN = 5;
  const int FRONT_IN1_PIN = 7;
  const int FRONT_IN2_PIN = 8;

  // Rear motor
  const int REAR_SPEED_PIN = 6;
  const int REAR_IN1_PIN = 4;
  const int REAR_IN2_PIN = 2;

  // Flip option without having to rewire the motors
  const bool FLIP_FRONT_MOTOR = false;
  const bool FLIP_REAR_MOTOR = false;
}

void Wheels::setup() {
  pinMode(FRONT_SPEED_PIN, OUTPUT);
  pinMode(FRONT_IN1_PIN, OUTPUT);
  pinMode(FRONT_IN2_PIN, OUTPUT);

  pinMode(REAR_SPEED_PIN, OUTPUT);
  pinMode(REAR_IN1_PIN, OUTPUT);
  pinMode(REAR_IN2_PIN, OUTPUT);

  stop();
}

void Wheels::setMotor(
  int speedPin,
  int in1Pin,
  int in2Pin,
  bool flipped,
  int speed
) {
  speed = constrain(speed, -255, 255);

  if (flipped) {
    speed = -speed;
  }

  digitalWrite(in1Pin, speed > 0 ? HIGH : LOW);
  digitalWrite(in2Pin, speed < 0 ? HIGH : LOW);
  analogWrite(speedPin, abs(speed));
}

void Wheels::move(int speed) {
  setMotor(
    FRONT_SPEED_PIN,
    FRONT_IN1_PIN,
    FRONT_IN2_PIN,
    FLIP_FRONT_MOTOR,
    speed
  );

  setMotor(
    REAR_SPEED_PIN,
    REAR_IN1_PIN,
    REAR_IN2_PIN,
    FLIP_REAR_MOTOR,
    speed
  );
}

void Wheels::brake() {
  // Both direction inputs LOW, with enable HIGH, actively brake.
  digitalWrite(FRONT_IN1_PIN, LOW);
  digitalWrite(FRONT_IN2_PIN, LOW);
  digitalWrite(REAR_IN1_PIN, LOW);
  digitalWrite(REAR_IN2_PIN, LOW);

  analogWrite(FRONT_SPEED_PIN, 255);
  analogWrite(REAR_SPEED_PIN, 255);
}

void Wheels::stop() {
  move(0);
}
