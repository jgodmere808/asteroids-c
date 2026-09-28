#pragma once

#include "raylib.h"
#include "utils.h"

typedef struct _asteroid {
    Position pos;
    Velocity vel;
    Vector2 lines[11];
} Asteroid;

void updateAsteroid(Asteroid *asteroid);
void drawAsteroid(Asteroid *asteroid);