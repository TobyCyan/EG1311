#ifndef CATAPULT_H
#define CATAPULT_H

#include <Servo.h>

class Catapult {
  public:
    void setup();
    void fire();

  private:
    void rest();

    Servo servo;
};

#endif
