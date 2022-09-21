#include <Arduino.h>
  
#define PIN_TRACKING_LEFT   A1
#define PIN_TRACKING_CENTER A2
#define PIN_TRACKING_RIGHT  A3

#define PIN_DIRECTION_RIGHT 3
#define PIN_DIRECTION_LEFT  4
#define PIN_MOTOR_PWM_RIGHT 5
#define PIN_MOTOR_PWM_LEFT  6

u8 sensorValue[4];       //define an array 

//Function to move the motors. Requires value between -255 and 255 for both sides
void drive(int left, int right){
  if(left > 0){
    digitalWrite(PIN_DIRECTION_LEFT, LOW);
  }else {
    digitalWrite(PIN_DIRECTION_LEFT, HIGH);
  }
  if(right > 0){
    digitalWrite(PIN_DIRECTION_RIGHT, HIGH);
  }else {
    digitalWrite(PIN_DIRECTION_RIGHT, LOW);
  }
  analogWrite(PIN_MOTOR_PWM_RIGHT, right);
  analogWrite(PIN_MOTOR_PWM_LEFT, left);
}

void setup() {
    Serial.begin(9600);
    pinMode(PIN_TRACKING_LEFT, INPUT); 
    pinMode(PIN_TRACKING_RIGHT, INPUT); 
    pinMode(PIN_TRACKING_CENTER, INPUT); 
}

void loop() {
    sensorValue[0] = digitalRead(PIN_TRACKING_LEFT);
    sensorValue[1] = digitalRead(PIN_TRACKING_CENTER);
    sensorValue[2] = digitalRead(PIN_TRACKING_RIGHT);
    sensorValue[3] = sensorValue[0] << 2 | sensorValue[1] << 1 | sensorValue[2]; //Moves the bits to create different values for the combinations of sensors

    switch(sensorValue[3]){
        case 0: //All white
            drive(0, 0);
            break;
        case 1: //Right black
            drive(120, -120);
            break;
        case 2: //Center black
            drive(80, 80);
            break;
        case 4: //Left black
            drive(-120, 120);
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
  
}
