#include <cstdlib>

#include "raylib.h"

#include "config.h"

//This is a test
#include "Actors/enums.h"
#include "Actors/Prop.h"
#include "Actors/Enemies/Enemy.h"

#include "Actors/Enemies/GangsterFemale.h"
#include "Actors/Enemies/Bouncer2.h"
#include "Actors/Enemies/GangsterMale.h"
#include "Actors/Enemies/Bouncer1.h"

#include "Actors/enums.h"
#include "Actors/Player.h"
#include "Systems/DialogueManager.h"
#include "Scenes/BattleScene.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/PauseScene.h"
#include <iostream>
#include <memory>
#include <vector>

typedef enum GameScreen {TITLESCREEN, MAINMENU, MAINOPTIONS, CREDITS, GAME, PAUSEMENU, PAUSEOPTIONS} GameScreen;

int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    // Set target FPS
    SetTargetFPS(60);

    GameScreen currentScreen = TITLESCREEN;


#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Your own initialization code here
    // ...

    //Implementing Logo for Titlescreen
    Image titleScreen = LoadImage("assets/graphics/ui/Logo02.png");
    ImageResize(&titleScreen, 500, 500);
    Texture2D logo = LoadTextureFromImage(titleScreen);
    UnloadImage(titleScreen);

    //Messages
    //for Titlescreen
    const char msg1[100] = "Welcome to the Game!";
    const char msg2[100] = "Please press Enter to continue.";

    //for Main Menu
    //const char msg3[100] = "Please press Enter to continue.";

    //for Options
    const char msg4[100] = "Options";

    //for Credits

    //Font
    Font font1 = LoadFont("assets/graphics/ui/Habbo.ttf");

    Vector2 fontPosition1 = {Game::ScreenWidth/2 - MeasureTextEx(font1, msg1,
                                                                 (float)font1.baseSize, 1).x/2, Game::ScreenHeight - (float)font1.baseSize/2 - 300};
    Vector2 fontPosition2 = {Game::ScreenWidth/2 - MeasureTextEx(font1, msg2,
                                                                 (float)font1.baseSize, 1).x/2, Game::ScreenHeight - (float)font1.baseSize/2 - 250};
    //Vector2 fontPosition3 = {Game::ScreenWidth/2 - MeasureTextEx(font1, msg3,
    //                                                             (float)font1.baseSize, 1).x/2, Game::ScreenHeight - (float)font1.baseSize/2 - 250};
    Vector2 fontPosition4 = {Game::ScreenWidth/2 - MeasureTextEx(font1, msg4,
                                                                 (float)font1.baseSize, 1).x/2, Game::ScreenHeight - (float)font1.baseSize/2 - 250};

    //Implementing menu
    MainMenuScene testMain;
    PauseScene testPause;

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
    std::shared_ptr<Enemy> testEnemy = std::make_shared<Bouncer1>(1, 1, Level01, testDialogue);
    BattleScene testBattle(testPlayer, testEnemy);

    // END OF TEST


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Updates that are made by frame are coded here

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
                testMain.Update();
                if(testMain.switchScene == true)
                    currentScreen = GAME;
                break;
            }

            case MAINOPTIONS:
            {
                if(IsKeyPressed(KEY_ESCAPE))
                {
                    currentScreen = MAINMENU;
                }
                break;
            }

            case CREDITS:
            {
                if(IsKeyPressed(KEY_ESCAPE))
                {
                    currentScreen = MAINMENU;
                }
                break;
            }

            case GAME:
            {
                //Issue: only works once opening the pausemenu, and lets itself close out with enter
                if(IsKeyPressed(KEY_P))
                {
                    currentScreen = PAUSEMENU;
                }

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

            case PAUSEMENU:
            {
                testPause.Update();

                if(testPause.switchScene == true)
                {
                    currentScreen = GAME;
                }

                //how do i integrate condition to open options in pausemenu?
                //maybe something like this?

               /* if(buttonPauseoptions = active_button)
                {
                    currentScreen = PAUSEOPTIONS;
                }*/

                break;
            }

            case PAUSEOPTIONS:
            {
                if(IsKeyPressed(KEY_ESCAPE))
                {
                    currentScreen = PAUSEMENU;
                }
                break;
            }
        }

        // ========== DRAW ==========
        BeginDrawing();
        ClearBackground(BLACK);

        switch (currentScreen)
        {
            case TITLESCREEN:
            {
                DrawTexture(logo, Game::ScreenWidth/2 - logo.width/2, Game::ScreenHeight/4 - logo.height/4, WHITE);

                DrawTextEx(font1, msg1,fontPosition1, font1.baseSize, 1,LIGHTGRAY);
                DrawTextEx(font1, msg2,fontPosition2, font1.baseSize, 1,LIGHTGRAY);

                break;
            }

            case MAINMENU:
            {
                testMain.Draw();
                break;
            }

            case MAINOPTIONS:
            {
                DrawTextEx(font1, msg4,fontPosition4, font1.baseSize, 1,LIGHTGRAY);

                DrawText("Music\n"
                         "SFX\n"
                         "Brightness\n"
                         "Fullscreen\n", Game::ScreenWidth/2, Game::ScreenHeight/4, 50, WHITE);
                //Back (Esc)

                break;
            }

            case CREDITS:
            {
                DrawText("Game Design: Marko Lapadatovic, Leah Berner\n"
                         "Lead Artist: Leah Berner\n"
                         "Artist: Marko Lapadatovic\n"
                         "Lead Programmer: Maximilian Röck\n"
                         "Programmer: Lena White, Sefer Tokdilli\n"
                         "Sound Artist: Maximilian Röck", Game::ScreenWidth/2, Game::ScreenHeight/4, 50, WHITE);
                //Back (Esc)

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

            case PAUSEMENU:
            {
                testPause.Draw();
                break;
            }
        }

        EndDrawing();
    } // Main game loop end

    // De-initialization here

    UnloadTexture(logo);
    UnloadFont(font1);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
