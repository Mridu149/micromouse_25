#include <Arduino.h>
#include "motors.h"
#include "encoders.h"
#include "motion.h"
#include "flood.h"
#include "walls.h"

Motor motorL, motorR;
Encoder encoders;
IRSensor sensors;

// Maze parameters
Cell **maze;
bool mazeComplete = false;

// Robot state
int startRow = 0;
int startCol = 0;
Direction currDir = North;

// Goal
const int goalRow = endr;
const int goalCol = endc;

// Helper: update robot coordinates after moving
void updatePosition(int &r, int &c, Direction dir) {
    switch(dir) {
        case North: r++; break;
        case South: r--; break;
        case East:  c++; break;
        case West:  c--; break;
    }
}

// Helper: turn robot from currDir -> targetDir
void turnRobot(Direction &currDir, Direction targetDir) {
    if(currDir == targetDir) return;

    int diff = (targetDir - currDir + 4) % 4;
    if(diff == 1) { // turn right
        turnRight90PID();
    } else if(diff == 2) { // turn back
        turn180PID();
    } else if(diff == 3) { // turn left
        turnLeft90PID();
    }
    currDir = targetDir;
}

void setup() {
    Serial.begin(115200);

    // Initialize motors and encoders
    motorL.init(MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, false, MOTOR_FREQUENCY, MOTOR_RESOLUTION);
    motorR.init(MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2, false, MOTOR_FREQUENCY, MOTOR_RESOLUTION);
    encoders.init();
    motorL.stop();
    motorR.stop();
    encoders.resetValuesToZero();

    // Allocate and initialize maze
    maze = new Cell*[ROW];
    for(int r = 0; r < ROW; r++) {
        maze[r] = new Cell[COL];
        for(int c = 0; c < COL; c++) {
            maze[r][c] = {r, c, false, false, false, false, false, false, -1};
            // Boundary walls
            if(r == ROW-1) maze[r][c].wallN = true;
            if(c == COL-1) maze[r][c].wallE = true;
            if(r == 0) maze[r][c].wallS = true;
            if(c == 0) maze[r][c].wallW = true;
        }
    }

    // Initialize floodfill from goal
    updateFlood(maze, goalRow, goalCol);
}

void loop() {
    if(mazeComplete) return;

    // 1. Detect walls relative to robot and update maze
    setRelativeWall(maze, startRow, startCol, currDir,
                    isWallAtFront(), isWallAtRight(), isWallAtLeft());

    // 2. Update flood values after discovering new walls
    updateFlood(maze, goalRow, goalCol);

    // 3. Get best neighbor
    Direction nextDir = getLowestNeighbor(maze, startRow, startCol);

    // 4. Turn robot if needed
    turnRobot(currDir, nextDir);

    // 5. Move one cell forward
    moveOneCell();

    // 6. Update robot coordinates
    updatePosition(startRow, startCol, currDir);

    // 7. Mark cell visited
    maze[startRow][startCol].visitedCell = true;

    // 8. Check if goal reached
    if(startRow == goalRow && startCol == goalCol) {
        mazeComplete = true;
        Serial.println("Goal Reached!");
    }

    delay(50); // small delay to allow sensors/motors to stabilize
}
