#ifndef ENCODERS_H
#define ENCODERS_H

#include "config.h"
#include <ESP32Encoder.h>

class Encoder
{
public:
  Encoder() : lastLeftCount(0), lastRightCount(0) {}
  ~Encoder() {}

  void init()
  {
    ESP32Encoder::useInternalWeakPullResistors = puType::up;
    encLeft.attachFullQuad(ENCODER_LEFT_CHA, ENCODER_LEFT_CHB);
    encRight.attachFullQuad(ENCODER_RIGHT_CHA, ENCODER_RIGHT_CHB);

    resetValuesToZero();
  }

  int64_t currentLeftCount()  { return encLeft.getCount(); }
  int64_t currentRightCount() { return encRight.getCount(); }

  void resetValuesToZero()
  {
    encLeft.setCount(0);
    encRight.setCount(0);
    lastLeftCount = 0;
    lastRightCount = 0;
  }

  void setLeftValue(int64_t value)
  {
    encLeft.setCount(value);
    lastLeftCount = value;
  }

  void setRightValue(int64_t value)
  {
    encRight.setCount(value);
    lastRightCount = value;
  }

  int64_t getLeftChange()
  {
    int64_t cur = encLeft.getCount();
    int64_t delta = cur - lastLeftCount;
    lastLeftCount = cur;
    return delta;
  }

  int64_t getRightChange()
  {
    int64_t cur = encRight.getCount();
    int64_t delta = cur - lastRightCount;
    lastRightCount = cur;
    return delta;
  }

  int getLeftDirection()
  {
    int64_t d = getLeftChange();
    return (d > 0) ? 1 : (d < 0 ? -1 : 0);
  }

  int getRightDirection()
  {
    int64_t d = getRightChange();
    return (d > 0) ? 1 : (d < 0 ? -1 : 0);
  }

private:
  ESP32Encoder encLeft;
  ESP32Encoder encRight;

  int64_t lastLeftCount;
  int64_t lastRightCount;
};

#endif
