
#include "raylib.h"

#include "game.h"
#include "menu.h"

int main()
{
    const int screenWidth = 1000;
    const int screenHeight = 800;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Asteroids!");

    initMenu(screenWidth, screenHeight);
    initGame(screenWidth, screenHeight);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);

            if (menuState == NEW_GAME) {
                updateGame();
                drawGame();
            } else {
                updateMenu();
                drawMenu();
            }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
