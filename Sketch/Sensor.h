#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
public:
  static const float OFFSET_CM;
  static const float NO_ECHO_CM;

  void setup();

  // Raw distance measured from the sensor.
  float readDistance();

  // Filtered distance measured from the robot's front.
  float distanceAhead();

  void clearReadings();

private:
  float readings[3];
  int readingIndex = 0;
  unsigned long lastReadTime = 0;

  float medianOfThree(float a, float b, float c);
};

#endif
