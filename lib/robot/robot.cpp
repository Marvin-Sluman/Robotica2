#include <Arduino.h>
#include "Servo.h"        
#include "robot.h"  

extern Servo servo;

void setPins(){
  pinMode(PIN_SONIC_TRIG, OUTPUT);
  pinMode(PIN_SONIC_ECHO, INPUT); 
  pinMode(PIN_TRACKING_LEFT, INPUT); 
  pinMode(PIN_TRACKING_RIGHT, INPUT); 
  pinMode(PIN_TRACKING_CENTER, INPUT); 
}

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

//Function to move the motors. Requires value between -255 and 255 for both sides
void drive(int left, int right){

  if(left > 0){
    digitalWrite(PIN_DIRECTION_LEFT, LOW);
  }else {
    digitalWrite(PIN_DIRECTION_LEFT, HIGH);
  }
  if(right > 0){
    digitalWrite(PIN_DIRECTION_RIGHT, HIGH);
  }else {
    digitalWrite(PIN_DIRECTION_RIGHT, LOW);
  }
  analogWrite(PIN_MOTOR_PWM_RIGHT, right);
  analogWrite(PIN_MOTOR_PWM_LEFT, left);
}

int getLightSensor() {
  uint8_t sensorValue[4];
  sensorValue[0] = digitalRead(PIN_TRACKING_LEFT);
  sensorValue[1] = digitalRead(PIN_TRACKING_CENTER);
  sensorValue[2] = digitalRead(PIN_TRACKING_RIGHT);
  sensorValue[3] = sensorValue[0] << 2 | sensorValue[1] << 1 | sensorValue[2]; //Moves the bits to create different values for the combinations of sensors
  Serial.print("Sensor Value (L / M / R / ALL) : ");
  for (int i = 0; i < 4; i++) {
    Serial.print(sensorValue[i]);
    Serial.print('\t');
  }
  Serial.print('\n');
  
  return sensorValue[3];
}