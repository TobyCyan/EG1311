#ifndef WHEELS_H
#define WHEELS_H

class Wheels {
public:
  void setup();

  // Positive: forward. Negative: reverse. Zero: coast.
  void move(int speed);
  void brake();
  void stop();

private:
  void setMotor(
    int speedPin,
    int in1Pin,
    int in2Pin,
    bool flipped,
    int speed
  );
};

#endif
