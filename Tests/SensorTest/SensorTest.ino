#include <Sensor.h>

Sensor sensor;

void setup() {
  sensor.setup();
  
  Serial.begin(115200);
}

void loop() {
    Serial.println(sensor.readDistance());
    delay(200);
}
