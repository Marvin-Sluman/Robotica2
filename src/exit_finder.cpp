#include <Arduino.h>
#include "robot.h"

Servo servo;
int distance;
int bottomSensor;
unsigned long beginTime;
unsigned long currentTime;
unsigned long duration;
unsigned long returnDuration;
uint8_t sensorValue[4]; 

void setup(){
    Serial.begin(9600);
    pinMode(PIN_SONIC_TRIG, OUTPUT);
    pinMode(PIN_SONIC_ECHO, INPUT); 
    pinMode(PIN_TRACKING_LEFT, INPUT); 
    pinMode(PIN_TRACKING_RIGHT, INPUT); 
    pinMode(PIN_TRACKING_CENTER, INPUT);
    servo.attach(PIN_SERVO);
    delay(6000);
}

void loop(){
    servo.write(90);
    distance = getSonar(); 
    if(distance < 50){
        Serial.println(distance);
        drive(-80, 80);
        delay(30);
    }else{
        drive(0, 0);
        delay(3000);
        drive(-80, 80);
        delay(200);
        drive(0, 0);
        beginTime = millis();
        drive(80, 80);
        while(1){
            sensorValue[0] = digitalRead(PIN_TRACKING_LEFT);
            sensorValue[1] = digitalRead(PIN_TRACKING_CENTER);
            sensorValue[2] = digitalRead(PIN_TRACKING_RIGHT);
            sensorValue[3] = sensorValue[0] << 2 | sensorValue[1] << 1 | sensorValue[2]; //Moves the bits to create different values for the combinations of sensors
            if(sensorValue[3] > 0){
                delay(500);
                drive(0,0);
                currentTime = millis();
                duration = currentTime - beginTime;
                //Turn 180 degrees
                drive(-100, 100);
                delay(1400);
                drive(0, 0);
                delay(500);
                beginTime = millis();
                drive(80, 80);
                while(returnDuration < duration){
                    currentTime = millis();
                    returnDuration = currentTime - beginTime;
                }
                drive(0,0);
                delay(60000);
            }
        }
    }

}