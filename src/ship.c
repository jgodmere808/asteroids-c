
#include "ship.h"

static int thrusting = 0;

Ship initShip()
{
    return (Ship){
        .pos = { 0, 0 },
        .vel = { 0, 0 },
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

void addShipAngle(Ship *ship, float angle)
{
    ship->angle += angle;
}

void updateShip(Ship *ship)
{
    if (IsKeyDown(KEY_UP)) {
        thrusting = 1;
    } else {
        thrusting = 0;
    }
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
