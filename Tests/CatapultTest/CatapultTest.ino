#include <Catapult.h>

Catapult catapult;

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
