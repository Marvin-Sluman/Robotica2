#include <Arduino.h>
#include "robot.h"

Servo servo;
int distance[3];
int bottomSensor;

void setup(){
    Serial.begin(9600);
    pinMode(PIN_SONIC_TRIG, OUTPUT);
    pinMode(PIN_SONIC_ECHO, INPUT); 
    pinMode(PIN_TRACKING_LEFT, INPUT); 
    pinMode(PIN_TRACKING_RIGHT, INPUT); 
    pinMode(PIN_TRACKING_CENTER, INPUT);
    servo.attach(PIN_SERVO);
}

void loop(){
    servo.write(10);
    distance[0] = getSonar(); 
    delay(200);
    servo.write(90);
    distance[1] = getSonar(); 
    delay(200);
    servo.write(170);
    distance[2] = getSonar();
    delay(200); 
    
    Serial.print("Left: ");
    Serial.print(distance[0]);
    Serial.print("   Center: ");
    Serial.print(distance[1]);
    Serial.print("   Right: ");
    Serial.print(distance[2]);
    Serial.println();

    if(distance[1] > distance[0] && distance[1] > distance[2]){
        while(1){
            drive(80, 80);
            bottomSensor = getLightSensor();
            /*if (bottomSensor > 0){
                exit(1);
            }else{*/
                servo.write(90);
                if(getSonar() <10){
                    delay(300);
                    drive(0, 0);
                    return;
                } 
                delay(200);
            //}
        }
    }else if(distance[0] > distance[2]){
        drive(80, -80);
    }else{
        drive(-80, 80);
    }
}