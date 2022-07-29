#include <cstdlib>

#include "raylib.h"

#include "config.h"

//This is a test
#include "Actors/enums.h"
#include "Actors/Prop.h"
#include "Actors/Enemies/Enemy.h"
#include "Actors/Enemies/GangsterFemale.h"
#include "Actors/enums.h"
#include "Actors/Player.h"
#include "Systems/DialogueManager.h"
#include "Scenes/BattleScene.h"
#include "Scenes/MainMenuScene.h"
#include <iostream>
#include <memory>

//Implementing menu
#include <vector>
#include "Scenes/Button.h"

typedef enum GameScreen {TITLESCREEN, MAINMENU, GAME} GameScreen;

int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    // Set target FPS
    SetTargetFPS(60);

    GameScreen currentScreen = TITLESCREEN ;

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Your own initialization code here
    // ...

    //Implementing menu
    MainMenuScene testMain;

    Texture2D myTexture = LoadTexture("assets/graphics/testimage.png");

    // ALL OF THIS IS FOR TEST PURPOSES (implementing and testing player)

    Player player(GetScreenWidth() / 2, GetScreenHeight() / 2, true);

    Texture2D actorTest = LoadTexture("assets/graphics/character/npcIdle/npc2/npc2.png");

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
    pActor = std::make_shared<Actor>(GetScreenWidth() / 4, GetScreenHeight() / 3, actorTest, testDialogue);
    pActor->setName("Test NPC");
    actors.push_back(pActor);
    pActor = std::make_shared<GangsterFemale>(1, 1, Level01, testDialogue);

    actors.push_back(pActor);

    std::shared_ptr<Player> testPlayer = std::make_shared<Player>(1, 1, true);
    std::shared_ptr<Enemy> testEnemy = std::make_shared<GangsterFemale>(1, 1, Level01, testDialogue);
    BattleScene testBattle(testPlayer, testEnemy);

    // END OF TEST


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Updates that are made by frame are coded here

        //still need to implement screens in their respective scene folders...


        switch (currentScreen)
        {
            case TITLESCREEN:
            {
                if(IsKeyPressed(KEY_ENTER))
                {
                    currentScreen = MAINMENU;
                }
                break;
            }

            case MAINMENU:
            {
                //Menu with buttons
                testMain.Update();
                if(testMain.switchScene == true)
                    currentScreen = GAME;
                break;
            }

            case GAME:
            {
                // This is a test

                player.Update();

                player.checkActorCollision(actors);

                player.interact(actors); //This garbage can be solved when we implemented a level-class

                for (int i = 0; i < actors.size(); i++)
                {
                    actors[i]->Update();
                }

                testBattle.Update();

                break;
            }
        }

        // ========== DRAW ==========

        BeginDrawing();
        ClearBackground(WHITE);



        switch (currentScreen)
        {
            case TITLESCREEN:
            {
                DrawText("This is a Titlescreen.\nPress Enter to continue",
                         10, 10, 30, LIGHTGRAY);
                break;
            }

            case MAINMENU:
            {
                testMain.Draw();
                break;
            }

            case GAME:
            {
                testBattle.Draw();
                DrawText("Try using WASD or the arrow keys!\nPress E to interact\nPress E to scroll through dialogue",
                         10, 10, 30, LIGHTGRAY);

                for (int i = 0; i < actors.size(); i++)
                {
                    actors[i]->Draw();
                }

                // This is a test (Implementing player)

                player.Draw();

                break;
            }
        }

        EndDrawing();
    } // Main game loop end

    // De-initialization here



    UnloadTexture(myTexture);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
