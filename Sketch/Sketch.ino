#include<Servo.h>

// Wheels
const int LEFT_MOTOR_PIN = 6;
const int RIGHT_MOTOR_PIN = 5
const FRONT_MOTOR_PIN = 3;
const int MOTOR_SPEED = 210;

// Sensor
const int TRIG_PIN = 13;
const int ECHO_PIN = 12;
const float SPEED_OF_SOUND = 0.0345
const int CLOSE_READINGS_REQUIRED = 3;
const int MAX_INVALID_READINGS = 5;
const float STOP_DISTANCE_CM = 7.0;

// Catapult
Servo catapultServo;
const int SERVO_PIN = 9;
const int READY_ANGLE = 20;
const int LAUNCH_ANGLE = 130;

void setup() {
  setupWheels();

  setupSensor();

  setupCatapult();

  Serial.begin (9600);
}

void loop() {
  
}

void moveForward() {
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
  catapultServo.attach(SERVO_PIN);
  catapultServo.write(READY_ANGLE);
}
