#include <Arduino.h>
#include "robot.h"
#include "Freenove_WS2812B_RGBLED_Controller.h"

#define I2C_ADDRESS 0x20
#define LEDS_COUNT  10
  
#define PIN_TRACKING_LEFT   A1
#define PIN_TRACKING_CENTER A2
#define PIN_TRACKING_RIGHT  A3

#define PIN_DIRECTION_RIGHT 3
#define PIN_DIRECTION_LEFT  4
#define PIN_MOTOR_PWM_RIGHT 5
#define PIN_MOTOR_PWM_LEFT  6

Freenove_WS2812B_Controller strip(I2C_ADDRESS, LEDS_COUNT, TYPE_GRB);

byte servoOffset = 0;    //change the value to Calibrate servo
uint8_t sensorValue[4];       //define an array 
uint8_t lastCase = 0;
uint16_t distance;
uint8_t message[4];
uint8_t lastBit;
int i = 0;

Servo servo;

void setup() {
    Serial.begin(9600);
    while(!strip.begin());
    pinMode(PIN_TRACKING_LEFT, INPUT); 
    pinMode(PIN_TRACKING_RIGHT, INPUT); 
    pinMode(PIN_TRACKING_CENTER, INPUT);
    servo.attach(PIN_SERVO); 
    servo.write(180);
}

void loop() {
    sensorValue[0] = digitalRead(PIN_TRACKING_LEFT);
    sensorValue[1] = digitalRead(PIN_TRACKING_CENTER);
    sensorValue[2] = digitalRead(PIN_TRACKING_RIGHT);
    sensorValue[3] = sensorValue[0] << 2 | sensorValue[1] << 1 | sensorValue[2]; //Moves the bits to create different values for the combinations of sensors

    distance = getSonar();
    delay(50);
    Serial.println(distance);
    if(distance < 10){
        message[i] = 1;
        lastBit = 1;
        i++;
    }else if(distance < 20){
        message[i] = 1;
        lastBit = 0;
        i++;
    }

    if(sensorValue[3] == 0){
        sensorValue[3] = lastCase;
    }
    switch(sensorValue[3]){
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
            break;  
    }