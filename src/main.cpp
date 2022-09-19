#include <Arduino.h>
#include "robot.h" 
#include "Servo.h"           
 
byte servoOffset = 0;    //change the value to Calibrate servo
u8 distance[4];          //define an arry with type u8(same to unsigned char)
uint8_t sensorValue;       //define an array 
uint8_t environmentMap[10][10];

Servo servo;

//Creates a 2D array of 10 readings at different servo positions in steps of 20 degrees
void mapObstacles(){
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      servo.write(j*20);
      environmentMap[j][i] = getSonar();
      delay(300);
    }
  }
  for(int i = 0; i < 10; i++){
    Serial.print("Readings:  ");
    //int degrees = i*20;
    //Serial.print(degrees);
    for(int j = 0; j <10; j++){
      Serial.print(environmentMap[i][j]);
      Serial.print(",  ");
    }
    Serial.print('\n');
  }
}

void setup() {
  Serial.begin(9600);
  void setPins();
  servo.attach(PIN_SERVO);        //initialize servo 
}

void loop() {
  sensorValue = getLightSensor();
  if(sensorValue > 0){ //Stop motors if one of the sensors measures black
    drive(0, 0);
    mapObstacles();
  }else{
    drive(70, 70);
    delay(1000);
  }

}
