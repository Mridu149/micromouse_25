#ifndef MOTION_H
#define MOTION_H

#include <Arduino.h>
#include "motors.h"
#include "encoders.h"
#include "config.h"  
// #include "logging.h"

const long ticks = 3100;   // Target encoder ticks to travel

// Distance PID (only loop now)
float Kp_bal = 0.34;   // tune this (start small)
float kp_dist = 0.002;
// float Ki_dist = 0.0;
// float Kd_dist = 0.01;

// Motor duty cycle settings (0–100)
int minPWM = 70;   // below this, motor stalls
int maxPWM = 95;  // max duty cycle

// ===============================================

long startTicksL = 0;
long startTicksR = 0;

extern Motor motorL, motorR;
extern Encoder encoders;

// PID variables
// long prevErrorDist = 0;
// float distIntegral = 0;

long err_bal=0;
long err_dist=0;
int baseSpeed = 80;

int leftPwm  = baseSpeed;
int rightPwm = baseSpeed;
long avgticks = 0;

int p_err_bal = 0;
int p_err_dist = 0;

void moveOneCell(){
  p_err_bal = 0;
  p_err_dist = 0;
  delay(10);

  // Record start positions
  startTicksL = encoders.currentLeftCount();
  startTicksR = encoders.currentRightCount();

  Serial.print("Start Left : ");
  Serial.println(startTicksL);
  Serial.print("Start Right: ");
  Serial.println(startTicksR);

  // Start moving
  motorL.move(baseSpeed);  // temp speed until PID takes over
  motorR.move(baseSpeed);

  while (true) {
    long leftTicks  = encoders.currentLeftCount() - startTicksL;
    long rightTicks = encoders.currentRightCount() - startTicksR;

    err_bal = leftTicks - rightTicks;
    avgticks = (leftTicks+rightTicks)/2;
    err_dist = ticks - avgticks;
    p_err_dist = kp_dist*err_dist;


    rightPwm = baseSpeed + p_err_dist + err_bal*Kp_bal;
    leftPwm =  baseSpeed + p_err_dist - err_bal*Kp_bal;
    // if(err_bal > 0){
    //   rightPwm = baseSpeed + p_err_dist + err_bal*Kp_bal;
    //   leftPwm =  baseSpeed + p_err_dist - err_bal*Kp_bal;
    // }
    // else if(err_bal < 0){
    //   rightPwm = baseSpeed + p_err_dist - abs(err_bal*Kp_bal);
    //   leftPwm = baseSpeed + p_err_dist + abs(err_bal*Kp_bal);
    // }else{
    //   rightPwm = baseSpeed;
    //   leftPwm = baseSpeed;
    // }

    // Deadband handling
    if (leftPwm < minPWM && leftPwm > 0) leftPwm = minPWM;
    if (rightPwm < minPWM && rightPwm > 0) rightPwm = minPWM;

    // Clamp to [0,100]
    leftPwm  = constrain(leftPwm, 0, maxPWM);
    rightPwm = constrain(rightPwm, 0, maxPWM);

    motorL.move(leftPwm);
    motorR.move(rightPwm);

    // Debug print
    Serial.print("L: ");
    Serial.print(leftTicks);
    Serial.print("  R: ");
    Serial.print(rightTicks);
    Serial.print("  Left PWM: ");
    Serial.print(leftPwm);
    Serial.print("  Right PWM: ");
    Serial.print(rightPwm);
    Serial.print("  Err Heading: ");
    Serial.print(err_bal);
    Serial.print("  Err Dist: ");
    Serial.println(err_dist);

    // ---- Stop condition ----
    if (avgticks >= ticks) { // average reached target
      motorL.brake();
      motorR.brake();
      break;
    }

    delay(10); // small update delay
  }

  // Done
  Serial.print("Final Left : ");
  Serial.println(encoders.currentLeftCount());
  Serial.print("Final Right: ");
  Serial.println(encoders.currentRightCount());

  // delay(2000);
  // encoders.resetValuesToZero();
}

void turnLeft90PID() {
  encoders.resetValuesToZero();
  Serial.println("============ TURNING LEFT with PID =======");

  int baseSpeed = 80;
  long targetTicks = TICKS_90_DEGREES_LEFT;

  long startL = encoders.currentLeftCount();
  long startR = encoders.currentRightCount();

  // PID gains (tune these)
  float Kp_rot = 0.003;   // distance to target
  float Kp_bal = 0.3;     // balance left vs right

  while (true) {
    long leftTicks  = encoders.currentLeftCount() - startL;
    long rightTicks = encoders.currentRightCount() - startR;

    long rotation = (abs(leftTicks) + abs(rightTicks)) / 2;
    long err_rot  = targetTicks - rotation;              // progress error
    long err_bal  = abs(leftTicks) - abs(rightTicks);    // balance error

    if (err_rot <= 0) {
      motorL.brake();
      motorR.brake();
      break;
    }

    // PID proportional terms
    int p_err_rot = (int)(Kp_rot * err_rot);
    int p_err_bal = (int)(Kp_bal * err_bal);

    // Compute PWM outputs
    int leftPWM  = -(baseSpeed + p_err_rot - p_err_bal); // negative = backward
    int rightPWM =  (baseSpeed + p_err_rot + p_err_bal); // positive = forward

    // Deadband handling
    if (abs(leftPWM) < minPWM)  leftPWM  = (leftPWM < 0) ? -minPWM : minPWM;
    if (abs(rightPWM) < minPWM) rightPWM = (rightPWM < 0) ? -minPWM : minPWM;

    // Clamp
    leftPWM  = constrain(leftPWM, -maxPWM, maxPWM);
    rightPWM = constrain(rightPWM, -maxPWM, maxPWM);

    // Drive motors
    motorL.move(leftPWM);
    motorR.move(rightPWM);

    // Debug
    Serial.print("L: "); Serial.print(leftTicks);
    Serial.print(" R: "); Serial.print(rightTicks);
    Serial.print(" RotErr: "); Serial.print(err_rot);
    Serial.print(" BalErr: "); Serial.print(err_bal);
    Serial.print(" Lpwm: "); Serial.print(leftPWM);
    Serial.print(" Rpwm: "); Serial.println(rightPWM);

    delay(10);
  }

  encoders.resetValuesToZero();
}


