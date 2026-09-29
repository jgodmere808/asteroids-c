
#include "game.h"
#include "asteroid.h"

#define GAME_WIDTH  1000
#define GAME_HEIGHT 800

#define MAX_ASTEROIDS 128

typedef struct _game {
    Ship ship;
    Asteroid asteroids[MAX_ASTEROIDS];
    int asteroidCount;
    int width;
    int height;
} Game;

static Game game;

void initGame()
{
    game = (Game){
        .ship = initShip(),
        .asteroidCount = 1,
        .width = GAME_WIDTH,
        .height = GAME_HEIGHT
    };

    game.asteroids[0] = createAsteroid(
        (Position){ game.width / 2, game.height / 2 },
        (Velocity){ 0, 0 }
    );

    // move ship to center screen
    moveShip(&game.ship, (Position){ GAME_WIDTH / 2, GAME_HEIGHT / 2 });
}

void updateGame()
{
    int i;

    for (i = 0; i < game.asteroidCount; i++) {
        updateAsteroid(&game.asteroids[i]);
    }

    updateShip(&game.ship);

    // if ship crosses outside map, respawn on other side
    if (game.ship.pos.x < 0) game.ship.pos.x = game.width;
    if (game.ship.pos.x > game.width) game.ship.pos.x = 0;
    if (game.ship.pos.y < 0) game.ship.pos.y = game.height;
    if (game.ship.pos.y > game.height) game.ship.pos.y = 0;
}

void drawGame()
{
    int i;

    for (i = 0; i < game.asteroidCount; i++) {
        drawAsteroid(&game.asteroids[i]);
    }

    // ship
    drawShip(&game.ship);
}
