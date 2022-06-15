#include <cstdlib>

#include "raylib.h"

#include "config.h"

//This is a test (implementing player)
#include "Actors/Prop.h"
#include "Actors/Enemy.h"
#include "Actors/Player.h"
#include <iostream>
#include <memory>

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

    // ALL OF THIS IS FOR TEST PURPOSES (implementing and testing player)

    Player player(GetScreenWidth() / 2, GetScreenHeight() / 2, myTexture);

    Actor testActor;
    testActor.setName("Manuel Neuer (Test NPC)");
    testActor.position.x = GetScreenWidth() / 3;
    testActor.position.y = GetScreenHeight() / 3;
    testActor.activeTexture = LoadTexture("assets/graphics/testBouncer.png");

    std::vector<Actor> actors;
    actors.push_back(testActor);

    // END OF TEST


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Updates that are made by frame are coded here
        // ...
        // ...

        // This is a test

            player.Update();
        //std::cout << "[DEBUG] Called Update" << std::endl;
            player.interact(actors); //This garbage can be solved when we implemented a level-class

        BeginDrawing();
            // You can draw on the screen between BeginDrawing() and EndDrawing()
            // ...
            // ...
            ClearBackground(WHITE);
            DrawText("Try using WASD or the arrow keys!\nPress E to interact", 10, 10, 30, LIGHTGRAY);


            // This is a test (Implementing player)

            /* Doesn't work for some reason...
            for(int i = 0; i < actors.size(); i++)
            {
                DrawTexture(actors[i].activeTexture, actors[i].position.x, actors[i].position.y, WHITE);
            }
            */
            DrawTexture(player.activeTexture, player.position.x, player.position.y, WHITE);
            DrawRectangleLines(player.collisionBox.x, player.collisionBox.y, player.collisionBox.width, player.collisionBox.height,
                               GREEN);

        DrawCircleLines(testActor.position.x + (testActor.activeTexture.width / 2),
                       testActor.position.y + (testActor.activeTexture.width / 2),
                        testActor.interactionRadius, RED);
            DrawTexture(testActor.activeTexture, testActor.position.x, testActor.position.y, WHITE);

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
