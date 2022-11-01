#include <Arduino.h>
#include "Servo.h"

//defining pins as needed for the Freenove expansion board
#define PIN_SERVO         2    
#define PIN_SONIC_TRIG    7    
#define PIN_SONIC_ECHO    8    

#define PIN_TRACKING_LEFT   A1
#define PIN_TRACKING_CENTER A2
#define PIN_TRACKING_RIGHT  A3

#define PIN_DIRECTION_RIGHT 3
#define PIN_DIRECTION_LEFT  4
#define PIN_MOTOR_PWM_RIGHT 5
#define PIN_MOTOR_PWM_LEFT  6

#define I2C_ADDRESS 0x20
#define LEDS_COUNT  10

#define MAX_DISTANCE    300   //cm
#define SONIC_TIMEOUT   (MAX_DISTANCE*60) // calculate timeout 
#define SOUND_VELOCITY  340  //soundVelocity: 340m/s

void setPins();

float getSonar();

void drive(int left, int right);

int getLightSensor();