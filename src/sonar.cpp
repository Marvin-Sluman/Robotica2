#include <Arduino.h>
#include "Servo.h"           
#include "robot.h"
#include "Freenove_WS2812B_RGBLED_Controller.h"

#define I2C_ADDRESS 0x20
#define LEDS_COUNT  10

Freenove_WS2812B_Controller strip(I2C_ADDRESS, LEDS_COUNT, TYPE_GRB);

byte servoOffset = 0;    //change the value to Calibrate servo
int distance[3];          //define an arry with type u8(same to unsigned char)
uint8_t sensorValue;       //define an array 

Servo servo;

void setup() {
  while(!strip.begin());
  Serial.begin(9600);
  pinMode(PIN_SONIC_TRIG, OUTPUT);
  pinMode(PIN_SONIC_ECHO, INPUT); 
  servo.attach(PIN_SERVO);        //initialize servo 
  servo.write(180);
}

void loop() {
    distance[0] = getSonar();
    Serial.println(distance[0]);
    if(distance[0] < 11){
      strip.setLedColor(3, 0x0000FF);
    }else if(distance[0] < 21){
      strip.setLedColor(3, 0xFF0000);
    }else if(distance[0] < 31){
      strip.setLedColor(8, 0x0000FF);
    }else if(distance[0] < 41){
      strip.setLedColor(8, 0xFF0000);
    }

    delay(200);
}
