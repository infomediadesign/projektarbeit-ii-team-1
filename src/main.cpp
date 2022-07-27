#include <cstdlib>

#include "raylib.h"

#include "config.h"

//This is a test (implementing player)
#include "Actors/Prop.h"
#include "Actors/Enemies/Enemy.h"
#include "Actors/enums.h"
#include "Actors/Player.h"
#include "Systems/DialogueManager.h"
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
    // ...

    //Implementing menu
    std::vector<game::Button*> buttons;
    int active_button = 0;

    auto* button1 = new game::Button(LoadTexture("assets/graphics/ui/combat/Button.png"),
                                     LoadTexture("assets/graphics/ui/combat/Button.png"),
                                     100,
                                     100,
                                     true);

    auto* button2 = new game::Button(LoadTexture("assets/graphics/ui/combat/Button.png"),
                                     LoadTexture("assets/graphics/ui/combat/Button.png"),
                                     100,
                                     200,
                                     false);

    auto* button3 = new game::Button(LoadTexture("assets/graphics/ui/combat/Button.png"),
                                     LoadTexture("assets/graphics/ui/combat/Button.png"),
                                     100,
                                     300,
                                     false);

    buttons.push_back(button1);
    buttons.push_back(button2);
    buttons.push_back(button3);

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
    pActor = std::make_shared<Actor>(GetScreenWidth() / 3, GetScreenHeight() / 3, actorTest, testDialogue);
    pActor->setName("Test NPC");


    actors.push_back(pActor);


    // END OF TEST


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Updates that are made by frame are coded here

        switch (currentScreen)
        {
            case TITLESCREEN:
            {
                IsKeyPressed(KEY_ENTER);
                currentScreen = MAINMENU;
                break;
            }

            case MAINMENU:
            {
                //Menu with buttons
                if (IsKeyPressed(KEY_DOWN))
                {
                    buttons[active_button]->active = false;
                    if (active_button < buttons.size() - 1)
                        active_button++;
                    else active_button = 0;

                    buttons[active_button]->active = true;
                }

                if (IsKeyPressed(KEY_UP))
                {
                    buttons[active_button]->active = false;
                    if (active_button == 0)
                        active_button = (int)buttons.size() - 1;
                    else active_button--;

                    buttons[active_button]->active = true;
                }

                if (IsKeyPressed(KEY_ENTER))
                {
                    currentScreen = GAME;
                    std::cout << "Button Nr. " << active_button << " gedrückt..." << std::endl;
                }
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
                //Why is this code segment unreachable??

                DrawText("This is a Titlescreen.\nPress Enter to continue",
                         10, 10, 30, LIGHTGRAY);
                break;
            }

            case MAINMENU:
            {
                for (auto& button : buttons)
                {
                    DrawText("This is the Main Menu.\nPlease use the arrow keys to select your desired option:",
                             10, 10, 30, LIGHTGRAY);

                    DrawTexture(button->getTexture(), button->pos_x, button->pos_y, WHITE);
                }
                break;
            }

            case GAME:
            {
                DrawText("Try using WASD or the arrow keys!\nPress E to interact\nPress E to scroll through dialogue",
                         10, 10, 30, LIGHTGRAY);

                for (int i = 0; i < actors.size(); i++)
                {
                    actors[i]->Draw();
                }

                // This is a test (Implementing player)

                player.Draw();
            }
        }

        EndDrawing();
    } // Main game loop end

    // De-initialization here
    // ...
    // ...

    delete button1;
    delete button2;
    delete button3;

    UnloadTexture(myTexture);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
