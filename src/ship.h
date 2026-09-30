#pragma once

#include "raylib.h"
#include "raymath.h"
#include "utils.h"

typedef struct _ship {
    float angle;
    float radius;
    Position pos;
    Velocity vel;
    Vector2 lines[5];
    Vector2 thrustLines[4];
    int disableThrusters;
} Ship;

Ship initShip();
void moveShip(Ship *ship, Position pos);
void updateShip(Ship *ship, int gameWidth, int gameHeight);
void drawShip(Ship *ship);