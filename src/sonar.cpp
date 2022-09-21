#include <Arduino.h>
#include "Servo.h"           
 
#define PIN_SERVO         2  
#define PIN_SONIC_TRIG    7    
#define PIN_SONIC_ECHO    8 

#define MAX_DISTANCE    300   //cm
#define SONIC_TIMEOUT   (MAX_DISTANCE*60) // calculate timeout 
#define SOUND_VELOCITY  340  //soundVelocity: 340m/s

byte servoOffset = 0;    //change the value to Calibrate servo
u8 distance;          //define an arry with type u8(same to unsigned char)
uint8_t sensorValue;       //define an array 

Servo servo;

float getSonar() {
  unsigned long pingTime;
  float distance;
  digitalWrite(PIN_SONIC_TRIG, HIGH); // make trigPin output high level lasting for 10μs to triger HC_SR04,
  delayMicroseconds(10);
  digitalWrite(PIN_SONIC_TRIG, LOW);
  pingTime = pulseIn(PIN_SONIC_ECHO, HIGH, SONIC_TIMEOUT); // Wait HC-SR04 returning to the high level and measure out this waitting time
  if (pingTime != 0)
    distance = (float)pingTime * SOUND_VELOCITY / 2 / 10000; // calculate the distance according to the time
  else
    distance = MAX_DISTANCE;
  return distance; // return the distance value
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_SONIC_TRIG, OUTPUT);
  pinMode(PIN_SONIC_ECHO, INPUT); 
  servo.attach(PIN_SERVO);        //initialize servo 
}

void loop() {
    distance = getSonar();
    Serial.println(distance);
}
