#include <Arduino.h>
  
#define PIN_TRACKING_LEFT   A1
#define PIN_TRACKING_CENTER A2
#define PIN_TRACKING_RIGHT  A3

#define PIN_DIRECTION_RIGHT 3
#define PIN_DIRECTION_LEFT  4
#define PIN_MOTOR_PWM_RIGHT 5
#define PIN_MOTOR_PWM_LEFT  6

int sensorValueLeft;
int sensorValueCenter;
int sensorValueRight;       

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
    sensorValueLeft = analogRead(PIN_TRACKING_LEFT);
    sensorValueCenter = analogRead(PIN_TRACKING_CENTER);
    sensorValueRight = analogRead(PIN_TRACKING_RIGHT);
    //sensorValue[3] = sensorValue[0] << 2 | sensorValue[1] << 1 | sensorValue[2]; //Moves the bits to create different values for the combinations of sensors  

    Serial.print("Left: ");
    Serial.print(sensorValueLeft);
    Serial.print("   Center: ");
    Serial.print(sensorValueCenter);
    Serial.print("   Right: ");
    Serial.print(sensorValueRight);
    Serial.println();

    delay(200);

}
