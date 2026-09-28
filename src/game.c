
#include "game.h"

#define GAME_WIDTH  800
#define GAME_HEIGHT 600

typedef struct _asteroid {
    Position pos;
    Velocity vel;
    Vector2 lines[11];
} Asteroid;

typedef struct _game {
    Ship ship;
    int width;
    int height;
} Game;

static Game game;

void initGame()
{
    game = (Game){
        .ship = initShip(),
        .width = GAME_WIDTH,
        .height = GAME_HEIGHT
    };
}

void updateGame()
{
    if (IsKeyDown(KEY_LEFT))  addShipAngle(&game.ship, -0.1f);
    if (IsKeyDown(KEY_RIGHT)) addShipAngle(&game.ship,  0.1f);
}

void drawGame()
{
    // ship
    drawShip(&game.ship);
}
