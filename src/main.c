
#include "raylib.h"

#include "game.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Asteroids!");

    initGame();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

            updateGame();
            drawGame();

            ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}