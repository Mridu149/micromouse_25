#include <Arduino.h>
#include "motors.h"
#include "encoders.h"
//#include "motion.h"
//#include "logging.h"
//#include "sensors.h"
//#include "walls.h"

Motor motorL, motorR;
//Encoder encoders;
//IRSensor sensors;
//
bool mazeComplete = false;

void setup() {
  Serial.begin(115200);

  // Initialize motors
  motorL.init(MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, false, MOTOR_FREQUENCY, MOTOR_RESOLUTION);
  motorR.init(MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2, false, MOTOR_FREQUENCY, MOTOR_RESOLUTION);

  // Initialize encoders
//  encoders.init();
//  sensors.init();

  // Stop motors at start
  motorL.stop();
  motorR.stop();
//
//  initBluetooth();

//  encoders.resetValuesToZero();
}
//
void loop() {
  motorL.move(90);
  motorR.move(90);
//  moveOneCell();
//  delay(2000);
//  turnRight90PID();
//  
//  delay(5000);
//  moveOneCell();
//  delay(2000);
//  turnLeft90PID();
//  
//  delay(5000);
//  
//  moveOneCell();
//  delay(2000);
//  turn180PID();
//
//   delay(6000);
//   if(!mazeComplete){
//    moveOneCell();
//    SerialBT.print("FRONT WALL : ");
//    SerialBT.println(isWallAtFront());
//    SerialBT.print("LEFT WALL : ");
//    SerialBT.println(isWallAtLeft());
//    SerialBT.print("RIGHT WALL : ");
//    SerialBT.println(isWallAtRight());
//     delay(1000);
//     turnLeft90PID();
//    SerialBT.print("FRONT WALL : ");
//    SerialBT.println(isWallAtFront());
//    SerialBT.print("LEFT WALL : ");
//    SerialBT.println(isWallAtLeft());
//    SerialBT.print("RIGHT WALL : ");
//    SerialBT.println(isWallAtRight());
//     delay(1000);
//     moveOneCell();
//    SerialBT.print("FRONT WALL : ");
//    SerialBT.println(isWallAtFront());
//    SerialBT.print("LEFT WALL : ");
//    SerialBT.println(isWallAtLeft());
//    SerialBT.print("RIGHT WALL : ");
//    SerialBT.println(isWallAtRight());
//     delay(1000);
//     turnRight90PID();
//    SerialBT.print("FRONT WALL : ");
//    SerialBT.println(isWallAtFront());
//    SerialBT.print("LEFT WALL : ");
//    SerialBT.println(isWallAtLeft());
//    SerialBT.print("RIGHT WALL : ");
//    SerialBT.println(isWallAtRight());
//     delay(1000);
//    moveOneCell();
//    SerialBT.print("FRONT WALL : ");
//    SerialBT.println(isWallAtFront());
//    SerialBT.print("LEFT WALL : ");
//    SerialBT.println(isWallAtLeft());
//    SerialBT.print("RIGHT WALL : ");
//    SerialBT.println(isWallAtRight());
//     delay(1000);
//     turnLeft90PID();
//    SerialBT.print("FRONT WALL : ");
//    SerialBT.println(isWallAtFront());
//    SerialBT.print("LEFT WALL : ");
//    SerialBT.println(isWallAtLeft());
//    SerialBT.print("RIGHT WALL : ");
//    SerialBT.println(isWallAtRight());
//     delay(1000);
//     moveOneCell();
//    SerialBT.print("FRONT WALL : ");
//    SerialBT.println(isWallAtFront());
//    SerialBT.print("LEFT WALL : ");
//    SerialBT.println(isWallAtLeft());
//    SerialBT.print("RIGHT WALL : ");
//    SerialBT.println(isWallAtRight());
//     delay(1000);
//     moveOneCell();
//    SerialBT.print("FRONT WALL : ");
//    SerialBT.println(isWallAtFront());
//    SerialBT.print("LEFT WALL : ");
//    SerialBT.println(isWallAtLeft());
//    SerialBT.print("RIGHT WALL : ");
//    SerialBT.println(isWallAtRight());
//     delay(1000);
//     turnRight90PID();
//    SerialBT.print("FRONT WALL : ");
//    SerialBT.println(isWallAtFront());
//    SerialBT.print("LEFT WALL : ");
//    SerialBT.println(isWallAtLeft());
//    SerialBT.print("RIGHT WALL : ");
//    SerialBT.println(isWallAtRight());
//     delay(1000);
//     moveOneCell();
//    SerialBT.print("FRONT WALL : ");
//    SerialBT.println(isWallAtFront());
//    SerialBT.print("LEFT WALL : ");
//    SerialBT.println(isWallAtLeft());
//    SerialBT.print("RIGHT WALL : ");
//    SerialBT.println(isWallAtRight());
//     delay(1000);
//}
//mazeComplete = false;
}
//
