#include <Arduino.h>
#include "Servo.h"             
 
//defining pins as needed for the Freenove expansion board
#define PIN_SERVO         2    
#define PIN_SONIC_TRIG    7    
#define PIN_SONIC_ECHO    8    

#define PIN_DIRECTION_RIGHT 3
#define PIN_DIRECTION_LEFT  4
#define PIN_MOTOR_PWM_RIGHT 5
#define PIN_MOTOR_PWM_LEFT  6

#define MAX_DISTANCE    300   //cm
#define SONIC_TIMEOUT   (MAX_DISTANCE*60) // calculate timeout 
#define SOUND_VELOCITY  340  //soundVelocity: 340m/s

Servo servo;             //create servo object
byte servoOffset = 0;    //change the value to Calibrate servo
u8 distance[20];          //define an arry with type u8(same to unsigned char)
u8 sensorValue[4];       //define an array 
uint8_t environmentMap[10][10];


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
    left = -left;
  }
  if(right > 0){
    digitalWrite(PIN_DIRECTION_RIGHT, HIGH);
  }else {
    digitalWrite(PIN_DIRECTION_RIGHT, LOW);
    right = - right;
  }
  analogWrite(PIN_MOTOR_PWM_RIGHT, right);
  analogWrite(PIN_MOTOR_PWM_LEFT, left);
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_SONIC_TRIG, OUTPUT);
  pinMode(PIN_SONIC_ECHO, INPUT); 

  servo.attach(PIN_SERVO);        //initialize servo 
  servo.write(90 + servoOffset);  // change servoOffset to Calibrate servo
}

void loop() {
    delay(5000);
    distance[0] = getSonar();
    for(int i = 1; i < 6; i++){
        drive(-80, -80);
        delay(500);
        drive(0, 0);
        delay(1000);
        distance[i] = getSonar();
    }
    for (int i = 7; i < 11; i++){
        drive(-80, -80);
        delay(1000);
        drive(0, 0);
        delay(1000);
        distance[i] = getSonar();
    }
    delay(10000);
    for (int i = 11; i < 15; i++){
        drive(80, 80);
        delay(5000);
        drive(0, 0);
        delay(1000);
        distance[i] = getSonar();
    }
/*
    for (int i = 11; i < 15; i++){
        drive(80, 80);
        delay(20000);
        drive(0, 0);
        delay(1000);
        distance[i] = getSonar();
    }*/

    for(int i = 0; i < sizeof(distance); i++){
        Serial.println(distance[i]);
    }

        Serial.println("Done");
        delay(50000);

}

