//#include "config.h"
//#include "motors.h"
//#include "sensors.h"
//#include "encoders.h"
//#include "logging.h"
//
//
//Motor motorL, motorR;
//Encoder encoders;
//IRSensor sensors;
//
//// SETUP CODE WILL GO HERE
//// WILL RUN ONCE ON POWER
//void setup(){
//  
//  motorL.init( MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, false,MOTOR_FREQUENCY, MOTOR_RESOLUTION );
//  motorR.init( MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2, false,MOTOR_FREQUENCY, MOTOR_RESOLUTION );
//
//  encoders.init();
//
//  sensors.init();
//
//  motorL.stop();
//  motorR.stop();
//
//}
//
//
//// LOOP CODE WILL GO HERE
//// WILL RUN CONTINIOSLY
//void loop(){
//
//  SerialBT.println("=====TEST SEQUENCE STARTS====="); 
//  SerialBT.println();
//  SerialBT.println("=====IR SENSOR READINGS=====");
//  SerialBT.print("FRONT: ");
//  SerialBT.println(sensors.getFrontSensorReading());
//  SerialBT.print("RIGHT: ");
//  SerialBT.println(sensors.getLeftSensorReading());
//  SerialBT.print("LEFT: ");
//  SerialBT.println(sensors.getRightSensorReading());
//
//  SerialBT.println("=====ENCODER READINGS=====");
//  SerialBT.print("LEFT ENC: ");
//  SerialBT.println(encoders.currentLeftCount());
//  SerialBT.print("RIGHT ENC: ");
//  SerialBT.println(encoders.currentRightCount());
//  SerialBT.println();
//  SerialBT.println("=====TEST SEQUENCE ENDS=====");
//
//  // Forward USB serial to Bluetooth and vice versa
//  if (Serial.available()) {
//    SerialBT.write(Serial.read());
//  }
//  if (SerialBT.available()) {
//    Serial.write(SerialBT.read());
//  }
//
////  Serial.println("=====TEST SEQUENCE STARTS====="); 
////  Serial.println();
////  Serial.println("=====IR SENSOR READINGS=====");
////  Serial.print("FRONT: ");
////  Serial.println(sensors.getFrontSensorReading());
////  Serial.print("RIGHT: ");
////  Serial.println(sensors.getLeftSensorReading());
////  Serial.print("LEFT: ");
////  Serial.println(sensors.getRightSensorReading());
////
////  Serial.println("=====ENCODER READINGS=====");
////  Serial.print("LEFT ENC: ");
////  Serial.println(encoders.currentLeftCount());
////  Serial.print("RIGHT ENC: ");
////  Serial.println(encoders.currentRightCount());
////  Serial.println();
////  Serial.println("=====TEST SEQUENCE ENDS=====");
//  delay(1000);
//}
