
#include "asteroid.h"

#define ASTEROID_LINES 11

Asteroid createAsteroid(Position pos)
{
    int i;
    enum AsteroidSize size = LARGE;
    enum AsteroidShape shape =
        (enum AsteroidShape)GetRandomValue(SHAPE_ONE, SHAPE_THREE);
    float angle, speed;
    Vector2 rotated;

    angle = GetRandomValue(0, 359) * DEG2RAD;
    rotated = Vector2Rotate((Vector2){ 0, -1.0f }, angle);

    switch (size) {
        case SMALL:
            speed = 2.5f;
            break;
        case MEDIUM:
            speed = 2.0f;
            break;
        case LARGE:
            speed = 1.5f;
            break;
    }

    Asteroid asteroid = {
        .pos = pos,
        .vel = (Velocity){ rotated.x * speed, rotated.y * speed },
        .shape = shape,
        .size = size
    };
    
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