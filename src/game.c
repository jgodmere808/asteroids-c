
#include "game.h"

#define GAME_WIDTH  1000
#define GAME_HEIGHT 800

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
    updateShip(&game.ship);

    // if ship crosses outside map, respawn on other side
    if (game.ship.pos.x < 0) game.ship.pos.x = game.width;
    if (game.ship.pos.x > game.width) game.ship.pos.x = 0;
    if (game.ship.pos.y < 0) game.ship.pos.y = game.height;
    if (game.ship.pos.y > game.height) game.ship.pos.y = 0;
}

void drawGame()
{
    // ship
    drawShip(&game.ship);
}
