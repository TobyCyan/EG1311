#ifndef CATAPULT_H
#define CATAPULT_H

#include <Servo.h>

class Catapult {
public:
  void setup();
  void fire();
  void rest();
  void detach();

private:
  Servo servo;
};

#endif
