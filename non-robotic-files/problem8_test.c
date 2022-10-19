#include <stdio.h>
#include <robot.h>

#define UP 1
#define DOWN 3
#define LEFT 4
#define RIGHT 2

#define N   1
#define E   2
#define S   3
#define W   4

//__uint16_t avoidanceSize = 1;
__uint16_t returnYCoord;
__uint16_t returnXCoord;
__uint16_t yCoord = 1;
__uint16_t xCoord = 1;
__uint16_t yMax = 40;
__uint16_t xMax = 100;
__uint16_t yMin = 3;
__uint16_t xMin = 3;
int heading = N;
int direction = UP;
int currentDirection;

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
        default:
            break;
    }
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

int checkObstacle(){
    int isObstacle;
    double pingTime = ping();
    if(pingTime < 0.005){
        returnXCoord = xCoord;
        returnYCoord = yCoord +1;
        isObstacle = 1;
    }else{
        isObstacle = 0;
    }
    return isObstacle;
}

void moveAroundObstacle(int xOffset, int yOffset){
    turnRight();
    if(checkObstacle()){
        turnRight();
        move(DOWN);
        turnLeft();
        move(RIGHT);
        turnLeft();
        moveAroundObstacle(1, 1);
    }else{
        (direction == 4) ? currentDirection = 1 : currentDirection++;
        move(currentDirection);
        turnLeft();
        if(checkObstacle()){
            moveAroundObstacle(2, 1);
        }else{
            move(direction);
            if(checkObstacle()){
                moveAroundObstacle(2, 2);
            }else{
                move(direction);
                turnLeft();
                if(checkObstacle()){
                    turnRight();
                    move(direction);
                    turnLeft();
                    (direction == 1) ? currentDirection = 4 : currentDirection--;
                    move(currentDirection);
                    turnRight();
                }else{
                    for(int i = 0; i < xOffset; i++){
                        (direction == 1) ? currentDirection = 4 : currentDirection--;
                        move(currentDirection);
                    }
                    turnRight();
                }
            }
        }
    }
}

void loop(){
    wait(0.2);
    dprintf(robotOut, "X: %d  Y: %d", xCoord, yCoord);
    wait(0.2);
    if(checkObstacle()){
            moveAroundObstacle(1, 1);
    }

    switch (direction)
    {
    case UP:
        if(yCoord < yMax){
            move(UP);
        }else{
            turnRight();
            yMax--;
            direction = RIGHT;
        }
        break;
    case RIGHT:
        if(xCoord < xMax){
            move(RIGHT);
        }else{
            xMax--;
            turnRight();
            direction = DOWN;
        }
        break;
    case DOWN:
        if(yCoord > yMin){
            move(DOWN);
        }else{
            turnRight();
            direction = LEFT;
        }
        break;
    case LEFT:
        if(xCoord > xMin){
            move(LEFT);
        }else{
            turnRight();
            direction = UP;
        }
        break;

    default:
        break;
    }
    /*
    if(yCoord < 44 && direction == UP){
        if(checkObstacle()){
            moveAroundObstacle(1, 1);
        }else{
            move(UP);
        }
    }else if(yCoord > 1 && direction == DOWN){
        if(checkObstacle()){
            moveAroundObstacle(1, 1);
        }else{
            move(DOWN);
        }
    }else{
        if(direction == UP){
            turnRight();
            move(RIGHT);
            turnRight();
            direction = DOWN;
        }else{
            turnLeft();
            move(LEFT);
            turnLeft();
            direction = UP;
        }
    }*/
}