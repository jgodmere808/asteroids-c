
#include "ship.h"

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
        }
    };
}

void moveShip(Ship *ship, Position pos)
{
    ship->pos = pos;
}

void drawShip(Ship *ship)
{
    DrawLineStrip(
        (Vector2[]){
            { ship->lines[0].x + ship->pos.x, ship->lines[0].y + ship->pos.y },
            { ship->lines[1].x + ship->pos.x, ship->lines[1].y + ship->pos.y },
            { ship->lines[2].x + ship->pos.x, ship->lines[2].y + ship->pos.y },
            { ship->lines[3].x + ship->pos.x, ship->lines[3].y + ship->pos.y },
            { ship->lines[4].x + ship->pos.x, ship->lines[4].y + ship->pos.y }
        },
        5,
        WHITE
    );
}