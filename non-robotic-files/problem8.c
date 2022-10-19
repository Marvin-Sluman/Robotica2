#include <stdio.h>
#include <robot.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define N   1
#define E   2
#define S   3
#define W   4


__uint16_t returnYCoord;
__uint16_t returnXCoord;
__uint16_t yCoord = 1;
__uint16_t xCoord = 1;
int heading = N;
int direction = UP;

void moveAroundObstacle();

void init(){
    double pingTime = ping();
    //dprintf(robotOut, "ping:%f", pingTime);
    directionLeft(CounterClockwise);
    directionRight(Clockwise);
    wait(5);
}

void move(int direction){
    speed(1);
    wait(1);
    //dprintf(robotOut, "X: %d  Y: %d", xCoord, yCoord);
    speed(0);
    switch (direction){
        case UP:
            yCoord++;
            break;
        case DOWN: 
            yCoord--;
            break;
        case RIGHT:
            xCoord++;
            break;
        case LEFT:
            xCoord--;
            break;
    }
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
    if(heading < 4){
        heading++;
    }else{
        heading = 0;
    }
    directionRight(CounterClockwise);
    speed(1);
    wait(2);
    directionRight(Clockwise);
    speed(0);
}

void turnLeft(){
    speed(0);
    if(heading > 0){
        heading--;
    }else{
        heading = 4;
    }
    directionLeft(Clockwise);
    speed(1);
    wait(2);
    directionLeft(CounterClockwise);
    speed(0);
}

void checkObstacle(){
    double pingTime = ping();
    if(pingTime < 0.005){
        returnXCoord = xCoord;
        returnYCoord = yCoord +1;
        moveAroundObstacle(direction);
    }
}

void moveAroundObstacle(int direction){
    turnRight();
    double pingTime = ping();
    if(pingTime < 0.005){
        turnLeft();
        turnLeft();
        move(LEFT);
        turnRight();
        checkObstacle();
        move(direction);
        checkObstacle();
        move(direction);
        turnRight();
        checkObstacle();
        move(RIGHT);
        turnRight();
    }else{
        moveRight();
        turnLeft();
        checkObstacle();
        move(direction);
        checkObstacle();
        move(direction);
        turnLeft();
        double pingTime = ping();
        if(pingTime < 0.005){
            turnRight();
            move(direction);
            turnLeft();
            move(LEFT);
            turnRight();
        }else{
            move(LEFT);
            turnRight();
        }
    }
}

void loop(){
    dprintf(robotOut, "X: %d  Y: %d", xCoord, yCoord);
    if(yCoord < 44 && direction == UP){
        checkObstacle();
        move(UP);
    }else if(yCoord > 1 && direction == DOWN){
        checkObstacle();
        move(DOWN);
    }else{
        if(direction == UP){
            turnRight();
            moveRight();
            turnRight();
            direction = DOWN;
        }else{
            turnLeft();
            move(LEFT);
            turnLeft();
            direction = UP;
        }
    }
}