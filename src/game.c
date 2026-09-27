
#include "game.h"

#define GAME_WIDTH  800
#define GAME_HEIGHT 600

typedef struct _ship {
    Position pos;
    Velocity vel;
    Vector2 lines[5];
} Ship;

typedef struct _game {
    Ship *ship;
    int width;
    int height;
} Game;

static Ship ship;
static Game game;

void initGame()
{
    ship = (Ship){
        .pos = { GAME_WIDTH / 2, GAME_HEIGHT / 2 },
        .vel = { 0, 0 },
        .lines = {
            {   0, -30 },  // nose
            {  20,  25 },  // right rear
            {   0,  15 },  // rear notch
            { -20,  25 },  // left rear
            {   0, -30 }   // back to nose
        }
    };

    game = (Game){
        .ship = &ship,
        .width = GAME_WIDTH,
        .height = GAME_HEIGHT
    };
}

void updateGame()
{
    return;
}

void drawGame()
{
    // ship

    DrawLineStrip(
        (Vector2[]){
            { ship.lines[0].x + ship.pos.x, ship.lines[0].y + ship.pos.y },
            { ship.lines[1].x + ship.pos.x, ship.lines[1].y + ship.pos.y },
            { ship.lines[2].x + ship.pos.x, ship.lines[2].y + ship.pos.y },
            { ship.lines[3].x + ship.pos.x, ship.lines[3].y + ship.pos.y },
            { ship.lines[4].x + ship.pos.x, ship.lines[4].y + ship.pos.y }
        },
        5,
        WHITE
    );
}
