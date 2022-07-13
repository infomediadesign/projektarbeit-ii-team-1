#include <cstdlib>

#include "raylib.h"

#include "config.h"

//This is a test (implementing player)
#include "Actors/Prop.h"
#include "Actors/Enemy.h"
#include "Actors/Player.h"
#include "Systems/DialogueManager.h"
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
    Texture2D spritesheetTest = LoadTexture("assets/graphics/testSpritesheet.png");

    // ALL OF THIS IS FOR TEST PURPOSES (implementing and testing player)

    Player player(GetScreenWidth() / 2, GetScreenHeight() / 2, spritesheetTest);

    Texture2D bouncerTest = LoadTexture("assets/graphics/npcSpritesheet.png");

    std::vector<std::shared_ptr<Actor>> actors;
    std::shared_ptr<Actor> pActor;

    std::vector<std::string> testDialogue =
            {
                    "This is a test line!",
                    "Test lines are great for testing the \ndialogue system!",
                    "I sure hope it works...",
                    "...",
                    "Still scrolling, huh?",
                    "Well that's okay.",
                    "It's not like the game will crash or anything...",
                    "... I hope."
            };
    pActor = std::make_shared<Actor>(GetScreenWidth() / 3, GetScreenHeight() / 3, bouncerTest, testDialogue);
    pActor->setName("Test NPC");


    actors.push_back(pActor);


    // END OF TEST


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Updates that are made by frame are coded here
        // ...
        // ...

        // This is a test

        player.Update();

        player.checkActorCollision(actors);

        player.interact(actors); //This garbage can be solved when we implemented a level-class

        for (int i = 0; i < actors.size(); i++)
        {
            actors[i]->Update();
        }


        // ========== DRAW ==========

        BeginDrawing();

        ClearBackground(WHITE);
        DrawText("Try using WASD or the arrow keys!\nPress E to interact\nPress E to scroll through dialogue",
            10, 10, 30, LIGHTGRAY);


        for (int i = 0; i < actors.size(); i++)
        {
            actors[i]->Draw();
        }


        // This is a test (Implementing player)

        player.Draw();

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
