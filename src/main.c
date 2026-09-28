
#include "raylib.h"

#include "game.h"

int main()
{
    const int screenWidth = 1000;
    const int screenHeight = 800;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
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