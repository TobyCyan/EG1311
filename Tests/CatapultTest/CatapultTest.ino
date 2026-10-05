#include <Catapult.h>

Catapult catapult;

const int FAST_SPEED = 255;

void setup() {
  catapult.setup();
  
  Serial.begin(115200);
}

void loop() {
    catapult.rest();
    delay(4000);

    catapult.fire();
    delay(1500);
}
