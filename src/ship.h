#pragma once

#include "raylib.h"
#include "utils.h"

typedef struct _ship {
    Position pos;
    Velocity vel;
    Vector2 lines[5];
} Ship;

Ship initShip();
void moveShip(Ship *ship, Position pos);
void drawShip(Ship *ship);