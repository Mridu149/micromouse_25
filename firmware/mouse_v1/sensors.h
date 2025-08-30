#ifndef SENSORS_H
#define SENSORS_H

#include "config.h"

#include <Wire.h>
#include <VL53L0X.h>

class IRSensor
{
public:
  void init()
  {
    Wire.begin(21, 22);
    delay(10);
    
    Wire.setClock(100000);  

    sensor1.setBus(&Wire);
    sensor2.setBus(&Wire);   
    sensor3.setBus(&Wire);   

    pinMode(IR_XSHUT_1, OUTPUT);
    pinMode(IR_XSHUT_2, OUTPUT);
    pinMode(IR_XSHUT_3, OUTPUT);

    digitalWrite(IR_XSHUT_1, LOW);
    digitalWrite(IR_XSHUT_2, LOW);
    digitalWrite(IR_XSHUT_3, LOW);
    delay(10);

    digitalWrite(IR_XSHUT_1, HIGH);
    delay(10);
    sensor1.init();
    sensor1.setAddress(0x30);

    digitalWrite(IR_XSHUT_2, HIGH);
    delay(10);
    sensor2.init();
    sensor2.setAddress(0x31);

    digitalWrite(IR_XSHUT_3, HIGH);
    delay(10);
    sensor3.init();
    sensor3.setAddress(0x32);

    sensor1.setMeasurementTimingBudget(20000);
    sensor2.setMeasurementTimingBudget(20000);
    sensor3.setMeasurementTimingBudget(20000);
  }

  uint16_t getFrontSensorReading()
  {
    return (sensor1.readRangeSingleMillimeters() - FRONT_ERROR);
  }

  uint16_t getRightSensorReading()
  {
    return (sensor3.readRangeSingleMillimeters() - RIGHT_ERROR);
  }

  uint16_t getLeftSensorReading()
  {
    return (sensor2.readRangeSingleMillimeters() - LEFT_ERROR);
  }


private:
  VL53L0X sensor1; // FRONT SENSOR OBJECT
  VL53L0X sensor2; // LEFT SENSOR OBJECT
  VL53L0X sensor3; // RIGHT SENSOR OBJECT
};

#endif
