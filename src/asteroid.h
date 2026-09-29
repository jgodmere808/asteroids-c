#pragma once

#include "raylib.h"
#include "raymath.h"
#include "utils.h"

enum AsteroidShape {
    SHAPE_ONE,
    SHAPE_TWO,
    SHAPE_THREE
};

enum AsteroidSize {
    SMALL,
    MEDIUM,
    LARGE
};

typedef struct _asteroid {
    float speed;
    Position pos;
    Velocity vel;
    enum AsteroidShape shape;
    enum AsteroidSize size;
    Vector2 lines[11];
} Asteroid;

Asteroid createAsteroid(Position pos);
void moveAsteroid(Asteroid *asteroid, Position pos);
void updateAsteroid(Asteroid *asteroid);
void drawAsteroid(Asteroid *asteroid);