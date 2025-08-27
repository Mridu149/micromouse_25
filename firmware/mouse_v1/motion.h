#ifndef MOTION_H
#define MOTION_H

#include <Arduino.h>
#include "motors.h"
#include "encoders.h"
#include "config.h"  

int minPWM = 60;  
int maxPWM = 95; 

extern Motor motorL, motorR;
extern Encoder encoders;

void moveNcells(int n) {
  encoders.resetValuesToZero();
  
  long startTicksL = 0;
  long startTicksR = 0;

  long err_bal = 0;
  long err_dist = 0;
  int baseSpeed = 80;

  int leftPwm  = baseSpeed;
  int rightPwm = baseSpeed;
  long avgticks = 0;

  int p_err_dist = 0;

  startTicksL = encoders.currentLeftCount();
  startTicksR = encoders.currentRightCount();

//  Serial.print("Start Left : ");
//  Serial.println(startTicksL);
//  Serial.print("Start Right: ");
//  Serial.println(startTicksR);

  motorL.move(baseSpeed); 
  motorR.move(baseSpeed);

  long targetTicks = n * TICKS_PER_CELL;

  while (true) {
    long leftTicks  = encoders.currentLeftCount() - startTicksL;
    long rightTicks = encoders.currentRightCount() - startTicksR;

    err_bal = leftTicks - rightTicks;
    avgticks = (leftTicks + rightTicks) / 2;
    err_dist = targetTicks - avgticks;
    p_err_dist = KP_DIST * err_dist;

    if (err_bal > 0) {
      rightPwm = baseSpeed + p_err_dist + err_bal * KP_BAL;
      leftPwm  = baseSpeed + p_err_dist - err_bal * KP_BAL;
    }
    else if (err_bal < 0) {
      rightPwm = baseSpeed + p_err_dist - abs(err_bal * KP_BAL);
      leftPwm  = baseSpeed + p_err_dist + abs(err_bal * KP_BAL);
    }
    else {
      rightPwm = baseSpeed;
      leftPwm  = baseSpeed;
    }

    // Deadband handling
    if (leftPwm < minPWM && leftPwm > 0) leftPwm = minPWM;
    if (rightPwm < minPWM && rightPwm > 0) rightPwm = minPWM;

    // Clamp to [0,100]
    leftPwm  = constrain(leftPwm, 0, maxPWM);
    rightPwm = constrain(rightPwm, 0, maxPWM);

    motorL.move(leftPwm);
    motorR.move(rightPwm);

    // Debug print
//    Serial.print("L: ");
//    Serial.print(leftTicks);
//    Serial.print("  R: ");
//    Serial.print(rightTicks);
//    Serial.print("  Left PWM: ");
//    Serial.print(leftPwm);
//    Serial.print("  Right PWM: ");
//    Serial.print(rightPwm);
//    Serial.print("  Err Heading: ");
//    Serial.print(err_bal);
//    Serial.print("  Err Dist: ");
//    Serial.println(err_dist);

    if (avgticks >= targetTicks) {
      motorL.stop();
      motorR.stop();
      break;
    }

    delay(10); // small update delay
  }

  // Done
//  Serial.print("Final Left : ");
//  Serial.println(encoders.currentLeftCount());
//  Serial.print("Final Right: ");
//  Serial.println(encoders.currentRightCount());

  encoders.resetValuesToZero();
}

void turnRight90IP() {
  encoders.resetValuesToZero();

  int baseSpeed = 80;
  long startTicksL = encoders.currentLeftCount();
  long startTicksR = encoders.currentRightCount();

  long targetTicks = TICKS_90_DEGREES;
  
  int leftPwm = baseSpeed;
  int rightPwm = baseSpeed;

  motorL.move(baseSpeed);   // left forward
  motorR.move(-baseSpeed);  // right backward

  while (true) {
    long leftTicks  = encoders.currentLeftCount() - startTicksL;
    long rightTicks = encoders.currentRightCount() - startTicksR;

    long avgTicks = (abs(leftTicks) + abs(rightTicks)) / 2;
    
    long err_turn = targetTicks - avgTicks;
    int p_err_turn = KP_DIST * err_turn;
    
    // Calculate PWM values with P control
    leftPwm = baseSpeed + p_err_turn;
    rightPwm = baseSpeed + p_err_turn;
    
    if (leftPwm < minPWM && leftPwm > 0) leftPwm = minPWM;
    if (rightPwm < minPWM && rightPwm > 0) rightPwm = minPWM;
    
    leftPwm = constrain(leftPwm, 0, maxPWM);
    rightPwm = constrain(rightPwm, 0, maxPWM);
    
    motorL.move(leftPwm);    // left forward
    motorR.move(-rightPwm);  // right backward

    // Stop condition
    if (avgTicks >= targetTicks) {
      motorL.stop();
      motorR.stop();
      break;
    }
    
    delay(10); // small update delay
  }

  encoders.resetValuesToZero();
}

void turnLeft90IP(){
  encoders.resetValuesToZero();

  int baseSpeed = 80;
  long startTicksL = encoders.currentLeftCount();
  long startTicksR = encoders.currentRightCount();

  long targetTicks = TICKS_90_DEGREES;
  
  int leftPwm = baseSpeed;
  int rightPwm = baseSpeed;

  motorL.move(-baseSpeed);  // left backward
  motorR.move(baseSpeed);   // right forward

  while (true) {
    long leftTicks  = encoders.currentLeftCount() - startTicksL;
    long rightTicks = encoders.currentRightCount() - startTicksR;

    long avgTicks = (abs(leftTicks) + abs(rightTicks)) / 2;
    
    // P control for turn distance
    long err_turn = targetTicks - avgTicks;
    int p_err_turn = KP_DIST * err_turn;
    
    // Calculate PWM values with P control
    leftPwm = baseSpeed + p_err_turn;
    rightPwm = baseSpeed + p_err_turn;
    
    // Deadband handling
    if (leftPwm < minPWM && leftPwm > 0) leftPwm = minPWM;
    if (rightPwm < minPWM && rightPwm > 0) rightPwm = minPWM;
    
    // Clamp to valid range
    leftPwm = constrain(leftPwm, 0, maxPWM);
    rightPwm = constrain(rightPwm, 0, maxPWM);
    
    motorL.move(-leftPwm);   // left backward
    motorR.move(rightPwm);   // right forward

    // Stop condition
    if (avgTicks >= targetTicks) {
      motorL.stop();
      motorR.stop();
      break;
    }

    delay(10);
  }

  encoders.resetValuesToZero();
}

void turn180IP(){
  turnRight90IP();
  turnRight90IP();
}

#endif
