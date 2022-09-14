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

#include "Scenes/TutorialLevelScene.h"
#include "Scenes/TitleScreen.h"
#include "Scenes/MainOptions.h"
#include "Scenes/BattleScene.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/PauseScene.h"
#include "Scenes/PauseOptions.h"
#include "Scenes/CreditScene.h"
#include "Scenes/LevelScene.h"
#include "Scenes/InventoryScene.h"
#include "Scenes/ShopBarkeeper.h"
#include "Scenes/ShopDealer.h"
#include "Scenes/SkillTreeScene.h"
#include "Items/PunchGun.h"

#include <iostream>
#include <memory>
#include <vector>

// Sound / music volume
float volSfx = 1;
float volMusic = 0.75;

int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);

    InitAudioDevice();

    // Set target FPS
    SetTargetFPS(60);
    //Set Window titel
    const char gameTitel[] = "Disco Undercover";
    SetWindowTitle(gameTitel);
    //Set Window icon
    Image gameIcon = LoadImage("./assets/graphics/UI/Logo02.png");
    SetWindowIcon(gameIcon);
    //Set window exit key
    SetExitKey(KEY_BACKSPACE);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    //Font
    Font font1 = LoadFont("assets/graphics/ui/Habbo.ttf");

    //Implementing scenes
    TitleScreen testTitle;
    MainMenuScene testMain;
    MainOptions testMainOps;
    CreditScene testCredit;
    PauseScene testPause;
    PauseOptions testPauseOps;

    // Enums
    LevelRooms levelRooms;


    // ===== PLAYER INIT =====
    std::shared_ptr<Player> player = std::make_shared<Player>(GetScreenWidth() / 2, GetScreenHeight() / 2, true);

    // ========== LEVEL INITIALISATION ==========

    //  ----- Tutorial initialisation -----
    // Levelscene
    std::shared_ptr<LevelScene> levelTutorial = std::make_shared<LevelScene>(Wardrobe);
    levelTutorial->player = player;
    /*std::shared_ptr<Actor> pActor;
    Texture2D actorTest = LoadTexture("assets/graphics/character/npcIdle/npc2/npc2.png");
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
    std::vector<int> switches = {0, 2, 3};
    pActor->setDiaSwitches(switches);




    levelTutorial->actors.push_back(pActor);
    levelTutorial->allActors.push_back(pActor);
    std::shared_ptr<Enemy> pEnemy = std::make_shared<GangsterFemale>(500, 200, Level01, testDialogue);
    levelTutorial->enemies.push_back(pEnemy);
    levelTutorial->allActors.push_back(pEnemy);
    std::shared_ptr<Barkeeper> pBarkeeper = std::make_shared<Barkeeper>(1000, 700, testDialogue);
    levelTutorial->barkeepers.push_back(pBarkeeper);
    levelTutorial->allActors.push_back(pBarkeeper);
    std::shared_ptr<Dealer> pDealer = std::make_shared<Dealer>(1200, 800, testDialogue);
    levelTutorial->dealers.push_back(pDealer);
    levelTutorial->allActors.push_back(pDealer);
    Vector2 posi = {400, 400};
    levelTutorial->items.push_back(std::make_shared<PunchGun>(posi));*/

    std::shared_ptr<LevelScene> level01;
    std::shared_ptr<LevelScene> levelRooftop;

    // Scene management
    std::shared_ptr<Scenes> activeScene = std::make_shared<TitleScreen>();
    std::shared_ptr<LevelScene> activeLevel = levelTutorial;

    // ALL OF THIS IS FOR TEST PURPOSES

    std::shared_ptr<Enemy> enemyPtr;
    std::shared_ptr<Barkeeper> barkeeperPtr;

    player->money = player->money + 2000;

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
        if (activeScene->switchScene)
        {
            TraceLog(LOG_INFO, "scene switch request");
            activeScene->switchScene = false;

            switch (activeScene->switchTo)
            {
                case TITLESCREEN:
                {
                    activeScene = std::make_shared<TitleScreen>();
                    break;
                }

                case MAINMENU:
                {
                    activeScene = std::make_shared<MainMenuScene>();
                    break;
                }

                case MAINOPTIONS:
                {
                    activeScene = std::make_shared<MainOptions>();
                    break;
                }

                case CREDITS:
                {
                    activeScene = std::make_shared<CreditScene>();
                    break;
                }

                case GAME:
                {
                    activeScene = activeLevel;
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
                    break;
                }

                case PAUSEOPTIONS:
                {
                    activeScene = std::make_shared<PauseOptions>();
                    break;
                }

                case INVENTORY:
                {
                    activeScene->switchScene = false;
                    activeScene = std::make_shared<InventoryScene>(player);
                    break;
                }

                case SKILLTREE:
                {
                    activeScene->switchScene = false;
                    activeScene = std::make_shared<SkillTreeScene>(player);
                    break;
                }
            }
        }
        }

        // Scene update
        activeScene->Update();


        // ========== DRAW ==========
        BeginDrawing();
        ClearBackground(BLACK);


        if (activeScene->drawLevelBackground == true)
        {
            activeLevel->Draw();
        }
        activeScene->Draw();

        EndDrawing();
    } // Main game loop end

    // De-initialization here
    UnloadFont(font1);
    testTitle.Unload();
    testMain.Unload();
    testMainOps.Unload();
    testCredit.Unload();
    testPause.Unload();
    testPauseOps.Unload();

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}