
#include "ship.h"

static int thrusting = 0;

Ship initShip()
{
    return (Ship){
        .pos = { 0, 0 },
        .vel = { 0, 0 },
        .angle = 0,
        .lines = {
            {   0, -30 },  // nose
            {  20,  25 },  // right rear
            {   0,  15 },  // rear notch
            { -20,  25 },  // left rear
            {   0, -30 }   // back to nose
        },
        .thrustLines = {
            { -8, 20 },  // left base
            {  0, 45 },  // flame tip
            {  8, 20 },  // right base
            { -8, 20 }   // close triangle
        }
    };
}

void moveShip(Ship *ship, Position pos)
{
    ship->pos = pos;
}

static void addShipAngle(Ship *ship, float angle)
{
    ship->angle += angle;
}

static void addShipVelocity(Ship *ship, Velocity vel)
{
    ship->vel.dx += vel.dx;
    ship->vel.dy += vel.dy;
}

void updateShip(Ship *ship, int gameWidth, int gameHeight)
{
    float nextX, nextY;

    // rotate ship
    if (IsKeyDown(KEY_LEFT))  addShipAngle(ship, -0.1f);
    if (IsKeyDown(KEY_RIGHT)) addShipAngle(ship,  0.1f);

    // thrust boolean
    if (IsKeyDown(KEY_UP)) {
        thrusting = 1;
    } else {
        thrusting = 0;
    }

    // thrust velocity
    if (IsKeyDown(KEY_UP)) {
        Vector2 forward = Vector2Rotate((Vector2){ 0.0f, -1.0f }, ship->angle);
        Velocity change = { forward.x * 0.1f, forward.y * 0.1f };
        addShipVelocity(ship, change);
    } else {
        // drag, slows down the ship
        ship->vel.dx *= 0.99f;
        ship->vel.dy *= 0.99f;
    }

    // if ship crosses outside map, respawn on other side
    if (ship->pos.x < 0) ship->pos.x = gameWidth;
    if (ship->pos.x > gameWidth) ship->pos.x = 0;
    if (ship->pos.y < 0) ship->pos.y = gameHeight;
    if (ship->pos.y > gameHeight) ship->pos.y = 0;

    nextX = ship->pos.x + ship->vel.dx;
    nextY = ship->pos.y + ship->vel.dy;

    moveShip(ship, (Position){ nextX, nextY });
}

void drawShip(Ship *ship)
{
    Vector2 shipPoints[5];

    for (int i = 0; i < 5; i++) {
        Vector2 rotated = Vector2Rotate(ship->lines[i], ship->angle);
        shipPoints[i] = (Vector2){ rotated.x + ship->pos.x, rotated.y + ship->pos.y };
    }

    // Ship
    DrawLineStrip(shipPoints, 5, WHITE);

    // Thrust
    if (thrusting) {
        Vector2 thrustPoints[4];

        for (int i = 0; i < 4; i++) {
            Vector2 rotated = Vector2Rotate(ship->thrustLines[i], ship->angle);
            thrustPoints[i] = (Vector2){ rotated.x + ship->pos.x, rotated.y + ship->pos.y };
        }

        DrawLineStrip(thrustPoints, 4, WHITE);
    }
}
