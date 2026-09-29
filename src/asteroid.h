#pragma once

#include "raylib.h"
#include "utils.h"

enum AsteroidShape {
    SHAPE_ONE,
    SHAPE_TWO,
    SHAPE_THREE
};

typedef struct _asteroid {
    Position pos;
    Velocity vel;
    enum AsteroidShape shape;
    Vector2 lines[11];
} Asteroid;

Asteroid createAsteroid(Position pos, Velocity vel);
void updateAsteroid(Asteroid *asteroid);
void drawAsteroid(Asteroid *asteroid);