#include "LevelScene.h"
#include <vector>
#include "config.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>

LevelScene::LevelScene() {};

LevelScene::LevelScene(Level currentLevel, std::string currentLevelRoom, std::shared_ptr<Player> player)
{
    this->player = player;
    this->currentLevelRooms = currentLevelRoom;
    this->currentLevel = currentLevel;

    screenWidth = Game::ScreenWidth;
    screenHeight = Game::ScreenHeight;

    // ===== CAMERA =====
    cameraLs.offset = (Vector2){ static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2)};
    cameraLs.target = (Vector2){ player->position.x + player->frameRec.width / 2, player->position.y + player->frameRec.height / 2};
    cameraLs.rotation = 0.0f;
    cameraLs.zoom = 1.0f;
    // ===== CAMERA =====


    std::map<std::string , std::string> currentDataMap;
    switch (currentLevel) {
        case Level01:
            currentDataMap = level01;
            currentExitBoxes = lvl01ExitBoxe;
            currentExitCount = lvl01ExitCount;
            break;
        case Level02:
            currentDataMap = level02;
            currentExitBoxes = lvl02ExitBoxes;
            currentExitCount = lvl02ExitCount;
            break;
        case Rooftop:
            currentDataMap = roofTop;
            currentExitBoxes = roofTopExitBoxes;
            currentExitCount = roofTopExitCount;
            break;
        default:
            TraceLog(LOG_INFO,"LevelScene error: current level index out of rannge");
            break;
    }
    // ===== LOAD CURRENT Tileset Json and PNG =====
    //tilesetJsonPath = currentDataMap.at("tilesetJson");
    //tilesetPngPath = currentDataMap.at("tilesetPng");

    std::cout<<"++++++++++++++PFAD :"+ level01.at("wardrobe")<<std::endl;

    // ===== LOAD CURRENT TIELMAP JSON =====
    ifStreamFile.open(currentDataMap.at(currentLevelRoom.c_str()));
    if(!ifStreamFile.is_open()){
        TraceLog(LOG_INFO, "JSON-ERROR: File Tilemap.json is not available");
    }else if(ifStreamFile.is_open()){
        TraceLog(LOG_INFO, "LevelScene: Tilemap.Json loaded successfully");
    }
    assert(ifStreamFile.is_open());
    ifStreamFile >> levelMap;
    ifStreamFile.close();

    // ===== LOAD TILESET JSON =====
    ifStreamFile.open(currentDataMap.at("tilesetJson"));
    if(!ifStreamFile.is_open()){
        TraceLog(LOG_INFO, "JSON-ERROR: File Tileeset.json is not available");
    }else if(ifStreamFile.is_open()){
        TraceLog(LOG_INFO, "LevelScene: Tileset.Json loaded successfully");
    }
    assert(ifStreamFile.is_open());
    ifStreamFile >> levelTilesetDescription;
    ifStreamFile.close();
    // ===== LOAD TILESET JSON =====

    // ===== LOAD TILESET PNG =====
    tileAtlasTexture = LoadTexture(currentDataMap.at("tilesetPng").c_str());
    // ===== LOAD TILESET PNG =====

    // ===== PUSH TILE IDs IN VECTOR =====
    for (auto const layer : levelMap["tiles"]){
        tileAtlas.push_back(layer["id"]);
    };
    // ===== PUSH TILE IDs IN VECTOR =====

}

