
#include "game.h"
#include "asteroid.h"
#include <stdio.h>

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

static void reloadAsteroids(int count)
{
    int i;
    float angle;
    Vector2 rotated;

    for (i = 0; i < count; i++) {
        angle = GetRandomValue(0, 359) * DEG2RAD;
        rotated = Vector2Rotate((Vector2){ 0, -1.0f }, angle);

        printf("%.2f, %.2f, %.2f\n", angle, rotated.x, rotated.y);

        game.asteroids[i] = createAsteroid(
            (Position){
                game.width / 2,
                game.height / 2
            },
            (Velocity){
                rotated.x,
                rotated.y
            },
            LARGE
        );
    }

    game.asteroidCount = count;
}

void initGame()
{
    game = (Game){
        .ship = initShip(),
        .asteroidCount = 1,
        .width = GAME_WIDTH,
        .height = GAME_HEIGHT
    };

    // move ship to center screen
    moveShip(&game.ship, (Position){ GAME_WIDTH / 2, GAME_HEIGHT / 2 });

    reloadAsteroids(6);
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
