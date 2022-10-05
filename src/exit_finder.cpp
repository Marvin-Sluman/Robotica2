#include <Arduino.h>
#include "robot.h"

Servo servo;
int distance[3];
int bottomSensor;

void setup(){
    Serial.begin(9600);
    pinMode(PIN_TRACKING_LEFT, INPUT); 
    pinMode(PIN_TRACKING_RIGHT, INPUT); 
    pinMode(PIN_TRACKING_CENTER, INPUT);
    servo.attach(PIN_SERVO);
}

void loop(){
    servo.write(10);
    distance[0] = getSonar(); 
    servo.write(90);
    distance[1] = getSonar(); 
    servo.write(170);
    distance[2] = getSonar(); 

    if(distance[1] > distance[0] && distance[1] > distance[2]){
        //Move forward
        bottomSensor = getLightSensor();
        if (bottomSensor > 0){
            exit(1);
        }else{
            servo.write(90);
            if(getSonar() <10){
                return;
            } 
        }
    }else if(distance[0] > distance[2]){
        //Move left
    }else{
        //Move right
    }
}