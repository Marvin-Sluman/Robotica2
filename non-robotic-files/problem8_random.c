#include <stdio.h>
#include <stdlib.h>
#include <robot.h>
#include <time.h>


float distanceMultiplier = 171.5265866209262; //   1 / 0.005830
int distance;

time_t t1;
int counter;

void init() {
    double pingTime = ping();
    //dprintf(robotOut, "ping:%f", pingTime);
    directionLeft(CounterClockwise);
    directionRight(Clockwise);
    srand((unsigned) time(&t1));
    wait(5);
}

void turnRight(){
    speed(0);
    directionRight(CounterClockwise);
    speed(1);
    wait(2);
    directionRight(Clockwise);
    speed(0);
}

void turnLeft(){
    speed(0);
    directionLeft(Clockwise);
    speed(1);
    wait(2);
    directionLeft(CounterClockwise);
    speed(0);
}

void turn(){
    counter = 0;
    if((rand() % 2) == 1){
        turnLeft();
        loop();
    }else{
        turnRight();
        loop();
    }
}

void loop(){
    double pingTime = ping();
    distance = pingTime * distanceMultiplier;
    dprintf(robotOut, "Dist: %d", distance);
    if(pingTime == 0 || counter == 5){
        turn();
    }else if(pingTime < 0.012){
        speed(1);
    }else if(pingTime < 0.018){
        speed(2);
    }else{
        speed(3);
    }
    wait(1);
    speed(0);
    counter++;
}