#include <Wheels.h>

Wheels wheels;

const int FAST_SPEED = 255;

void setup() {
  wheels.setup();
  
  Serial.begin(115200);
}

void loop() {
    wheels.move(FAST_SPEED);
    delay(1000);

    wheels.stop();
    delay(1000);

    wheels.move(-FAST_SPEED);
    delay(1000);

    wheels.stop();
    delay(1000);
}
