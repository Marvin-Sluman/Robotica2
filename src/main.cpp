#include <Arduino.h>
#include "robot.h" 
#include "Servo.h"  
#include "Freenove_WS2812B_RGBLED_Controller.h"         

Freenove_WS2812B_Controller strip(I2C_ADDRESS, LEDS_COUNT, TYPE_GRB);

byte servoOffset = 0;    //change the value to Calibrate servo
u8 distance[4];          //define an arry with type u8(same to unsigned char)
uint8_t sensorValue;       //define an array 
uint8_t environmentMap[10][10];

Servo servo;

void showColours(int distance){
  if(distance < 11){
    strip.setAllLedsColor(0x0000FF);
  }else if (distance < 21){
    strip.setAllLedsColor(0x00FF00);
  }else if (distance < 31){
    strip.setAllLedsColor(0x00FFFF);
  }else if (distance < 41){
    strip.setAllLedsColor(0xFF0000);
  }else if (distance < 51){
    strip.setAllLedsColor(0xFF00FF);
  }else if (distance < 61){
    strip.setAllLedsColor(0xFFFF00);
  }
  
}

//Creates a 2D array of 10 readings at different servo positions in steps of 20 degrees
void mapObstacles(){
  //Reading the distances
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      servo.write(j*20);
      environmentMap[j][i] = getSonar();
      int colour;
      if(environmentMap[i][j] < 61){
        showColours(environmentMap[i][j]);
      }else{
        strip.setAllLedsColor(0);
      }
      delay(300);
    }
  }
  //Printing the distances
  for(int i = 0; i < 10; i++){
    Serial.print("Readings:  ");
    for(int j = 0; j <10; j++){
      Serial.print(environmentMap[i][j]);
      Serial.print(",  ");
    }
    Serial.print('\n');
  }
}

void setup() {
  Serial.begin(9600);
  setPins();
  servo.attach(PIN_SERVO);        //initialize servo 
}

void loop() {
  sensorValue = getLightSensor();
  if(sensorValue > 0){            //Stop motors if one of the sensors measures black
    drive(0, 0);
    mapObstacles();
  }else{
    drive(70, 70);
    delay(1000);
  }
}
