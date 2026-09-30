
#include "menu.h"

#define MENU_MAX_ASTEROIDS 10

typedef struct _button {
    Position pos;
    int width;
    int height;
} Button;

typedef struct _menu {
    Asteroid asteroids[MENU_MAX_ASTEROIDS];
    int asteroidCount;
    Button newGameBtn;
    int screenWidth;
    int screenHeight;
} Menu;

static Menu menu;

static void reloadAsteroids(int count)
{
    int i;
    enum AsteroidSize size;
    Position pos;

    for (i = 0; i < count; i++) {
        pos = (Position) {
            GetRandomValue(0, menu.screenWidth),
            GetRandomValue(0, menu.screenHeight)
        };

        size = GetRandomValue(SMALL, LARGE);
        
        menu.asteroids[i] = createAsteroid(pos, size);
    }

    menu.asteroidCount = count;
}

void initMenu(int screenWidth, int screenHeight)
{
    menu = (Menu) {
        .screenWidth = screenWidth,
        .screenHeight = screenHeight,
        .newGameBtn = (Button) {
            .pos = (Position){ 400, 400 },
            .width = 180,
            .height = 30
        }
    };

    menuState = IN_MENU;

    reloadAsteroids(MENU_MAX_ASTEROIDS);
}

void updateMenu()
{
    int i;
    Vector2 mouse = GetMousePosition();

    for (i = 0; i < menu.asteroidCount; i++) {
        updateAsteroid(&menu.asteroids[i], menu.screenWidth, menu.screenHeight);
    }

    // if hovering above button
    if (
        mouse.x >= menu.newGameBtn.pos.x &&
        mouse.x <= menu.newGameBtn.pos.x + menu.newGameBtn.width &&
        mouse.y >= menu.newGameBtn.pos.y &&
        mouse.y <= menu.newGameBtn.pos.y + menu.newGameBtn.height
    ) {
        // is hovering
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            menuState = NEW_GAME;
        }
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}

void drawMenu()
{
    int i;

    for (i = 0; i < menu.asteroidCount; i++) {
        drawAsteroid(&menu.asteroids[i]);
    }

    // TITLE
    DrawText(
        "ASTEROIDS",
        (menu.screenWidth - 755) / 2,
        (menu.screenHeight - 400) / 2,
        128,
        WHITE
    );

    // NEW GAME BUTTON
    DrawText(
        "NEW GAME",
        (menu.screenWidth - 190) / 2,
        (menu.screenHeight - 0) / 2,
        32,
        WHITE
    );
}