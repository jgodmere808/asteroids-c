
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
        (Velocity){ 0, 0 },
        LARGE
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

    updateShip(&game.ship, game.width, game.height);
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
