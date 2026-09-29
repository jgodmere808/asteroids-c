
#include "game.h"
#include "asteroid.h"

#define GAME_WIDTH  1000
#define GAME_HEIGHT 800

#define MAX_ASTEROIDS 128

#define MAX_BULLETS  64
#define BULLET_SPEED 8
#define RESPAWN_INVINCIBILITY 1.0f
#define SHIP_FLASH_RATE 10.0f

enum GameState {
    PLAYING,
    GAME_OVER
};

typedef struct {
    Position pos;
    Velocity vel;
    float lifetime;
} Bullet;

typedef struct _game {
    int lives;
    enum GameState state;
    float shipInvincibleTime;
    Ship ship;
    Asteroid asteroids[MAX_ASTEROIDS];
    int asteroidCount;
    Bullet bullets[MAX_BULLETS];
    int bulletCount;
    int width;
    int height;
} Game;

static Game game;

static void respawnShip()
{
    game.ship = initShip();
    game.shipInvincibleTime = RESPAWN_INVINCIBILITY;

    moveShip(&game.ship, (Position){ GAME_WIDTH / 2, GAME_HEIGHT / 2 });
}

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
            },
            LARGE
        );
    }

    game.asteroidCount = count;
}

static void checkBulletAsteroidCollisions()
{
    int b, a;
    bool hit;
    Asteroid parent, child;
    Asteroid *asteroid;
    Bullet *bullet;
    Vector2 bulletPos, asteroidPos, parentDirection, direction;
    enum AsteroidSize childSize;

    for (b = 0; b < game.bulletCount;) {
        hit = false;

        for (a = 0; a < game.asteroidCount; a++) {
            asteroid = &game.asteroids[a];
            bullet = &game.bullets[b];

            bulletPos = (Vector2){ bullet->pos.x, bullet->pos.y };
            asteroidPos = (Vector2){ asteroid->pos.x, asteroid->pos.y };

            if (!CheckCollisionCircles(
                bulletPos, 2.0f,
                asteroidPos, asteroid->radius
            )) {
                continue;
            }

            // Save the parent before removing it from the array;
            parent = *asteroid;

            game.bullets[b] = game.bullets[--game.bulletCount];
            game.asteroids[a] = game.asteroids[--game.asteroidCount];
            hit = true;

            if (parent.size != SMALL && game.asteroidCount <= MAX_ASTEROIDS - 2) {
                childSize = parent.size == LARGE ? MEDIUM: SMALL;

                parentDirection = Vector2Normalize(
                    (Vector2){ parent.vel.dx, parent.vel.dy }
                );

                for (int side = -1; side <= 1; side += 2) {
                    direction = Vector2Rotate(
                        parentDirection, side * 0.5f
                    );

                    child = createAsteroid(parent.pos, childSize);

                    // Separate the pieces and send them in different directions
                    child.pos.x += direction.x * child.radius;
                    child.pos.y += direction.y * child.radius;
                    child.vel.dx = direction.x * child.speed;
                    child.vel.dy = direction.y * child.speed;

                    game.asteroids[game.asteroidCount++] = child;
                }
            }

            break;
        }

        // A removed bullet was replaced by the last one; check that slot again;
        if (!hit) b++;
    }
}

static void checkShipAsteroidCollision()
{
    int i;
    Vector2 asteroidPos, shipPos;

    if (game.state != PLAYING || game.shipInvincibleTime > 0.0f) return;

    for (i = 0; i < game.asteroidCount; i++) {
        shipPos = (Vector2){
            game.ship.pos.x,
            game.ship.pos.y
        };
        asteroidPos = (Vector2){
            game.asteroids[i].pos.x,
            game.asteroids[i].pos.y
        };

        if (CheckCollisionCircles(
            shipPos, game.ship.radius,
            asteroidPos, game.asteroids[i].radius
        )) {
            game.lives--;

            if (game.lives <= 0) {
                game.state = GAME_OVER;
            } else {
                respawnShip();
            }
            return;
        }
    }
}

void initGame()
{
    game = (Game){
        .lives = 3,
        .state = PLAYING,
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

    if (game.shipInvincibleTime > 0.0f) {
        game.shipInvincibleTime -= GetFrameTime();
        if (game.shipInvincibleTime < 0.0f) game.shipInvincibleTime = 0.0f;
    }

    for (i = 0; i < game.asteroidCount; i++) {
        updateAsteroid(&game.asteroids[i], game.width, game.height);
    }

    updateShip(&game.ship, game.width, game.height);

    if (IsKeyPressed(KEY_SPACE)) fireBullet();
    updateBullets();

    checkShipAsteroidCollision();
    checkBulletAsteroidCollisions();
}

void drawGame()
{
    int i;

    for (i = 0; i < game.asteroidCount; i++) {
        drawAsteroid(&game.asteroids[i]);
    }

    // Flash every tenth of a second while the ship is invincible.
    if (
        game.shipInvincibleTime <= 0.0f ||
        (int)(game.shipInvincibleTime * SHIP_FLASH_RATE) % 2 == 0
    ) {
        if (game.state == PLAYING) drawShip(&game.ship);
    }

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

    // GAME OVER TEXT
    if (game.state == GAME_OVER) {
        DrawText("GAME OVER", (game.width - 380) / 2, (game.height - 100) / 2, 64, WHITE);
    }
}
