#include <cstdlib>

#include "raylib.h"

#include "config.h"

//This is a test (implementing player)
#include "Actors/Prop.h"
#include "Actors/Enemy.h"
#include "Actors/Player.h"

int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    // Set target FPS
    SetTargetFPS(60);
    // Sets the window to full screen
    ToggleFullscreen();

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Your own initialization code here
    // ...
    // ...
    Texture2D myTexture = LoadTexture("assets/graphics/testimage.png");



    // ALL OF THIS IS FOR TEST PURPOSES (implementing player)

    Player player;
    player.posX = GetScreenWidth() / 2;
    player.posY = GetScreenHeight() / 2;
    player.activeTexture = myTexture;

    // END OF TEST


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Updates that are made by frame are coded here
        // ...
        // ...

        // This is a test (implementing player)
        player.move();



        BeginDrawing();
            // You can draw on the screen between BeginDrawing() and EndDrawing()
            // ...
            // ...
            ClearBackground(WHITE);
            DrawText("Try using WASD or the arrow keys!", 10, 10, 30, LIGHTGRAY);
            DrawTexture(myTexture, 10, 100, WHITE);

            // This is a test (Implementing player)
            DrawTexture(player.activeTexture, player.posX, player.posY, WHITE);


        EndDrawing();
    } // Main game loop end

    // De-initialization here
    // ...
    // ...
    UnloadTexture(myTexture);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
