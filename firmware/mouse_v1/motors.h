#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>

class Motor {
  private:
    uint8_t in1Pin;
    uint8_t in2Pin;
    bool dirSwap;
    uint8_t resolution;
    uint32_t pwmFreq;

  public:
    Motor() {
      in1Pin = 0;
      in2Pin = 0;
      dirSwap = false;
      resolution = 10;   // default 10-bit (0-1023)
      pwmFreq = 5000;    // default 5kHz
    }

    bool init(uint8_t in1, uint8_t in2, bool swap = false, uint32_t freq = 5000, uint8_t res = 10) {
      in1Pin = in1;
      in2Pin = in2;
      dirSwap = swap;
      pwmFreq = freq;
      resolution = res;

      // attach both pins as PWM channels
      if (!ledcAttach(in1Pin, pwmFreq, resolution)) return false;
      if (!ledcAttach(in2Pin, pwmFreq, resolution)) return false;

      // start with motor off
      ledcWrite(in1Pin, 0);
      ledcWrite(in2Pin, 0);
      return true;
    }

    void move(int8_t power) {
      // constrain range -100..100
      power = constrain(power, -100, 100);

      // scale power to duty
      uint32_t maxDuty = (1 << resolution) - 1;
      uint32_t duty = map(abs(power), 0, 100, 0, maxDuty);

      // apply direction swap if needed
      bool forward = (power >= 0);
      if (dirSwap) forward = !forward;

      if (power == 0) {
        stop();
      } else if (forward) {
        ledcWrite(in1Pin, duty);
        ledcWrite(in2Pin, 0);
      } else {
        ledcWrite(in1Pin, 0);
        ledcWrite(in2Pin, duty);
      }
    }

    void stop() {
      // fast decay = free run
      ledcWrite(in1Pin, 0);
      ledcWrite(in2Pin, 0);
    }

    void brake() {
      // slow decay = both pins high
      uint32_t maxDuty = (1 << resolution) - 1;
      ledcWrite(in1Pin, maxDuty);
      ledcWrite(in2Pin, maxDuty);
    }

    void setFrequency(uint32_t freq, uint8_t res = 10) {
      pwmFreq = freq;
      resolution = res;
      ledcChangeFrequency(in1Pin, pwmFreq, resolution);
      ledcChangeFrequency(in2Pin, pwmFreq, resolution);
    }

    void swapDirection(bool swap) {
      dirSwap = swap;
    }
};

#endif
