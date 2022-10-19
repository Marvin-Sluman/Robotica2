#include <stdio.h>
#include <robot.h>

#define UP 1
#define DOWN 2

__uint16_t yCoord = 2;
__uint16_t xCoord = 1;
int direction = UP;

void init(){
    double pingTime = ping();
    //dprintf(robotOut, "ping:%f", pingTime);
    directionLeft(CounterClockwise);
    directionRight(Clockwise);
    wait(5);
}

void moveUp(){
    speed(1);
    wait(1);
    //dprintf(robotOut, "X: %d  Y: %d", xCoord, yCoord);
    speed(0);
    yCoord++;
}

void moveDown(){
    speed(1);
    wait(1);
    yCoord--;
    dprintf(robotOut, "X: %d  Y: %d", xCoord, yCoord);
    speed(0);
}

void moveRight(){
    speed(1);
    wait(1);
    xCoord++;
    dprintf(robotOut, "X: %d  Y: %d", xCoord, yCoord);
    speed(0);
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

void loop(){
    dprintf(robotOut, "X: %d  Y: %d", xCoord, yCoord);
    if(yCoord < 44 && direction == UP){
        moveUp();
    }else if(yCoord > 0 && direction == DOWN){
        moveDown();
    }else{
        turnRight();
        moveRight();
        turnRight();
        direction = DOWN;
    }
    double pingTime = ping();
    if(pingTime < 0.005){
        turnRight();
        moveRight();
        turnLeft();
    }/*
    pingTime = ping();
    dprintf(robotOut, "ping:%f", pingTime);
    speed(1);
    pingTime = ping();
    dprintf(robotOut, "ping:%f", pingTime);
    wait(1);*/
}