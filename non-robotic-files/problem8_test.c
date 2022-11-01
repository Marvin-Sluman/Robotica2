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
__uint16_t yMax = 44;
__uint16_t xMax = 100;
__uint16_t yMin = 3;
__uint16_t xMin = 3;
int heading = N;
int direction = UP;
int currentDirection;
int distance;

void moveAroundObstacle();

void init(){
    double pingTime = ping();
    //dprintf(robotOut, "ping:%f", pingTime);
    directionLeft(CounterClockwise);
    directionRight(Clockwise);
    wait(5);
}

int getDistance(){
    double pingTime = ping();
    if(pingTime < 0.005){
        distance = 0;
        returnXCoord = xCoord;
        returnYCoord = yCoord +1;
    }else if(pingTime < 0.012){
        distance = 1;
    }else if(pingTime < 0.018){
        distance = 2;
    }else{
        distance = 3;
    }
    return distance;
}

void move(int direction, int steps){
    speed(steps);
    wait(1);
    speed(0);
    switch (direction){
        case UP:
            yCoord = yCoord + steps;
            break;
        case DOWN: 
            yCoord = yCoord - steps;
            break;
        case RIGHT:
            xCoord = xCoord + steps;
            break;
        case LEFT:
            xCoord = xCoord - steps;
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

void moveAroundObstacle(int xOffset, int yOffset){
    turnRight();
    if(getDistance() == 0){
        turnRight();
        move(DOWN, 1);
        turnLeft();
        move(RIGHT, 1);
        turnLeft();
        moveAroundObstacle(1, 1);
    }else{
        currentDirection = direction;
        (direction == 4) ? currentDirection = 1 : currentDirection++;
        move(currentDirection, 1);
        turnLeft();
        if(getDistance() == 0){  
            moveAroundObstacle(2, 1);
        }else{
            move(direction, 1);
            if(getDistance() == 0){
                moveAroundObstacle(2, 2);
            }else{
                move(direction, 1);
                turnLeft();
                if(getDistance() == 0){
                    turnRight();
                    move(direction, 1);
                    turnLeft();
                    currentDirection = direction;
                    (direction == 1) ? currentDirection = 4 : currentDirection--;
                    move(currentDirection, 1);
                    turnRight();
                }else{
                    for(int i = 0; i < xOffset; i++){
                        currentDirection = direction;
                        (direction == 1) ? currentDirection = 4 : currentDirection--;
                        move(currentDirection, 1);
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

    switch (getDistance())
    {
    case 0:
        moveAroundObstacle(1, 1);
        break;
    default:
        break;
    }

    switch (direction)
    {
    case UP:
        if(yCoord < yMax){
            if(getDistance == 0){
                moveAroundObstacle(1, 1);
            }else{
                move(UP, getDistance());
            }
        }else{
            turnRight();
            yMax--;
            direction = RIGHT;
        }
        break;
    case RIGHT:
        if(xCoord < xMax){
            if(getDistance == 0){
                moveAroundObstacle(1, 1);
            }else{
                move(RIGHT, getDistance());
            }
        }else{
            xMax--;
            turnRight();
            direction = DOWN;
        }
        break;
    case DOWN:
        if(yCoord > yMin){
            if(getDistance == 0){
                moveAroundObstacle(1, 1);
            }else{
                move(DOWN, getDistance());
            }
        }else{
            turnRight();
            direction = LEFT;
        }
        break;
    case LEFT:
        if(xCoord > xMin){
            if(getDistance == 0){
                moveAroundObstacle(1, 1);
            }else{
                move(LEFT, getDistance());
            }
        }else{
            turnRight();
            direction = UP;
        }
        break;

    default:
        break;
    }
}