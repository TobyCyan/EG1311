#include "Catapult.h"

namespace {
  const int SERVO_PIN = 9;
  const int REST_ANGLE = 0;
  const int LAUNCH_ANGLE = 70;
}

void Catapult::setup() {
  servo.attach(SERVO_PIN);
  rest();
}

void Catapult::fire() {
  servo.write(LAUNCH_ANGLE);
}

void Catapult::rest() {
  servo.write(REST_ANGLE);
}
