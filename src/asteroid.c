
#include "asteroid.h"

#define ASTEROID_LINES 11

Asteroid createAsteroid(Position pos, Velocity vel, enum AsteroidSize size)
{
    int i;
    enum AsteroidShape shape =
        (enum AsteroidShape)GetRandomValue(SHAPE_ONE, SHAPE_THREE);

    Asteroid asteroid = {
        .pos = pos,
        .vel = vel,
        .shape = shape,
        .size = size
    };

    switch (size) {
        case SMALL:
            asteroid.speed = 40.0f;
            break;
        case MEDIUM:
            asteroid.speed = 30.0f;
            break;
        case LARGE:
            asteroid.speed = 20.0f;
            break;
    }
    
    Vector2 lines[3][ASTEROID_LINES] = {
        { // SHAPE_ONE
            {   0, -55 }, {  24, -49 }, {  47, -29 }, {  39,  -6 },
            {  55,  19 }, {  30,  46 }, {   2,  51 }, { -25,  40 },
            { -51,  17 }, { -43, -26 }, {   0, -55 }
        },
        { // SHAPE_TWO
            {  -5, -54 }, {  16, -36 }, {  39, -49 }, {  55, -21 },
            {  34,   1 }, {  49,  27 }, {  20,  50 }, {  -9,  44 },
            { -38,  52 }, { -52,   3 }, {  -5, -54 }
        },
        { // SHAPE_THREE
            { -37, -40 }, {  -7, -50 }, {  24, -47 }, {  53, -25 },
            {  40,   0 }, {  54,  33 }, {  15,  50 }, { -15,  35 },
            { -43,  45 }, { -53,   0 }, { -37, -40 }
        }
    };

    for (i = 0; i < ASTEROID_LINES; i++) {
        asteroid.lines[i] = lines[shape][i];
    }

    return asteroid;
}

void moveAsteroid(Asteroid *asteroid, Position pos)
{
    asteroid->pos = pos;
}

void updateAsteroid(Asteroid *asteroid)
{
    float nextX, nextY;

    nextX = asteroid->pos.x + asteroid->vel.dx;
    nextY = asteroid->pos.y + asteroid->vel.dy;

    asteroid->pos.x = nextX;
    asteroid->pos.y = nextY;
}

void drawAsteroid(Asteroid *asteroid)
{
    int i;
    float factor = 0;
    Vector2 posLines[ASTEROID_LINES];

    switch (asteroid->size) {
        case SMALL:
            factor = 0.2f;
            break;
        case MEDIUM:
            factor = 0.6f;
            break;
        case LARGE:
            factor = 1.0f;
            break;
    }

    for (i = 0; i < ASTEROID_LINES; i++) {
        posLines[i] = (Vector2){
            factor * asteroid->lines[i].x + asteroid->pos.x,
            factor * asteroid->lines[i].y + asteroid->pos.y
        };
    }

    DrawLineStrip(posLines, ASTEROID_LINES, WHITE);
}