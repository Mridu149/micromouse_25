//#include "config.h"
//#include "motors.h"
//#include "sensors.h"
//#include "encoders.h"
//
//Motor motorL, motorR;
//Encoders encoders;
//IRSensor sensors;
//
//// SETUP CODE WILL GO HERE
//// WILL RUN ONCE ON POWER
//void setup(){
//
//  Serial.begin(9600);
//  
//  motorL.init( MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, false,MOTOR_FREQUENCY, MOTOR_RESOLUTION );
//  motorR.init( MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2, false,MOTOR_FREQUENCY, MOTOR_RESOLUTION );
//
//  encoders.init();
////  sensors.init();
//
//  motorL.stop();
//  motorR.stop();
//
//}
//
//
////// LOOP CODE WILL GO HERE
////// WILL RUN CONTINIOSLY
//void loop(){
//
//  motorL.move(80);
//  motorR.move(80);
//
//  Serial.println("=====TEST SEQUENCE STARTS====="); 
//  Serial.println();
////  Serial.println("=====IR SENSOR READINGS=====");
////  Serial.print("FRONT: ");
////  Serial.println(sensors.getFirstSensorReading());
////  Serial.print("RIGHT: ");
////  Serial.println(sensors.getSecondSensorReading());
////  Serial.print("LEFT: ");
////  Serial.println(sensors.getThirdSensorReading());
//  Serial.println("=====ENCODER READINGS=====");
//  Serial.print("LEFT ENC: ");
//  Serial.println(encoders.getLeftCount());
//  Serial.print("RIGHT ENC: ");
//  Serial.println(encoders.getRightCount());
//  Serial.println();
//  Serial.println("=====TEST SEQUENCE ENDS=====");
//  delay(2000);
//}
