#include <Arduino.h>
#include "robot.h"

byte servoOffset = 0;    //change the value to Calibrate servo

Servo servo;

int distance;

void setup(){
    Serial.begin(9600);
    pinMode(PIN_TRACKING_LEFT, INPUT); 
    pinMode(PIN_TRACKING_RIGHT, INPUT); 
    pinMode(PIN_TRACKING_CENTER, INPUT); 
    pinMode(PIN_SONIC_TRIG, OUTPUT);
    pinMode(PIN_SONIC_ECHO, INPUT); 
    servo.attach(PIN_SERVO);
    delay(5000);
    Serial.println("Start");
    servo.write(180);
    delay(3000);
}

void loop(){
    distance = getSonar();
    delay(50);
    Serial.println(distance);
    if(distance < 20){
        Serial.println("Object links");
        drive(70, 70);
    }else{//Parking gap detected. Initiate parking movement
        drive(0,0);
        distance = getSonar();
        if(distance < 20){
            loop();
        }
        Serial.println("Begin met parkeren");
        drive(0, 70);
        delay(3000);
        drive(0, 0);
        delay(1000);
        drive(80, 80);
        delay(400);
        drive(100, -100);
        delay(630);
        drive(0, 0);
        servo.write(90);
        delay(1000);
        while(1){
            if(getSonar() < 10){
                drive(0, 0);
                exit(1);
            }else{
                drive(70, 70);
                delay(100);
            }
        }
    }
}