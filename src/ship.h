#pragma once

#include "raylib.h"
#include "raymath.h"
#include "utils.h"

typedef struct _ship {
    float angle;
    Position pos;
    Velocity vel;
    Vector2 lines[5];
} Ship;

Ship initShip();
void moveShip(Ship *ship, Position pos);
void addShipAngle(Ship *ship, float angle);
void drawShip(Ship *ship);