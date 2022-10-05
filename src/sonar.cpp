#include <Arduino.h>
#include "Servo.h"           
#include "robot.h"

byte servoOffset = 0;    //change the value to Calibrate servo
int distance[3];          //define an arry with type u8(same to unsigned char)
uint8_t sensorValue;       //define an array 

Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_SONIC_TRIG, OUTPUT);
  pinMode(PIN_SONIC_ECHO, INPUT); 
  servo.attach(PIN_SERVO);        //initialize servo 
}

void loop() {
    distance[0] = getSonar();
    Serial.println(distance[0]);
    delay(300);
}
