#include "Wheels.h"
#include "Sensor.h"
#include "Catapult.h"

Wheels wheels;
Sensor sensor;
Catapult catapult;

// 0: Full run
// 1: Sensor test (Serial Monitor at 115200)
// 2: Motor test
// 3: Catapult test
const int MODE = 0;

// Motor speeds: 0 to 255
const int FAST_SPEED = 255;
const int SLOW_SPEED = 150;
const int REVERSE_SPEED = 255;

// Distances measured from the front of the robot
const float STOP_DISTANCE_CM = 3.5;
const float SLOW_DISTANCE_CM = 35.0;
const float HOME_DISTANCE_CM = 150.0;

// Timing
const unsigned long IGNORE_SENSOR_MS = 2000;
const unsigned long MAX_DRIVE_MS = 12000;
const unsigned long MIN_REVERSE_MS = 4000;
const unsigned long MAX_REVERSE_MS = 9000;
const unsigned long THROW_WAIT_MS = 700;
const unsigned long TIME_LIMIT_MS = 28000;

enum State {
  WAIT_FOR_HAND,
  WAIT_FOR_HAND_AWAY,
  DRIVE_TO_WALL,
  THROW_BALL,
  RETURN_HOME,
  DONE
};

// Explicit declaration for Arduino's automatic function prototypes.
void changeState(State next);

State state = WAIT_FOR_HAND;

unsigned long runStart = 0;
unsigned long stateStart = 0;
unsigned long handSeenSince = 0;

void changeState(State next) {
  state = next;
  stateStart = millis();
}

void brakeAndStop() {
  wheels.brake();
  delay(300);
  wheels.stop();
}

void setup() {
  Serial.begin(115200);

  wheels.setup();
  sensor.setup();
  catapult.setup();

  Serial.println(F("Ready. Hold a hand near the sensor, then remove it."));
}

void runCourse() {
  float distance = sensor.distanceAhead();
  unsigned long now = millis();
  unsigned long elapsed = now - stateStart;

  bool running =
    state == DRIVE_TO_WALL ||
    state == THROW_BALL ||
    state == RETURN_HOME;

  if (running && now - runStart >= TIME_LIMIT_MS) {
    wheels.stop();
    changeState(DONE);
    Serial.println(F("Time limit reached."));
    return;
  }

  switch (state) {
    case WAIT_FOR_HAND: {
      // Hand detection uses distance from the sensor, not the robot front.
      float handDistance = distance + Sensor::OFFSET_CM;

      if (handDistance < 10.0) {
        if (handSeenSince == 0) {
          handSeenSince = now;
        }

        if (now - handSeenSince >= 500) {
          changeState(WAIT_FOR_HAND_AWAY);
          Serial.println(F("Hand detected. Remove it to start."));
        }
      } else {
        handSeenSince = 0;
      }
      break;
    }

    case WAIT_FOR_HAND_AWAY:
      if (distance + Sensor::OFFSET_CM > 20.0) {
        delay(1000);
        sensor.clearReadings();

        runStart = millis();
        changeState(DRIVE_TO_WALL);

        Serial.println(F("Go."));
      }
      break;

    case DRIVE_TO_WALL: {
      bool checkingWall = elapsed >= IGNORE_SENSOR_MS;

      if (checkingWall && distance <= STOP_DISTANCE_CM) {
        brakeAndStop();
        changeState(THROW_BALL);
        Serial.println(F("Wall reached."));
      } else if (elapsed >= MAX_DRIVE_MS) {
        wheels.stop();
        changeState(THROW_BALL);
        Serial.println(F("Drive timeout. Throwing anyway."));
      } else if (checkingWall && distance < SLOW_DISTANCE_CM) {
        wheels.move(SLOW_SPEED);
      } else {
        wheels.move(FAST_SPEED);
      }
      break;
    }

    case THROW_BALL:
      catapult.fire();
      delay(THROW_WAIT_MS);
      catapult.detach();

      sensor.clearReadings();
      changeState(RETURN_HOME);
      break;

    case RETURN_HOME: {
      bool validDistance = distance < Sensor::NO_ECHO_CM - 50.0;
      bool reachedHome =
        elapsed >= MIN_REVERSE_MS &&
        validDistance &&
        distance > HOME_DISTANCE_CM;

      if (reachedHome || elapsed >= MAX_REVERSE_MS) {
        brakeAndStop();
        changeState(DONE);
        Serial.println(F("Return complete."));
      } else {
        wheels.move(-REVERSE_SPEED);
      }
      break;
    }

    case DONE:
      wheels.stop();
      break;
  }
}

void loop() {
  switch (MODE) {
    case 0:
      runCourse();
      break;

    case 1:
      Serial.println(sensor.readDistance());
      delay(200);
      break;

    case 2:
      wheels.move(FAST_SPEED);
      delay(1000);

      wheels.stop();
      delay(1000);

      wheels.move(-FAST_SPEED);
      delay(1000);

      wheels.stop();
      delay(1000);
      break;

    case 3:
      catapult.rest();
      delay(4000);

      catapult.fire();
      delay(1500);
      break;
  }
}
