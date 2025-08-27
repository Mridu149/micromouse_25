#include <Arduino.h>
#include "motors.h"
#include "encoders.h"
#include "motion.h"

Motor motorL, motorR;
Encoder encoders;

bool mazeComplete = false;

void setup() {
  Serial.begin(115200);

  // Initialize motors
  motorL.init(MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, false, MOTOR_FREQUENCY, MOTOR_RESOLUTION);
  motorR.init(MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2, false, MOTOR_FREQUENCY, MOTOR_RESOLUTION);

  // Initialize encoders
  encoders.init();

  // Stop motors at start
  motorL.stop();
  motorR.stop();

  encoders.resetValuesToZero();
}

void loop() {
  delay(2000);
  moveOneCell();
  delay(2000);
  turnRight90PID();
  delay(2000);
  moveOneCell();
  delay(2000);
  turnLeft90PID();
  delay(2000);
  moveOneCell();
  delay(2000);
  turn180PID();
  delay(3000);
  // delay(5000);
  // if(!mazeComplete){
  //   moveOneCell();
  //   delay(200);
  //   turnLeft90PID();
  //   delay(200);
  //   moveOneCell();
  //   delay(200);
  //   turnRight90PID();
  //   delay(200);
  //   moveOneCell();
  //   delay(200);
  //   turnLeft90PID();
  //   delay(200);
  //   moveOneCell();
  //   moveOneCell();
  //   delay(200);
  //   turnRight90PID();
  //   delay(200);
  //   moveOneCell();
  // }
  // mazeComplete = true;
}


