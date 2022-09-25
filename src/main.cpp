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
#include "Scenes/MainControls.h"
#include "Scenes/BattleScene.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/PauseScene.h"
#include "Scenes/PauseOptions.h"
#include "Scenes/PauseControls.h"
#include "Scenes/CreditScene.h"
#include "Scenes/LevelScene.h"
#include "Scenes/InventoryScene.h"
#include "Scenes/ShopBarkeeper.h"
#include "Scenes/ShopDealer.h"
#include "Scenes/SkillTreeScene.h"
#include "Items/PunchGun.h"
#include "Items/Note.h"

#include <iostream>
#include <memory>
#include <vector>

// Sound / music volume
float volSfx = 1;
float volMusic = 0.75;

//Screen brightness
float brightness = 0;

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

    // Enums
    LevelRooms currentLevelRooms = TutorialLevel;
    Level currentLevel = Tutorial;


    // ===== PLAYER INIT =====
    std::shared_ptr<Player> playerPointer = std::make_shared<Player>(0 ,0, false);


    // Victory animation init
    bool playVictoryAnim = false;
    int victoryFramesCounter = 0;
    int victoryCurrentFrame = 0;
    Texture2D victoryTex = LoadTexture("assets/graphics/ui/combat/victory.png");
    Rectangle victoryRec;
    victoryRec.x = 0;
    victoryRec.y = 0;
    victoryRec.width = victoryTex.width / 8;
    victoryRec.height = victoryTex.height;

    // ===== LEVEL POINTER =====
    std::shared_ptr<LevelScene> tutorialLevelScene;

    std::shared_ptr<LevelScene> lvl01Wardrobe;
    std::shared_ptr<LevelScene> lvl01VipRoom;
    std::shared_ptr<LevelScene> lvl01Storage;
    std::shared_ptr<LevelScene> lvl01DanceFloor;
    std::shared_ptr<LevelScene> lvl01Floor;
    std::shared_ptr<LevelScene> lvl01WcWoman;
    std::shared_ptr<LevelScene> lvl01WcMan;

    std::shared_ptr<LevelScene> lvl02FirstRoom;
    std::shared_ptr<LevelScene> lvlRoofTop;


    // ========== LEVEL INITIALISATION ==========
    playerPointer->position = {100, 580};
    tutorialLevelScene = std::make_shared<TutorialLevelScene>(currentLevel, "tutorial", playerPointer);


    /*switch (currentLevel) {
        case Tutorial:
            tutorialLevelScene = std::make_shared<TutorialLevelScene>(playerPointer);
            break;

        case Level01:
            //lvl01Wardrobe
            lvl01Wardrobe = std::make_shared<LevelScene>(currentLevel, "wardrobe",playerPointer);
            //lvl01Wardrobe->items.push_back(std::make_shared<Note>(1,Vector2{120.0,340.0}));
            //lvl01Wardrobe->items.push_back(std::make_shared<Note>(2,Vector2{340.0,340.0}));

            // lvl01VipRoom
            lvl01VipRoom = std::make_shared<LevelScene>(currentLevel, "vipRoom",playerPointer);

            // lvl01Storage
            lvl01Storage = std::make_shared<LevelScene>(currentLevel, "storageRoom",playerPointer);
            //lvl01Wardrobe->items.push_back(std::make_shared<Note>(3,Vector2{340.0,340.0}));

            // lvl01MainRoom
            lvl01DanceFloor = std::make_shared<LevelScene>(currentLevel, "danceFloor",playerPointer);

            //lvl01DanceFloor->actors.push_back(std::make_shared<Actor>());
            // lvl01Floor
            lvl01Floor = std::make_shared<LevelScene>(currentLevel, "hallway",playerPointer);

            // lvl01WcWoman
            lvl01WcWoman = std::make_shared<LevelScene>(currentLevel, "wcWoman",playerPointer);
            //lvl01Wardrobe->items.push_back(std::make_shared<Note>(4,Vector2{340.0,340.0}));

            // lvl01WcMan
            lvl01WcMan = std::make_shared<LevelScene>(currentLevel, "wcMan",playerPointer);
            break;

        case Rooftop:
            // lvlvRooftop
            lvlRoofTop = std::make_shared<LevelScene>(currentLevel, "roofTop",playerPointer);
            break;

        default:
            TraceLog(LOG_INFO, "Main: Load level rooms, current level index out of range");
    }*/


    // Scene management
    std::shared_ptr<Scenes> activeScene = std::make_shared<TitleScreen>();
    std::shared_ptr<LevelScene> activeLevel = tutorialLevelScene;

    // ALL OF THIS IS FOR TEST PURPOSES

    std::shared_ptr<Enemy> enemyPtr;
    std::shared_ptr<Barkeeper> barkeeperPtr;

    playerPointer->money = playerPointer->money + 2000;



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

                    case MAINCONTROLS:
                    {
                        activeScene = std::make_shared<MainControls>();
                        break;
                    }

                    case CREDITS:
                    {
                        activeScene = std::make_shared<CreditScene>();
                        break;
                    }

                    case GAME:
                    {
                        if (activeScene->battleWon == true)
                        {
                            playVictoryAnim = true;
                            playerPointer->interactionForced(playerPointer->enemyToFight);
                        }
                        activeScene = activeLevel;
                        break;
                    }

                    case BATTLE:
                        // Extract playerPointer and enemy from active level
                        // Then make a new shared pointer with the extracted actors

                        // Hardcoded for now
                        enemyPtr = playerPointer->enemyToFight;
                        activeScene = std::make_shared<BattleScene>(playerPointer, enemyPtr);
                        break;
                    case SHOP_BARKEEPER:
                        // Extract playerPointer and barkeeper from active level
                        // Then make a new shared pointer with the extracted actors

                        activeScene = std::make_shared<ShopBarkeeper>(playerPointer, playerPointer->barkeeperPtr);
                        break;
                    case SHOP_DEALER:
                        // Extract playerPointer from active level
                        // Then make a new shared pointer with the extracted actor

                        activeScene = std::make_shared<ShopDealer>(playerPointer);
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

                    case PAUSECONTROLS:
                    {
                        activeScene = std::make_shared<PauseControls>();
                        break;
                    }

                    case INVENTORY:
                    {
                        activeScene->switchScene = false;
                        activeScene = std::make_shared<InventoryScene>(playerPointer);
                        break;
                    }

                    case SKILLTREE:
                    {
                        activeScene->switchScene = false;
                        activeScene = std::make_shared<SkillTreeScene>(playerPointer);
                        break;
                    }
                }
            }
        }


        // ===== Scene update ====  =
        if(activeLevel->switchLevelScene)
        {
            TraceLog(LOG_INFO,"##################################### this is it ################");
            activeLevel->switchLevelScene = false;

            if (activeLevel->switchNextLevel)
            {
                activeLevel->switchNextLevel = false;
                Level newLevel = activeLevel->nextLevel;

                switch (newLevel)
                {
                    case Level01:
                        //lvl01Wardrobe
                        lvl01Wardrobe = std::make_shared<LevelScene>(newLevel, "wardrobe", playerPointer);
                        //lvl01Wardrobe->items.push_back(std::make_shared<Note>(1,Vector2{120.0,340.0}));
                        //lvl01Wardrobe->items.push_back(std::make_shared<Note>(2,Vector2{340.0,340.0}));

                        // lvl01VipRoom
                        lvl01VipRoom = std::make_shared<LevelScene>(newLevel, "vipRoom", playerPointer);

                        // lvl01Storage
                        lvl01Storage = std::make_shared<LevelScene>(newLevel, "storageRoom", playerPointer);
                        //lvl01Wardrobe->items.push_back(std::make_shared<Note>(3,Vector2{340.0,340.0}));

                        // lvl01MainRoom
                        lvl01DanceFloor = std::make_shared<LevelScene>(newLevel, "danceFloor", playerPointer);

                        //lvl01DanceFloor->actors.push_back(std::make_shared<Actor>());
                        // lvl01Floor
                        lvl01Floor = std::make_shared<LevelScene>(newLevel, "hallway", playerPointer);

                        // lvl01WcWoman
                        lvl01WcWoman = std::make_shared<LevelScene>(newLevel, "wcWoman", playerPointer);
                        //lvl01Wardrobe->items.push_back(std::make_shared<Note>(4,Vector2{340.0,340.0}));

                        // lvl01WcMan
                        lvl01WcMan = std::make_shared<LevelScene>(newLevel, "wcMan", playerPointer);
                        break;

                    case Level02:
                        // empty
                            lvlRoofTop = std::make_shared<LevelScene>(newLevel, "roofTop", playerPointer);
                        break;

                    case Rooftop:
                        // lvlvRooftop
                        lvlRoofTop = std::make_shared<LevelScene>(newLevel, "roofTop", playerPointer);
                        break;

                    default:
                        TraceLog(LOG_INFO, "Main: Load level rooms, current level index out of range");
                        break;
                }

                if (activeLevel->switchNextRoom)
                {
                    activeLevel->switchNextRoom = false;

                    if(newLevel == Level01)
                    {
                        currentLevel = activeLevel->nextLevel;
                        currentLevelRooms = activeLevel->nextRoom;
                        LevelRooms newLevelRooms = activeLevel->nextRoom;
                        Vector2 newPos = activeLevel->newPlayerPos;
                        switch (newLevelRooms)
                        {
                            case Wardrobe:
                                //activeLevel->switchNextRoom = false;
                                activeLevel = lvl01Wardrobe;
                                break;
                            case VIPRoom:
                                //activeLevel->switchNextRoom = false;
                                activeLevel = lvl01VipRoom;
                                break;
                            case Storage:
                                //activeLevel->switchNextRoom = false;
                                activeLevel = lvl01Storage;
                                break;
                            case Dancefloor:
                                //activeLevel->switchNextRoom = false;

                                activeLevel = lvl01DanceFloor;
                                TraceLog(LOG_INFO,"Neues LEVEL DANCEFLOOR");
                                activeLevel->player->position = newPos;
                                break;
                            case Floor:
                                //activeLevel->switchNextRoom = false;
                                activeLevel = lvl01Floor;
                                break;
                            case WCW:
                                //activeLevel->switchNextRoom = false;
                                activeLevel = lvl01WcWoman;
                                break;
                            case WCM:
                                //activeLevel->switchNextRoom = false;
                                activeLevel = lvl01WcMan;
                                break;
                            default:
                                TraceLog(LOG_INFO,"Main: Switch activeLevel error, next room index out of range");
                        }
                    }else if(newLevel == Level02){
                        //activeLevel->switchNextRoom = false;
                        activeLevel = lvlRoofTop;

                        currentLevel = activeLevel->nextLevel;
                        currentLevelRooms = activeLevel->nextRoom;
                        TraceLog(LOG_INFO,"Main: Switch activeLevel error, Level02 does´t exists");
                    }else if(newLevel == Rooftop){
                        //activeLevel->switchNextRoom = false;
                        activeLevel = lvlRoofTop;

                        currentLevel = activeLevel->nextLevel;
                        currentLevelRooms = activeLevel->nextRoom;
                    }
                    else
                    {
                        TraceLog(LOG_INFO,"Main: Switch activeLevel error, next Level index out of range");
                    }

                }
                activeScene = activeLevel;
            }
        }
        else
        {
            TraceLog(LOG_INFO,"Bool war falsch");
        }


    activeScene->Update();
    // Victory animation update (I hate this...)

        if (playVictoryAnim)
        {
            if (victoryCurrentFrame >= 7 && victoryFramesCounter >= 6)
            {
                playVictoryAnim = false;
            }
            victoryFramesCounter++;
            if (victoryFramesCounter >= 7)
            {
                victoryCurrentFrame++;
                victoryFramesCounter = 0;
                victoryRec.x = victoryTex.width / 8 * victoryCurrentFrame;
            }
        }


        // ========== DRAW ==========
        BeginDrawing();
        ClearBackground(BLACK);

        if (activeScene->drawLevelBackground == true)
        {
            activeLevel->Draw();
        }
        activeScene->Draw();

        // Victory anim draw (I hate this...)
        if (playVictoryAnim)
        {
            DrawTextureRec(victoryTex, victoryRec, {0, 0}, WHITE);
        }

        //Alternative for adjusting screen brightness
        DrawRectangle(0, 0, Game::ScreenWidth, Game::ScreenHeight, ColorAlpha(BLACK, brightness));

        EndDrawing();
    } // Main game loop end

    // De-initialization here
    UnloadFont(font1);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}