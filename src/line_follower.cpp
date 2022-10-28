#include <Arduino.h>
#include "robot.h"
#include "Freenove_WS2812B_RGBLED_Controller.h"

#define I2C_ADDRESS 0x20
#define LEDS_COUNT  10

Freenove_WS2812B_Controller strip(I2C_ADDRESS, LEDS_COUNT, TYPE_GRB);

byte servoOffset = 0;    //change the value to Calibrate servo
uint8_t sensorValue;       //define an array 
uint8_t lastCase = 0;
bool returning = false;
uint32_t startTime;
uint32_t currentTime;
uint32_t lastMeasure = 0;
uint32_t objectsLeft[10];
uint32_t objectsRight[10];
uint8_t objectsLeftCount, objectsRightCount;

Servo servo;

void returnPath(){
    if(objectsLeft[objectsLeftCount] < (currentTime - startTime)){
       strip.setLedColor(3, 0x0000FF);
       delay(50);
       objectsLeftCount++;
    }else{
        strip.setLedColor(3, 0x000000);
    }

    if(objectsRight[objectsRightCount] < (currentTime - startTime)){
       strip.setLedColor(8, 0x0000FF);
       delay(50);
       objectsRightCount++;
    }else{
        strip.setLedColor(8, 0x000000);
    }
}

void setup() {
    Serial.begin(9600);
    while(!strip.begin());
    pinMode(PIN_TRACKING_LEFT, INPUT); 
    pinMode(PIN_TRACKING_RIGHT, INPUT); 
    pinMode(PIN_TRACKING_CENTER, INPUT);
    pinMode(PIN_SONIC_TRIG, OUTPUT);
    pinMode(PIN_SONIC_ECHO, INPUT); 
    servo.attach(PIN_SERVO); 
    startTime = millis();
}

void loop() {
    
    sensorValue = getLightSensor();

    if(sensorValue == 0){
        sensorValue = lastCase;
    }
    switch(sensorValue){
        case 1: //Right black
            drive(120, -140);
            break;
        case 2: //Center black
            drive(80, 80);
            break;
        case 4: //Left black
            drive(-140, 120);
            break;
        case 3: //Center and right black
            drive(100, 60);
            break;
        case 6: //Center and left black
            drive(60, 100);
            break;
        case 5:
            drive(80, 80);
            break;
        case 7:
            drive(0, 0);
            delay(3000);
            returning = true;
            objectsLeftCount = 0;
            objectsRightCount = 0;
            startTime = millis();
            break;  
    }
    
    lastCase = sensorValue;
    currentTime = millis();
    if(returning == false){
        if((currentTime - lastMeasure) > 500 ){
            drive(0, 0);
            servo.write(170);
            delay(1000);
            if(getSonar() < 20){
                objectsLeft[objectsLeftCount] = (millis() - startTime);
                objectsLeftCount++;
                strip.setLedColor(3, 0x0000FF);
            }else{
                strip.setLedColor(3, 0x000000);
            }
            servo.write(10);
            delay(1000);
            if(getSonar() < 20){
                objectsRight[objectsRightCount] = (millis() - startTime);
                objectsRightCount++;
                strip.setLedColor(8, 0x0000FF);
            }else{
                strip.setLedColor(8, 0x000000);
            }
            lastMeasure = millis();
        }
    }else{
        returnPath();
    }
}
