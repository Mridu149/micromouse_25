#include "config.h"
#include "motors.h"
#include "encoders.h"
#include "sensors.h"
#include "motion.h"

Motor motorR, motorL;
Encoder encoders;
IRSensor sensors;


void setup(){
  motorL.init( MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, false,MOTOR_FREQUENCY, MOTOR_RESOLUTION );
  motorR.init( MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2, false,MOTOR_FREQUENCY, MOTOR_RESOLUTION );

  encoders.init();
  sensors.init();
}

void loop(){
  
}