void turnRight90PID() {
  encoders.resetValuesToZero();
  Serial.println("============ TURNING RIGHT with PID =======");

  int baseSpeed = 80;
  long targetTicks = TICKS_90_DEGREES_RIGHT;

  long startL = encoders.currentLeftCount();
  long startR = encoders.currentRightCount();

  float Kp_rot = 0.003;
  float Kp_bal = 0.3;

  while (true) {
    long leftTicks  = encoders.currentLeftCount() - startL;
    long rightTicks = encoders.currentRightCount() - startR;

    long rotation = (abs(leftTicks) + abs(rightTicks)) / 2;
    long err_rot  = targetTicks - rotation;
    long err_bal  = abs(leftTicks) - abs(rightTicks);

    if (err_rot <= 0) {
      motorL.brake();
      motorR.brake();
      break;
    }

    int p_err_rot = (int)(Kp_rot * err_rot);
    int p_err_bal = (int)(Kp_bal * err_bal);

    int leftPWM  =  (baseSpeed + p_err_rot - p_err_bal); // left forward
    int rightPWM = -(baseSpeed + p_err_rot + p_err_bal); // right backward

    if (abs(leftPWM) < minPWM)  leftPWM  = (leftPWM < 0) ? -minPWM : minPWM;
    if (abs(rightPWM) < minPWM) rightPWM = (rightPWM < 0) ? -minPWM : minPWM;

    leftPWM  = constrain(leftPWM, -maxPWM, maxPWM);
    rightPWM = constrain(rightPWM, -maxPWM, maxPWM);

    motorL.move(leftPWM);
    motorR.move(rightPWM);

    Serial.print("L: "); Serial.print(leftTicks);
    Serial.print(" R: "); Serial.print(rightTicks);
    Serial.print(" RotErr: "); Serial.print(err_rot);
    Serial.print(" BalErr: "); Serial.print(err_bal);
    Serial.print(" Lpwm: "); Serial.print(leftPWM);
    Serial.print(" Rpwm: "); Serial.println(rightPWM);

    delay(10);
  }

  encoders.resetValuesToZero();
}


void turn180PID() {
  encoders.resetValuesToZero();
  Serial.println("============ TURNING 180 with PID =======");

  int baseSpeed = 80;
  long targetTicks = TICKS_180_DEGREES;

  long startL = encoders.currentLeftCount();
  long startR = encoders.currentRightCount();

  float Kp_rot = 0.003;
  float Kp_bal = 0.3;

  while (true) {
    long leftTicks  = encoders.currentLeftCount() - startL;
    long rightTicks = encoders.currentRightCount() - startR;

    long rotation = (abs(leftTicks) + abs(rightTicks)) / 2;
    long err_rot  = targetTicks - rotation;
    long err_bal  = abs(leftTicks) - abs(rightTicks);

    if (err_rot <= 0) {
      motorL.brake();
      motorR.brake();
      break;
    }

    int p_err_rot = (int)(Kp_rot * err_rot);
    int p_err_bal = (int)(Kp_bal * err_bal);

    int leftPWM  =  (baseSpeed + p_err_rot - p_err_bal); // left forward
    int rightPWM = -(baseSpeed + p_err_rot + p_err_bal); // right backward

    if (abs(leftPWM) < minPWM)  leftPWM  = (leftPWM < 0) ? -minPWM : minPWM;
    if (abs(rightPWM) < minPWM) rightPWM = (rightPWM < 0) ? -minPWM : minPWM;

    leftPWM  = constrain(leftPWM, -maxPWM, maxPWM);
    rightPWM = constrain(rightPWM, -maxPWM, maxPWM);

    motorL.move(leftPWM);
    motorR.move(rightPWM);

    Serial.print("L: "); Serial.print(leftTicks);
    Serial.print(" R: "); Serial.print(rightTicks);
    Serial.print(" RotErr: "); Serial.print(err_rot);
    Serial.print(" BalErr: "); Serial.print(err_bal);
    Serial.print(" Lpwm: "); Serial.print(leftPWM);
    Serial.print(" Rpwm: "); Serial.println(rightPWM);

    delay(10);
  }

  encoders.resetValuesToZero();
}

#endif
