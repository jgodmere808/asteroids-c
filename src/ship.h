#pragma once

#include "raylib.h"
#include "raymath.h"
#include "utils.h"

typedef struct _ship {
    float angle;
    Position pos;
    Velocity vel;
    Vector2 lines[5];
    Vector2 thrustLines[4];
} Ship;

Ship initShip();
void moveShip(Ship *ship, Position pos);
void updateShip(Ship *ship);
void drawShip(Ship *ship);