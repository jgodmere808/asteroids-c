
#include "game.h"
#include "asteroid.h"

#define GAME_WIDTH  1000
#define GAME_HEIGHT 800

#define MAX_ASTEROIDS 128

#define MAX_BULLETS  64
#define BULLET_SPEED 8

typedef struct {
    Position pos;
    Velocity vel;
    float lifetime;
} Bullet;

typedef struct _game {
    Ship ship;
    Asteroid asteroids[MAX_ASTEROIDS];
    int asteroidCount;
    Bullet bullets[MAX_BULLETS];
    int bulletCount;
    int width;
    int height;
} Game;

static Game game;

static void fireBullet()
{
    if (game.bulletCount >= MAX_BULLETS) return;

    Vector2 forward = Vector2Rotate(
        (Vector2){ 0, -1.0f },
        game.ship.angle
    );

    game.bullets[game.bulletCount++] = (Bullet) {
        .pos = {
            game.ship.pos.x + forward.x * 30,
            game.ship.pos.y + forward.y * 30
        },
        .vel = {
            game.ship.vel.dx + forward.x * BULLET_SPEED,
            game.ship.vel.dy + forward.y * BULLET_SPEED
        },
        .lifetime = 90
    };
}

static void updateBullets()
{
    int i;

    for (i = 0; i < game.bulletCount;) {
        Bullet *bullet = &game.bullets[i];

        bullet->pos.x += bullet->vel.dx;
        bullet->pos.y += bullet->vel.dy;
        bullet->lifetime -= 1;

        if (bullet->lifetime <= 0) {
            game.bullets[i] = game.bullets[--game.bulletCount];
        } else {
            i++;
        }
    }
}

static void reloadAsteroids(int count)
{
    int i;

    for (i = 0; i < count; i++) {
        game.asteroids[i] = createAsteroid(
            (Position){
                game.width / 2,
                game.height / 2
            }
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
        updateAsteroid(&game.asteroids[i], game.width, game.height);
    }

    updateShip(&game.ship, game.width, game.height);

    if (IsKeyPressed(KEY_SPACE)) fireBullet();
    updateBullets();
}

void drawGame()
{
    int i;

    for (i = 0; i < game.asteroidCount; i++) {
        drawAsteroid(&game.asteroids[i]);
    }

    // ship
    drawShip(&game.ship);

    // bullets
    for (i = 0; i < game.bulletCount; i++) {
        DrawCircleV(
            (Vector2){
                game.bullets[i].pos.x,
                game.bullets[i].pos.y
            },
            2,
            WHITE
        );
    }
}
