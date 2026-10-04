#include "Catapult.h"

namespace {
  const int SERVO_PIN = 9;
  const int REST_ANGLE = 10;
  const int LAUNCH_ANGLE = 80;
}

void Catapult::setup() {
  rest();
  servo.attach(SERVO_PIN);
}

void Catapult::fire() {
  servo.write(LAUNCH_ANGLE);
}

void Catapult::rest() {
  servo.write(REST_ANGLE);
}

void Catapult::detach() {
  servo.detach();
}