LevelScene::LevelScene(LevelRooms levelRooms, Level currentLevel, std::shared_ptr<Player> player)
{
    this->player = player;
    this->currentLevelRooms = levelRooms;
    this->currentLevel = currentLevel;

    screenWidth = Game::ScreenWidth;
    screenHeight = Game::ScreenHeight;

    // ===== Camera =====
    cameraLs = {0,0};
    cameraLs.target = (Vector2){ player->position.x + 1.0f, player->position.y + 1.0f };
    cameraLs.offset = (Vector2){ player->position.x, player->position.y};
    cameraLs.rotation = 0.0;
    cameraLs.zoom = 1.0;

    // ===== MAP GENERATION =====

    switch (levelRooms) {
        case Wardrobe:
            // ===== Load room JSON "Wardrobe" // ./assets/maps/Floor01/Wardrobe.json // ./assets/maps/msp_als_json.json   ./assets/maps/Floor01/test/wardrobeTilemap.json =====
            ifStreamFile.open("./assets/maps/Floor01/wardrobe/wardrobeTilemap2.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File Wardrobe.json is not available");
            }else if(ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "msp_als_json.json");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;

        case Floor:
            // ===== Load room JSON "Hallway" =====
            ifStreamFile.open("./assets/maps/Floor01/hallway/hallway.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File Floor.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;

        case VIPRoom:
            // ===== Load room JSON "VIPRoom" =====
            ifStreamFile.open("./assets/maps/Floor01/vipRoom/viproom.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File VIPRoom.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;

        case Storage:
            // ===== Load room JSON "StorageRoom" =====
            ifStreamFile.open("./assets/maps/Floor01/storageRoom/storageroom.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File StorageRoom.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;

        case Dancefloor:
            // ===== Load room JSON "Mainroom" =====
            ifStreamFile.open("./assets/maps/Floor01/mainRoom/mainhall.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File DanceFloor.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;

        case WCM:
            // ===== Load room JSON "WC Man" =====
            ifStreamFile.open("./assets/maps/Floor01/wcMan/WCman.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File WCMan.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;

        case WCW:
            // ===== Load room JSON "WC Woman" =====
            ifStreamFile.open("./assets/maps/Floor01/wcWoman/WCwoman.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File WCWoman.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;
        case RoofTop:
            // ===== Load room JSON "Rooftop" =====
            ifStreamFile.open("./assets/maps/Rooftop/rooftop.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File rooftop.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;
        default:
            TraceLog(LOG_INFO, "Level room value out of range");
            break;

    }

    // ===== Check current Level index =====
    switch (currentLevel) {
        case Level01:
            tilesetJsonPath = "./assets/maps/Floor01/TilesetFloor01.json";
            tilesetPngPath = "./assets/maps/Floor01/TilesetFloor01.png";
            break;

        case Level02:
            tilesetJsonPath = "./assets/maps/Floor02/....json";
            tilesetPngPath = "./assets/maps/Floor02/....png";
            break;
        case Rooftop:
            tilesetJsonPath = "./assets/maps/Rooftop/TileSet_rooftop.json";
            tilesetPngPath = "./assets/maps/Rooftop/TileSet_rooftop.png";
            break;
        default:
            TraceLog(LOG_INFO, "LevelSceCurrent level index out of range");
            break;
    }


    // ===== Load tileset json =====
    ifStreamFile.open(tilesetJsonPath);
    if(!ifStreamFile.is_open()){
        TraceLog(LOG_INFO, "JSON-ERROR: File Tileeset.json is not available");
    }
    assert(ifStreamFile.is_open());
    ifStreamFile >> levelTilesetDescription;
    ifStreamFile.close();


    // ===== Load tileset png =====
    tileAtlasTexture = LoadTexture(tilesetPngPath.c_str());



    // ===== Tile IDs in einem Vector<int> speichern "layers" =====
    for (auto const layer : levelMap["tiles"]){
        TraceLog(LOG_INFO,"PUSH IN VECTOR*******************************");
        tileAtlas.push_back(layer["id"]);
    };


    TraceLog(LOG_INFO, "LOAD TILESET.JSON SUCCESFULL");


}

void LevelScene::CustomUpdate()
{
    player->Update();
    cameraLs.target = (Vector2){ player->position.x, player->position.y };

    if (IsKeyPressed(KEY_I)) {
        this->switchTo = INVENTORY;
        this->switchScene = true;
    }
    if (IsKeyPressed(KEY_C)) {
        this->switchTo = SKILLTREE;
        this->switchScene = true;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        this->switchTo = PAUSEMENU;
        this->switchScene = true;
    }

    // ===== Check if a shop has to be opened =====
    if (player->openShopBarkeeper == true && player->dialogueManager.dialoguePlaying == false) {
        TraceLog(LOG_INFO, "Opening shop...");
        player->openShopBarkeeper = false;

        // ===== This is hardcoded for now, because the level class isn't ready yet =====
        this->switchTo = SHOP_BARKEEPER;
        this->switchScene = true;
    }
    if (player->openShopDealer == true && player->dialogueManager.dialoguePlaying == false) {
        TraceLog(LOG_INFO, "Opening shop...");
        player->openShopDealer = false;


        // ===== This is hardcoded for now, because the level class isn't ready yet (would be this->switchTo, etc.) =====
        this->switchTo = SHOP_DEALER;
        this->switchScene = true;
    }


    player->checkActorCollision(this->allActors);

    // ===== Check if a fight has to be started =====
    if (player->startCombat == true && player->dialogueManager.dialoguePlaying == false) {
        TraceLog(LOG_INFO, "Starting combat...");
        player->startCombat = false;
        // Start combat with player and player->enemyToFight
        // Has to remember the player's position in the level before battle!

        this->switchTo = BATTLE;
        this->switchScene = true;
    }

    // ===== Check enemy aggro radius collision =====
    bool stopSearch = false;
    for (int i = 0; i < enemies.size() && stopSearch == false &&
                    player->dialogueManager.dialoguePlaying == false; i++) {
        if (CheckCollisionCircleRec({enemies[i]->position.x + enemies[i]->frameRec.width / 2,
                                     enemies[i]->position.y + enemies[i]->frameRec.height / 2},
                                    enemies[i]->aggroRadius, player->collisionBox) &&
            enemies[i]->defeated == false &&
            this->switchScene == false) {
            player->interactionForced(enemies[i]);
            stopSearch = true;
        }
    }

    player->interact(actors);
    player->interact(enemies);
    player->interact(barkeepers);
    player->interact(dealers);
    player->interact(items);


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
}

void LevelScene::CustomDraw()
{
   BeginMode2D(cameraLs);
    this->DrawMap();



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
    for (int i = 0; i < this->items.size(); i++) {
        if (this->items[i]->showInLevel == true)
        {
            // items[i]->Draw();
            DrawTexture(this->items[i]->texture, this->items[i]->levelPosition.x, this->items[i]->levelPosition.y, WHITE);
            //DrawRectangleLines(this->items[i]->levelPosition.x, this->items[i]->levelPosition.y, this->items[i]->collisionBox.width, this->items[i]->collisionBox.height, RED);
        }
    }

    bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2);
    bool CheckCollisionPointRec(Vector2 point, Rectangle rec);
    //  ===== CHECK IF PLAYER IS ON LEVEL EXIT =====
    if (CheckCollisionRecs(player->interactionBox, recLevelExit))
    {
        // Steuerung stoppen
        // switchNextLevel und oder switchNextRoom auf true setzten
        TraceLog(LOG_INFO, "************** PLAYER IN DER BOX *************");
    }

    player->Draw();
    EndMode2D();

    // Stupid but doesn't work any other way...
    player->dialogueManager.drawDialogue();
}



void LevelScene::DrawMap()
{
    // ===== Save the vales from Json file =====
    float tileWidth = levelMap["tilewidth"];
    float tileHeight = levelMap["tileheight"];
    float levelWidth = levelMap["width"];
    float levelHeigth = levelMap["height"];
    int tileColumCount = levelTilesetDescription["columns"];


    Vector2 vec = {200, 0};
    Rectangle rec = {0, 0, tileWidth, tileHeight};


    for (auto const &layer : levelMap["layers"]) {
        if (layer["type"] == "tilelayer" && layer["visible"]) {
            for (auto const &tileId : layer["data"]) {
                if (tileId != 0) {

                    rec.x = (float) ((int) tileId - 1 % tileColumCount) *
                            tileWidth;
                    rec.y = (float) floor((float) tileId / (float) tileColumCount) *
                            tileWidth;
                    DrawTextureRec(tileAtlasTexture, rec, vec, WHITE);
                }
                vec.x += tileWidth;
                if (vec.x >= (float) layer["width"] * tileWidth + 200) {
                    vec.x = 200;
                    vec.y += tileHeight;
                }
            }
            vec = {200, 0};
        }
    }
    // Draw exit boxes
    for (int i = 1; i<= currentExitCount.at(currentLevelRooms); i++) {
        int index =1;
        if(currentExitCount.at(currentLevelRooms) == 1)
        {
            DrawRectangleLines(currentExitBoxes.at(currentLevelRooms).rec.x + 200,
                               currentExitBoxes.at(currentLevelRooms).rec.y,
                               currentExitBoxes.at(currentLevelRooms).rec.width,
                               currentExitBoxes.at(currentLevelRooms).rec.height, RED);
        }else if(currentExitCount.at(currentLevelRooms) > 1){
            if (i == 1)
            {
                /* Temporarily disabled
                DrawRectangleLines(currentExitBoxes.at(currentLevelRooms).rec.x+ 200 ,
                                   currentExitBoxes.at(currentLevelRooms).rec.y,
                                   currentExitBoxes.at(currentLevelRooms).rec.width,
                                   currentExitBoxes.at(currentLevelRooms).rec.height, RED);
                                   */
                std::cout<< currentLevelRooms <<std::endl;

            }else{
                std::string raum = currentLevelRooms + std::to_string(i);
                /* Temporarily disabled
                DrawRectangleLines(currentExitBoxes.at(raum).rec.x+ 200 ,
                                   currentExitBoxes.at(raum).rec.y,
                                   currentExitBoxes.at(raum).rec.width,
                                   currentExitBoxes.at(raum).rec.height, RED);
                                   */
                //std::string room = currentLevelRooms + std::to_string(i);
                std::cout<< raum <<std::endl;
            }


        }
    }
}