#include "Wheels.h"
#include "Sensor.h"
#include "Catapult.h"

Wheels wheels;
Sensor sensor;
Catapult catapult;
bool launched = false;

void setup() {
  Serial.begin(9600);

  wheels.setup();
  sensor.setup();
  catapult.setup();
}

void loop() {
  if (launched) {
    wheels.stop();
    delay(50);
    return;
  }

  if (sensor.isCloseToObstacle()) {
    wheels.stop();
    delay(250);
    catapult.fire();
    launched = true;
  } else {
    wheels.move();
  }
  
  delay(60);
}
