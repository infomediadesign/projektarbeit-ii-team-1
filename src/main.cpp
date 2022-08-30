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

#include "Actors/Player.h"
#include "Actors/Dealer.h"
#include "Systems/DialogueManager.h"
#include "Scenes/BattleScene.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/PauseScene.h"
#include "Scenes/CreditScene.h"
#include "Scenes/LevelScene.h"
#include "Scenes/InventoryScene.h"
#include "Scenes/ShopBarkeeper.h"
#include "Scenes/ShopDealer.h"
#include <iostream>
#include <memory>
#include <vector>


int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    // Set target FPS
    SetTargetFPS(60);
    //Window fullscreen
    ToggleFullscreen();

    SetExitKey(KEY_BACKSPACE);

#ifdef GAME_START_FULLSCREEN

#endif

    // Your own initialization code here
    // ...

    GameScreen currentScreen = TITLESCREEN;

    //Titlescreen
    Image titleScreen = LoadImage("assets/graphics/ui/Logo02.png");
    ImageResize(&titleScreen, 500, 500);
    Texture2D logo = LoadTextureFromImage(titleScreen);
    UnloadImage(titleScreen);

    LevelScene testL;

    //Messages
    //for Titlescreen
    const char msg1[100] = "Welcome to the Game!";
    const char msg2[100] = "Please press Enter to continue.";

    //for Options
    const char msg4[100] = "Options";

    //for Credits

    //Font
    Font font1 = LoadFont("assets/graphics/ui/Habbo.ttf");

    //Messages TitleScreen
    Vector2 fontPosition1 = {Game::ScreenWidth/2 - MeasureTextEx(font1, msg1,
                                                                 (float)font1.baseSize, 1).x/2, Game::ScreenHeight - (float)font1.baseSize/2 - 300};
    Vector2 fontPosition2 = {Game::ScreenWidth/2 - MeasureTextEx(font1, msg2,
                                                                 (float)font1.baseSize, 1).x/2, Game::ScreenHeight - (float)font1.baseSize/2 - 250};

    //Messages OptionScreen
    Vector2 fontPosition4 = {Game::ScreenWidth/2 - MeasureTextEx(font1, msg4,
                                                                 (float)font1.baseSize, 1).x/2, Game::ScreenHeight - (float)font1.baseSize/2 - 250};

    //Implementing scenes
    MainMenuScene testMain;
    CreditScene testCredit;
    PauseScene testPause;


    // Level initialisation goes here (use shared pointers!)
    // Maybe you need to use pointers for rooms
    std::shared_ptr<LevelScene> levelTutorial = std::make_shared<LevelScene>();
    std::shared_ptr<LevelScene> level01;
    std::shared_ptr<LevelScene> levelRooftop;

    // Scene management
    std::shared_ptr<Scenes> activeScene = std::make_shared<MainMenuScene>();
    std::shared_ptr<LevelScene> activeLevel;

    // ALL OF THIS IS FOR TEST PURPOSES

    std::shared_ptr<Player> player = std::make_shared<Player>(GetScreenWidth() / 2, GetScreenHeight() / 2, true);

    Texture2D actorTest = LoadTexture("assets/graphics/character/npcIdle/npc2/npc2.png");

    std::vector<std::shared_ptr<Prop>> props;
    std::vector<std::shared_ptr<Actor>> actors;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Barkeeper>> barkeepers;
    std::vector<std::shared_ptr<Dealer>> dealers;
    std::vector<std::shared_ptr<Actor>> allActors;
    std::shared_ptr<Prop> pProp;
    std::shared_ptr<Actor> pActor;
    std::shared_ptr<Enemy> pEnemy;
    std::shared_ptr<Barkeeper> pBarkeeper;
    std::shared_ptr<Dealer> pDealer;

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
    allActors.push_back(pActor);
    pEnemy = std::make_shared<GangsterFemale>(500, 200, Level01, testDialogue);
    enemies.push_back(pEnemy);
    allActors.push_back(pEnemy);
    pBarkeeper = std::make_shared<Barkeeper>(1000, 700, testDialogue);
    barkeepers.push_back(pBarkeeper);
    allActors.push_back(pBarkeeper);
    pDealer = std::make_shared<Dealer>(1200, 800, testDialogue);
    dealers.push_back(pDealer);
    allActors.push_back(pDealer);





    std::shared_ptr<Enemy> enemyPtr;
    std::shared_ptr<Barkeeper> barkeeperPtr;

    //std::shared_ptr<Player> testPlayer = std::make_shared<Player>(1, 1, true);
    //std::shared_ptr<Enemy> testEnemy = std::make_shared<Bouncer1>(1, 1, Level01, testDialogue);
    //BattleScene testBattle(testPlayer, testEnemy);

    // END OF TEST


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // ========== UPDATE ==========

        // Scene transition
        if (activeScene->switchScene == true)
        {
            activeScene->switchScene = false;
            currentScreen = activeScene->switchTo;

            switch (activeScene->switchTo)
            {
                case MAINMENU:
                {
                    activeScene = std::make_shared<MainMenuScene>();
                    //if(testMain.switchScene == true)
                    //    currentScreen = GAME;
                    break;
                }

                case MAINOPTIONS:
                {
                    // Should be moved to scene update / into a class
                    if(IsKeyPressed(KEY_ESCAPE))
                    {
                        currentScreen = MAINMENU;
                    }
                    break;
                }


                case CREDITS:
                {
                    activeScene = std::make_shared<CreditScene>();
                    // Should be moved to scene update / into a class
                    if(IsKeyPressed(KEY_ESCAPE))
                    {
                        currentScreen = MAINMENU;
                    }
                    break;
                }

                case GAME:
                {
                    activeScene = activeLevel;



                    /* All of this has to go to LevelScene.Update()!!

                    //Issue: only works once opening the pausemenu, and lets itself close out with enter
                    if(IsKeyPressed(KEY_P))
                    {
                        this->switchScene = true;
                        this->switchTo = PAUSEMENU;
                    }

                    // This is a test

                    player.Update();

                    player.checkActorCollision(actors);

                    player.interact(actors); //This garbage can be solved when we implemented a level-class

                    for (int i = 0; i < actors.size(); i++)
                    {
                        actors[i]->Update();
                    }
                    */
                    break;
                }
                case BATTLE:
                    // Extract player and enemy from active level
                    // Then make a new shared pointer with the extracted actors

                    // Hardcoded for now
                    enemyPtr = player->enemyToFight;
                    activeScene = std::make_shared<BattleScene>(player, enemyPtr);
                    break;
                case SHOP_BARKEEPER:
                    // Extract player and barkeeper from active level
                    // Then make a new shared pointer with the extracted actors

                    activeScene = std::make_shared<ShopBarkeeper>(player, player->barkeeperPtr);
                    break;
                case SHOP_DEALER:
                    // Extract player from active level
                    // Then make a new shared pointer with the extracted actor

                    activeScene = std::make_shared<ShopDealer>(player);
                    break;
                case PAUSEMENU:
                {
                    activeScene = std::make_shared<PauseScene>();

                    /* All of this has to go to PauseScene.Update()!
                    if(testPause.switchScene == true)
                    {
                        currentScreen = GAME;
                    }

                    //how do i integrate condition to open options in pausemenu?
                    //maybe something like this?

                    if(buttonPauseoptions == active_button)
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
                case TESTSCENE:
                {
                    // This is a test

                    break;
                }
                case INVENTORY:
                {
                   activeScene = std::make_shared<InventoryScene>();

                }
                case SKILLTHREE:
                {
                    activeScene = std::make_shared<SkillTreeScene>();
                }
            }

        }

        // Scene update
        if (currentScreen != TITLESCREEN)
            // TEMPORARY?
            if (currentScreen == TESTSCENE) {

                // This is going to be moved to LevelScene::Update()
                player->Update();


                // Check if a shop has to be opened
                if(player->openShopBarkeeper == true && player->dialogueManager.dialoguePlaying == false)
                {
                    TraceLog(LOG_INFO, "Opening shop...");
                    player->openShopBarkeeper = false;

                    // This is hardcoded for now, because the level class isn't ready yet
                    activeScene->switchTo = SHOP_BARKEEPER;
                    activeScene->switchScene = true;
                }
                if(player->openShopDealer == true && player->dialogueManager.dialoguePlaying == false)
                {
                    TraceLog(LOG_INFO, "Opening shop...");
                    player->openShopDealer = false;


                    // This is hardcoded for now, because the level class isn't ready yet (would be this->switchTo, etc.)
                    activeScene->switchTo = SHOP_DEALER;
                    activeScene->switchScene = true;
                }
                // Check if a fight has to be started
                if(player->startCombat == true && player->dialogueManager.dialoguePlaying == false)
                {
                    TraceLog(LOG_INFO, "Starting combat...");
                    player->startCombat = false;
                    // Start combat with player and player->enemyToFight
                    // Has to remember the player's position in the level before battle!


                    // This is hardcoded for now, because the level class isn't ready yet
                    activeScene->switchTo = BATTLE;
                    activeScene->switchScene = true;
                }

                player->checkActorCollision(allActors);

                // Check enemy aggro radius collision (maybe move this into a method of the level-class
                bool stopSearch = false;
                for (int i = 0; i < enemies.size() && stopSearch == false && player->dialogueManager.dialoguePlaying == false; i++)
                {
                    if (CheckCollisionCircleRec({enemies[i]->position.x + enemies[i]->frameRec.width / 2, enemies[i]->position.y + enemies[i]->frameRec.height / 2},
                                                enemies[i]->aggroRadius, player->collisionBox) && enemies[i]->defeated == false)
                    {
                        player->interactionForced(enemies[i]);
                        stopSearch = true;
                    }
                }

                player->interact(actors);
                player->interact(enemies);
                player->interact(barkeepers);
                player->interact(dealers);

                for (int i = 0; i < actors.size(); i++) {
                    actors[i]->Update();
                }
                for (int i = 0; i < enemies.size(); i++) {
                    enemies[i]->Update();
                }
                for (int i = 0; i < barkeepers.size(); i++) {
                    barkeepers[i]->Update();
                }
                for (int i = 0; i < dealers.size(); i++) {
                    dealers[i]->Update();
                }
            } else {
                {
                    activeScene->Update();
                }
            }
        else
        {
            if(IsKeyPressed(KEY_ENTER))
            {
                currentScreen = MAINMENU;
            }
        }



        // ========== DRAW ==========
        BeginDrawing();
        ClearBackground(BLACK);

        if (currentScreen != TITLESCREEN) {
            // TEMPORARY
            if (currentScreen == TESTSCENE) {
                levelTutorial->Draw();

                for (int i = 0; i < actors.size(); i++) {
                    actors[i]->Draw();
                }
                for (int i = 0; i < enemies.size(); i++) {
                    enemies[i]->Draw();
                }
                for (int i = 0; i < barkeepers.size(); i++) {
                    barkeepers[i]->Draw();
                }
                for (int i = 0; i < dealers.size(); i++) {
                    dealers[i]->Draw();
                }
                // Draw player after NPCs
                player->Draw();

            } else {
                if (activeScene->drawLevelBackground == true) {
                    activeLevel->Draw();
                }
                activeScene->Draw();
            }
        }
        else
        {
            DrawTexture(logo, Game::ScreenWidth/2 - logo.width/2, Game::ScreenHeight/4 - logo.height/4, WHITE);

            DrawTextEx(font1, msg1,fontPosition1, font1.baseSize, 1,WHITE);
            DrawTextEx(font1, msg2,fontPosition2, font1.baseSize, 1,WHITE);
        }

        /*
        switch (currentScreen)
        {
            case TITLESCREEN:
            {
                DrawTexture(logo, Game::ScreenWidth/2 - logo.width/2, Game::ScreenHeight/4 - logo.height/4, WHITE);

                DrawTextEx(font1, msg1,fontPosition1, font1.baseSize, 1,WHITE);
                DrawTextEx(font1, msg2,fontPosition2, font1.baseSize, 1,WHITE);

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
                testCredit.Draw();
                //Back (Esc)

                break;
            }

            case GAME:
            {
                //testBattle.Draw();
                testL.DrawMap();

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
        */
        EndDrawing();
    } // Main game loop end

    // De-initialization here

    UnloadTexture(logo);
    UnloadFont(font1);
    testMain.Unload();
    testCredit.Unload();
    testPause.Unload();

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
