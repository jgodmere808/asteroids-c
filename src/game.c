
#include "game.h"

#define GAME_WIDTH  1000
#define GAME_HEIGHT 800

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

    // move ship to center screen
    moveShip(&game.ship, (Position){ GAME_WIDTH / 2, GAME_HEIGHT / 2 });
}

void updateGame()
{
    if (IsKeyDown(KEY_LEFT))  addShipAngle(&game.ship, -0.1f);
    if (IsKeyDown(KEY_RIGHT)) addShipAngle(&game.ship,  0.1f);

    updateShip(&game.ship);
}

void drawGame()
{
    // ship
    drawShip(&game.ship);
}
