// #include "config.h"
// #include "motors.h"
// #include "sensors.h"
// #include "encoders.h"
// #include "logging.h"
//
//Motor motorL, motorR;
//Encoder encoders;
// IRSensor sensors;
////
////// // SETUP CODE WILL GO HERE
////// // WILL RUN ONCE ON POWER
//void setup(){
////
//Serial.begin(9600);
//// 
//motorL.init( MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, false,MOTOR_FREQUENCY, MOTOR_RESOLUTION );
//motorR.init( MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2, false,MOTOR_FREQUENCY, MOTOR_RESOLUTION );
////
//encoders.init();
//sensors.init();
////
//motorL.stop();
//motorR.stop();
//
//initBluetooth();
////
//}
////
////
////// //// LOOP CODE WILL GO HERE
////// //// WILL RUN CONTINIOSLY
//void loop(){
////
////motorL.move(90);
////motorR.move(90);
////
//SerialBT.println("=====TEST SEQUENCE STARTS====="); 
//SerialBT.println(); 
//SerialBT.println("=====IR SENSOR READINGS=====");
//SerialBT.print("FRONT: ");
//SerialBT.println(sensors.getFrontSensorReading());
//SerialBT.print("RIGHT: ");
//SerialBT.println(sensors.getRightSensorReading());
//SerialBT.print("LEFT: ");
//SerialBT.println(sensors.getLeftSensorReading());
////SerialBT.println("=====ENCODER READINGS=====");
////SerialBT.print("LEFT ENC: ");
////SerialBT.println(encoders.currentLeftCount());
////SerialBT.print("RIGHT ENC: ");
////SerialBT.println(encoders.currentRightCount());
////SerialBT.println();
//SerialBT.println("=====TEST SEQUENCE ENDS=====");
//delay(2000);
//}
