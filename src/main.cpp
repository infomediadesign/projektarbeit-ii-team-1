#include <cstdlib>

#include "raylib.h"
#include "config.h"

//This is a test
#include "Actors/enums.h"
#include "Actors/Prop.h"
#include "Actors/Enemies/Enemy.h"
#include "Actors/Enemies/GangsterFemale.h"
#include "Actors/Enemies/GangsterMale.h"
#include "Actors/Enemies/Bouncer2.h"
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
#include "Items/BottlecapAmmo.h"

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

    //Implementing scenes
    TitleScreen testTitle;
    MainMenuScene testMain;
    MainOptions testMainOps;
    CreditScene testCredit;
    PauseScene testPause;
    PauseOptions testPauseOps;

    // Enums
    LevelRooms currentLevelRooms = VIPRoom;
    Level currentLevel = Level01;


    // ===== PLAYER INIT =====
    std::shared_ptr<Player> player = std::make_shared<Player>(GetScreenWidth() / 2, GetScreenHeight() / 2, true);


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

    std::shared_ptr<LevelScene> levelPointer;

    // ========== LEVEL INITIALISATION ==========
    // Laod next level
    switch (currentLevel) {
        case Tutorial:
            std::make_shared<TutorialLevelScene>(player);
            break;

        case Level01:
            //lvl01Wardrobe
            std::make_shared<LevelScene>(currentLevel, "wardrobe",player);
            // lvl01VipRoom
            std::make_shared<LevelScene>(currentLevel, "vipRoom",player);
            // lvl01Storage
            std::make_shared<LevelScene>(currentLevel, "storageRoom",player);
            // lvl01MainRoom
            std::make_shared<LevelScene>(currentLevel, "danceFloor",player);
            // lvl01Hallway
            std::make_shared<LevelScene>(currentLevel, "hallway",player);
            // lvl01WcWoman
            std::make_shared<LevelScene>(currentLevel, "wcWoman",player);
            // lvl01WcMan
            std::make_shared<LevelScene>(currentLevel, "wcMan",player);
            break;

        case Rooftop:
            // lvlvRooftop
            std::make_shared<LevelScene>(currentLevel, "roofTop",player);
            break;

        default:
            TraceLog(LOG_INFO, "Main: Load level rooms, current level index out of range");
    }

    //  ----- Tutorial initialisation -----
    // Levelscene
    //std::shared_ptr<LevelScene> currentlevelPointer = std::make_shared<LevelScene>(currentLevelRooms, currentLevel , player);
    std::shared_ptr<LevelScene> currentlevelPointer = std::make_shared<LevelScene>(currentLevel , "danceFloor",player);


    std::shared_ptr<Actor> pActor;
    Texture2D texGreenGirl = LoadTexture("assets/graphics/character/npcIdle/npc2/npc2.png");
    Texture2D texBlondeDude = LoadTexture("assets/graphics/character/npcIdle/npc1/npc1.png");
    Texture2D texPurpleDude = LoadTexture("assets/graphics/character/npcIdle/npc3/npc3.png");
    Texture2D texRedhead = LoadTexture("assets/graphics/character/npcIdle/npc4/npc4.png");
    Texture2D texBlondeGal = LoadTexture("assets/graphics/character/npcIdle/npc5/npc5.png");
    Texture2D texDJ = LoadTexture("assets/graphics/character/npcIdle/npcDj/djParty.png");

    std::vector<std::string> testDialogue =
            {
                    "Get out of here, man. Can't you see I'm\ntrying to have a good time?",
                    "You're interrupting this good time,\nso get lost."
            };
    std::vector<std::string> dealerDialogue =
            {
                    "How does it look? Are you liquid again?\nWhat do you need?"

            };

    std::vector<std::string> barkeeperDialogue =
            {
                    "What can I do for them?\nWould you like something to drink?",
                    "No, thanks. I am looking for information.",
                    "I was told you were the right person to\ncontact.",
                    "Indeed. I am mainly programmed to serve\ndrinks, but I am not prohibited from storing",
                    "conversation information.\nHow can I be of assistance?",
                    "Can you give me more details about the\nrecent accident of one of the",
                    "Endless Dragon Gang transports?",
                    "Of course. The accident is unfortunate.\n",
                    "As I have learned through conversations\nof some gang members, apparently the",
                    "driver of the transport vehicle in question\nlost control of the vehicle.",
                    "According to statements, the van behaved as\nif someone had steered it from ",
                    "a distance and caused the accident with a\nspecific intention.",
                    "Then it wasn't an accident, it was murder!\nThis family was simply murdered but why?",
                    "Why would you murder innocent bystanders in\nthe middle of the street with a van?",
                    "That makes no sense.",
                    "Forgive me, but I am not programmed for\ninference.",
                    "I cannot give you information that I have\nnot stored.",
                    "Would you like any other information?",
                    "Would you like to know why Billy cheated on his\ngirlfriend Clara?",
                    "What? No. Who's gonna do anything with that?\nNever mind.",
                    " You've already helped me, I thank you.",
                    "You're welcome. I'm happy to help. I wish you\nanother pleasant stay here at Colourful Cube."
            };
    std::vector<int> barkeeperDiaSwitches = {1, 3, 5, 7, 12, 15, 19, 21};


    std::vector<std::string> storyDialogue =
            {
                    "What's up? How can I help you?",
                    "Hey, um I'm looking for someone who knows\nsomething about an accident.",
                    "I heard about the accident and that a woman\nand her son lost their lives.",
                    "Do you know maybe who I can ask?",
                    "Why should I tell you anything? That's internal\ngang stuff and none of your business.",
                    "When I just tell everyone who comes in here\nabout how on one of our transports",
                    "the driver suddenly lost control.",
                    "Fucking hell.\nHow did you do that?",
                    "Anyway, now I gotta make you disappear."
            };
    std::vector<int> storyDiaSwitches = {1, 4};

    // NPCs
    pActor = std::make_shared<Actor>(1250, 1200, texBlondeDude, testDialogue);
    pActor->setName("Jack");
    pActor->turn(up);
    currentlevelPointer->actors.push_back(pActor);
    currentlevelPointer->allActors.push_back(pActor);

    pActor = std::make_shared<Actor>(1700, 1500, texPurpleDude, testDialogue);
    pActor->setName("Joseph");
    pActor->turn(down);
    currentlevelPointer->actors.push_back(pActor);
    currentlevelPointer->allActors.push_back(pActor);

    pActor = std::make_shared<Actor>(1875, 1800, texBlondeGal, testDialogue);
    pActor->setName("Jennifer");
    pActor->turn(left);
    currentlevelPointer->actors.push_back(pActor);
    currentlevelPointer->allActors.push_back(pActor);

    pActor = std::make_shared<Actor>(1800, 700, texBlondeGal, testDialogue);
    pActor->setName("Janina");
    pActor->turn(up);
    currentlevelPointer->actors.push_back(pActor);
    currentlevelPointer->allActors.push_back(pActor);

    pActor = std::make_shared<Actor>(1650, 600, texBlondeDude, testDialogue);
    pActor->setName("Johnathan");
    pActor->turn(right);
    currentlevelPointer->actors.push_back(pActor);
    currentlevelPointer->allActors.push_back(pActor);

    pActor = std::make_shared<Actor>(650, 600, texRedhead, testDialogue);
    pActor->setName("Johanna");
    pActor->turn(up);
    currentlevelPointer->actors.push_back(pActor);
    currentlevelPointer->allActors.push_back(pActor);

    pActor = std::make_shared<Actor>(1425, 155, texDJ, testDialogue);
    pActor->setName("DJ");
    pActor->turn(down);
    currentlevelPointer->actors.push_back(pActor);
    currentlevelPointer->allActors.push_back(pActor);


    pActor = std::make_shared<Actor>(1775, 550, texGreenGirl, testDialogue);
    pActor->setName("Jaqui");
    pActor->turn(down);
    std::vector<int> switches = {0, 2, 3};
    pActor->setDiaSwitches(switches);
    currentlevelPointer->actors.push_back(pActor);
    currentlevelPointer->allActors.push_back(pActor);


    std::shared_ptr<Enemy> pEnemy = std::make_shared<GangsterFemale>(1175, 1050, Level01, storyDialogue);
    pEnemy->dialogueDefeated = {"Are you going to tell me who knows\nmore, or do you want more beatings?",
                                "It's OK. I don't know who knows the details,\nbut the bartender is usually well informed.",
                                "There you go. Thank you."};
    pEnemy->diaDefeatedSwitches = {0, 1, 2};
            pEnemy->setDiaSwitches(storyDiaSwitches);
    pEnemy->aggroRadius = 0;
    currentlevelPointer->enemies.push_back(pEnemy);
    currentlevelPointer->allActors.push_back(pEnemy);


    /*
    pEnemy = std::make_shared<GangsterMale>(650, 600, Level01, testDialogue);
    pEnemy->dialogueDefeated = {"I bims, ded", "Fuk dis m8"};
    pEnemy->aggroRadius = 0;
    pEnemy->turn(up);
    currentlevelPointer->enemies.push_back(pEnemy);
    currentlevelPointer->allActors.push_back(pEnemy);
    */

    std::shared_ptr<Barkeeper> pBarkeeper = std::make_shared<Barkeeper>(570, 275, barkeeperDialogue);
    pBarkeeper->setDiaSwitches(barkeeperDiaSwitches);
    currentlevelPointer->barkeepers.push_back(pBarkeeper);
    currentlevelPointer->allActors.push_back(pBarkeeper);

    std::shared_ptr<Dealer> pDealer = std::make_shared<Dealer>(2010, 100, dealerDialogue);
    currentlevelPointer->dealers.push_back(pDealer);
    currentlevelPointer->allActors.push_back(pDealer);
    Vector2 posi = {350, 250};
    currentlevelPointer->items.push_back(std::make_shared<BottlecapGun>(posi));
    posi = {600, 600};
    currentlevelPointer->items.push_back(std::make_shared<BottlecapAmmo>(posi));
    posi = {900, 375};
    currentlevelPointer->items.push_back(std::make_shared<BottlecapAmmo>(posi));
    posi = {900, 260};
    currentlevelPointer->items.push_back(std::make_shared<BottlecapAmmo>(posi));
    posi = {1580, 1935};
    currentlevelPointer->items.push_back(std::make_shared<BottlecapAmmo>(posi));
    posi = {1345, 1690};
    currentlevelPointer->items.push_back(std::make_shared<BottlecapAmmo>(posi));

    posi = {-5000, -5000};
    player->inventory.push_back(std::make_shared<PunchGun>(posi));

    std::shared_ptr<LevelScene> level01;
    std::shared_ptr<LevelScene> levelRooftop;

    // Scene management
    std::shared_ptr<Scenes> activeScene = std::make_shared<TitleScreen>();
    std::shared_ptr<LevelScene> activeLevel = currentlevelPointer;

    // ALL OF THIS IS FOR TEST PURPOSES

    std::shared_ptr<Enemy> enemyPtr;
    std::shared_ptr<Barkeeper> barkeeperPtr;

    // For demo
    player->money = 2000;


    // END OF TEST


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // ========== UPDATE ==========

        // Scene transition
        if (activeScene->switchScene == true) {
            if (activeScene->switchScene) {
                TraceLog(LOG_INFO, "scene switch request");
                activeScene->switchScene = false;

                switch (activeScene->switchTo) {
                    case TITLESCREEN: {
                        activeScene = std::make_shared<TitleScreen>();
                        break;
                    }

                    case MAINMENU: {
                        activeScene = std::make_shared<MainMenuScene>();
                        break;
                    }

                    case MAINOPTIONS: {
                        activeScene = std::make_shared<MainOptions>();
                        break;
                    }

                    case MAINCONTROLS:
                    {
                        activeScene = std::make_shared<MainControls>();
                        break;
                    }

                    case CREDITS: {
                        activeScene = std::make_shared<CreditScene>();
                        break;
                    }

                    case GAME: {
                        if (activeScene->battleWon == true)
                        {
                            playVictoryAnim = true;
                            player->interactionForced(player->enemyToFight);
                        }
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

                    case PAUSEMENU: {
                        activeScene = std::make_shared<PauseScene>();
                        break;
                    }

                    case PAUSEOPTIONS: {
                        activeScene = std::make_shared<PauseOptions>();
                        break;
                    }

                    case PAUSECONTROLS:
                    {
                        activeScene = std::make_shared<PauseControls>();
                        break;
                    }

                    case INVENTORY: {
                        activeScene->switchScene = false;
                        activeScene = std::make_shared<InventoryScene>(player);
                        break;
                    }

                    case SKILLTREE: {
                        activeScene->switchScene = false;
                        activeScene = std::make_shared<SkillTreeScene>(player);
                        break;
                    }
                }
            }
        }

        if (currentlevelPointer->switchNextLevel)
        {
            std::string room = currentlevelPointer->nextLevel;

            /*switch (room) {
                case level01:
                    currentLevel = Level01;
                    currentlevelPointer->switchNextLevel = false;
                    break;
                case "level02":
                    currentLevel =Level02;
                    currentlevelPointer->switchNextLevel = false;
                    break;
                case "rooftip":
                    currentLevel = Rooftop;
                    currentlevelPointer->switchNextLevel = false;
                    break;
                default:
                    TraceLog(LOG_INFO, "Main: switch next level error, index out of range");
                    break;
            }*/
        }






        // ===== Scene update =====
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

        //Alternative for screen brightness
        DrawRectangle(0, 0, Game::ScreenWidth, Game::ScreenHeight, ColorAlpha(BLACK, brightness));

        EndDrawing();
    } // Main game loop end

    // De-initialization here
    UnloadFont(font1);
    testTitle.Unload();
    testMain.Unload();
    //testMainOps.Unload();
    testCredit.Unload();
    testPause.Unload();
    testPauseOps.Unload();

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
