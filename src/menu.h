#pragma once

#include "raylib.h"
#include "asteroid.h"

enum MenuState {
    IN_MENU,
    NEW_GAME
};

enum MenuState menuState;

void initMenu(int screenWidth, int screenHeight);
void updateMenu();
void drawMenu();