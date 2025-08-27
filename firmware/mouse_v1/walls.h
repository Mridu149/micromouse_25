#ifndef WALLS_H
#define WALLS_H

#include "sensors.h"
#include "config.h"

extern IRSensor sensors;

int isWallAtFront() {
    uint16_t dist = sensors.getFrontSensorReading();
    if (dist <= FRONT_WALL_THRESHOLD) {
        return 1;
    }
    return 0;
}

int isWallAtRight() {
    uint16_t dist = sensors.getRightSensorReading();
    if (dist <= SIDE_WALL_THRESHOLD) {
        return 1;
    }
    return 0;
}

int isWallAtLeft() {
    uint16_t dist = sensors.getLeftSensorReading();
    if (dist <= SIDE_WALL_THRESHOLD) {
        return 1;
    }
    return 0;
}

#endif
