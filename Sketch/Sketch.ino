#include<Servo.h>

// Wheels
const int LEFT_MOTOR_PIN = 6;
const int RIGHT_MOTOR_PIN = 5;
const int FRONT_MOTOR_PIN = 3;
const int MOTOR_SPEED = 210;

// Sensor
const int TRIG_PIN = 13;
const int ECHO_PIN = 12;
const float SPEED_OF_SOUND = 0.0345;
const int CLOSE_READINGS_REQUIRED = 3;
const int MAX_INVALID_READINGS = 5;
const float STOP_DISTANCE_CM = 12.0;
int closeReadingCount = 0;

// Catapult
Servo cServo;
const int SERVO_PIN = 9;
const int REST_ANGLE = 0;
const int LAUNCH_ANGLE = 180;
bool launched = false;

void setup() {
  setupWheels();

  setupSensor();

  setupCatapult();

  Serial.begin(9600);
}

void loop() {
  if (launched) {
    stop();
    delay(50);
    return;
  }

  if (isCloseToObstacle()) {
    stop();
    closeReadingCount++;
    if (closeReadingCount >= CLOSE_READINGS_REQUIRED) {
      delay(250);
      fireCatapult();
      launched = true;
    }
  } else {
    closeReadingCount = 0;
    move();
  }
  delay(60);
}

void move() {
  analogWrite(LEFT_MOTOR_PIN, MOTOR_SPEED);
  analogWrite(RIGHT_MOTOR_PIN, MOTOR_SPEED);
  analogWrite(FRONT_MOTOR_PIN, MOTOR_SPEED);
}

void stop() {
  analogWrite(LEFT_MOTOR_PIN, 0);
  analogWrite(RIGHT_MOTOR_PIN, 0);
  analogWrite(FRONT_MOTOR_PIN, 0);
}

void setupWheels() {
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
  pinMode(FRONT_MOTOR_PIN, OUTPUT);
  stop();
}

void setupSensor() {
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
}

void setupCatapult() {
  cServo.attach(SERVO_PIN);
  restCatapult();
}

void fireCatapult() {
  cServo.write(LAUNCH_ANGLE);
}

void restCatapult() {
  cServo.write(REST_ANGLE);
}

bool isCloseToObstacle() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int microsecs = pulseIn(ECHO_PIN, HIGH);
  float cms = microsecs * SPEED_OF_SOUND / 2;
  Serial.println(cms);
  return cms > 0 && cms < STOP_DISTANCE_CM;
}
