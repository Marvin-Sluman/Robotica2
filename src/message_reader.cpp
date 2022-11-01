#include <Arduino.h>
#include "robot.h"
#include "Freenove_WS2812B_RGBLED_Controller.h"

Freenove_WS2812B_Controller strip(I2C_ADDRESS, LEDS_COUNT, TYPE_GRB);

byte servoOffset = 0;    //change the value to Calibrate servo
uint8_t sensorValue[4];       //define an array 
uint8_t lastCase = 0;
uint16_t distance;
uint8_t message[4];
uint8_t lastBit;
bool gapDetect = true;
int i = 0;
int timeOut = 500;
int timeReading;

Servo servo;

void setup() {
    Serial.begin(9600);
    while(!strip.begin());
    setPins();
    servo.attach(PIN_SERVO); 
    servo.write(180);
    delay(5000);
}

void loop() {
    sensorValue[0] = digitalRead(PIN_TRACKING_LEFT);
    sensorValue[1] = digitalRead(PIN_TRACKING_CENTER);
    sensorValue[2] = digitalRead(PIN_TRACKING_RIGHT);
    sensorValue[3] = sensorValue[0] << 2 | sensorValue[1] << 1 | sensorValue[2]; //Moves the bits to create different values for the combinations of sensors

    if((millis() - timeReading) > timeOut){
        distance = getSonar();
        delay(50);
        //Serial.println(distance);
        if(distance < 15){
            drive(0, 0);
            gapDetect = false;
            message[i] = 1;
            lastBit = 1;
            i++;
            strip.setLedColor(i, 0xFF0000);
            delay(3000);
            timeReading = millis();
        }else if(distance < 21){
            drive(0, 0);
            gapDetect = false;
            message[i] = 0;
            lastBit = 0;
            i++;
            strip.setLedColor(i, 0x0000FF);
            delay(3000);
            timeReading = millis();
        }else if(distance > 20){
            gapDetect = true;
        }
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
    if(i == 4){
        for(int j = 0; j < 4; j++){
            drive(0, 0);
            Serial.print("Bit: ");
            Serial.print(j);
            Serial.print(" = ");
            Serial.println(message[j]);
            delay(2000);
        }
        exit(1);
    }
}