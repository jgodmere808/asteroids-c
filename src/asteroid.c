
#include "asteroid.h"

#define ASTEROID_LINES 11

Asteroid createAsteroid(Position pos, Velocity vel)
{
    int i;
    enum AsteroidShape shape =
        (enum AsteroidShape)GetRandomValue(SHAPE_ONE, SHAPE_THREE);

    Asteroid asteroid = {
        .pos = pos,
        .vel = vel,
        .shape = shape
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
    return;
}

void drawAsteroid(Asteroid *asteroid)
{
    int i;
    Vector2 posLines[ASTEROID_LINES];

    for (i = 0; i < ASTEROID_LINES; i++) {
        posLines[i] = (Vector2){
            asteroid->lines[i].x + asteroid->pos.x,
            asteroid->lines[i].y + asteroid->pos.y
        };
    }

    DrawLineStrip(posLines, ASTEROID_LINES, WHITE);
}