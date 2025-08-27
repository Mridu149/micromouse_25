#ifndef MOTION_H
#define MOTION_H

#include <Arduino.h>
#include "motors.h"
#include "encoders.h"

// ================== SETTINGS ==================
const long ticksPerCell = 1700;   // ticks for 1 cell (same as your `ticks` earlier)

// Distance PID (only loop now)
float Kp_bal = 0.048;   // tune this (start small)
float kp_dist = 0.002;

// Motor duty cycle settings (0–100)
int minPWM = 60;   // below this, motor stalls
int maxPWM = 95;   // max duty cycle

// ===============================================

extern Motor motorL, motorR;
extern Encoder encoders;

// ---------------- MOVE FUNCTION ----------------
void moveNcells(int n) {
  long startTicksL = 0;
  long startTicksR = 0;

  long err_bal = 0;
  long err_dist = 0;
  int baseSpeed = 80;

  int leftPwm  = baseSpeed;
  int rightPwm = baseSpeed;
  long avgticks = 0;

  int p_err_dist = 0;

  delay(2000);

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

  long targetTicks = n * ticksPerCell;

  while (true) {
    long leftTicks  = encoders.currentLeftCount() - startTicksL;
    long rightTicks = encoders.currentRightCount() - startTicksR;

    err_bal = leftTicks - rightTicks;
    avgticks = (leftTicks + rightTicks) / 2;
    err_dist = targetTicks - avgticks;
    p_err_dist = kp_dist * err_dist;

    if (err_bal > 0) {
      rightPwm = baseSpeed + p_err_dist + err_bal * Kp_bal;
      leftPwm  = baseSpeed + p_err_dist - err_bal * Kp_bal;
    }
    else if (err_bal < 0) {
      rightPwm = baseSpeed + p_err_dist - abs(err_bal * Kp_bal);
      leftPwm  = baseSpeed + p_err_dist + abs(err_bal * Kp_bal);
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
    if (avgticks >= targetTicks) {
      motorL.stop();
      motorR.stop();
      break;
    }

    delay(10); // small update delay
  }

  // Done
  Serial.print("Final Left : ");
  Serial.println(encoders.currentLeftCount());
  Serial.print("Final Right: ");
  Serial.println(encoders.currentRightCount());

  delay(2000);
  encoders.resetValuesToZero();
}

#endif
