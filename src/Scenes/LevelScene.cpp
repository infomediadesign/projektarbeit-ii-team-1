#include "LevelScene.h"
#include <vector>

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>
LevelScene::LevelScene() {}

LevelScene::LevelScene(LevelRooms levelRooms)
{
    // ===== MAP GENERATION =====
    this->levelRooms = levelRooms;
    switch (levelRooms) {
        case Wardrobe:
            // Load room JSON "Wardrobe" // ./assets/maps/Floor01/Wardrobe.json // ./assets/maps/msp_als_json.json   ./assets/maps/Floor01/test/wardrobeTilemap.json
            ifStreamFile.open("./assets/maps/msp_als_json.json");
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
            // Load room JSON "Hallway"
            ifStreamFile.open("./assets/maps/Floor01/hallway.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File Floor.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;

        case VIPRoom:
            // Load room JSON "VIPRoom"
            ifStreamFile.open("./assets/maps/Floor01/viproom.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File VIPRoom.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;

        case Storage:
            // Load room JSON "StorageRoom"
            ifStreamFile.open("./assets/maps/Floor01/storageroom.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File StorageRoom.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;

        case Dancefloor:
            // Load room JSON "Mainroom"
            ifStreamFile.open("./assets/maps/Floor01/mainroom.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File DanceFloor.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;

        case WCM:
            // Load room JSON "WC Man"
            ifStreamFile.open("./assets/maps/Floor01/WCman.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File WCMan.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;

        case WCW:
            // Load room JSON "WC Woman"
            ifStreamFile.open("./assets/maps/Floor01/WCwoman.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File WCWoman.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;

        default:
            TraceLog(LOG_INFO, "Level room value out of range");
            break;

    };


    // 1. Erstes die Json vom Ttleset laden
    /*std::ifstream levelTilesetJson("assets/maps/Floor_1_in_Tiles.json");
    if (!levelTilesetJson.is_open()){
        TraceLog(LOG_INFO, "JSON-ERROR: File is not available");
    }
    levelTilesetDescription = nlohmann::json::parse(levelTilesetJson);
    levelTilesetJson.close();*/



    // Fertiges Level als JSON "./assets/maps/Floor_1.jSON"   / "./assets/maps/msp_als_json.json"
    //std::ifstream levelMapFile("./assets/maps/msp_als_json.json");
    //levelMap = nlohmann::json::parse(levelMapFile);
    //levelMapFile.close();




    //2. die Json überprüfen ob die Datei geöffnet ist
    // Bei Fehler meldung -> Siehe tipp!!
    /*ifStreamFile.open(levelTilesetDescription);
    if(!ifStreamFile.is_open()){
        TraceLog(LOG_INFO, "JSON-ERROR: File is not available");
    }
    assert(ifStreamFile.is_open());
    ifStreamFile >> levelTilesetDescription;
    ifStreamFile.close();*/



    // tileset als json "assets/maps/Floor01/TileSet_Floor_1.json"  / "assets/maps/tilset.json"  assets/maps/Floor01/test/TilesetFloor01.json
    ifStreamFile.open("assets/maps/Floor01/test/TilesetFloor01.json");
    if(!ifStreamFile.is_open()){
        TraceLog(LOG_INFO, "JSON-ERROR: File Tileeset.json is not available");
    }
    assert(ifStreamFile.is_open());
    ifStreamFile >> levelTilesetDescription;
    ifStreamFile.close();

    // Level Tileset as PNG "./assets/maps/Floor01/pngs/TileSet_Floor_1.PNG" /   "./assets/maps/tilset1.png"   .assets/maps/Floor01/test/TilesetFloor01.png
    tileAtlasTexture = LoadTexture("./assets/maps/tilset1.png");


    //Tile IDs in einem Vector<int> speichern "layers"
    for (auto const layer : levelMap["tiles"]){
        TraceLog(LOG_INFO,"PUSH IN VECTOR*******************************");
        tileAtlas.push_back(layer["id"]);
    };

    TraceLog(LOG_INFO, "LOAD TILESET.JSON SUCCESFULL");




}

void LevelScene::CustomUpdate()
{
    player->Update();

    if (IsKeyPressed(KEY_I)) {
        this->switchTo = INVENTORY;
        this->switchScene = true;
    }
    if (IsKeyPressed(KEY_C)) {
        this->switchTo = SKILLTREE;
        this->switchScene = true;
    }
    if (IsKeyPressed(KEY_P)) {
        this->switchTo = PAUSEMENU;
        this->switchScene = true;
    }

    // Check if a shop has to be opened
    if (player->openShopBarkeeper == true && player->dialogueManager.dialoguePlaying == false) {
        TraceLog(LOG_INFO, "Opening shop...");
        player->openShopBarkeeper = false;

        // This is hardcoded for now, because the level class isn't ready yet
        this->switchTo = SHOP_BARKEEPER;
        this->switchScene = true;
    }
    if (player->openShopDealer == true && player->dialogueManager.dialoguePlaying == false) {
        TraceLog(LOG_INFO, "Opening shop...");
        player->openShopDealer = false;


        // This is hardcoded for now, because the level class isn't ready yet (would be this->switchTo, etc.)
        this->switchTo = SHOP_DEALER;
        this->switchScene = true;
    }
    // Check if a fight has to be started
    if (player->startCombat == true && player->dialogueManager.dialoguePlaying == false) {
        TraceLog(LOG_INFO, "Starting combat...");
        player->startCombat = false;
        // Start combat with player and player->enemyToFight
        // Has to remember the player's position in the level before battle!


        // This is hardcoded for now, because the level class isn't ready yet
        this->switchTo = BATTLE;
        this->switchScene = true;
    }

    player->checkActorCollision(this->allActors);

    // Check enemy aggro radius collision (maybe move this into a method of the level-class
    bool stopSearch = false;
    for (int i = 0; i < enemies.size() && stopSearch == false &&
                    player->dialogueManager.dialoguePlaying == false; i++) {
        if (CheckCollisionCircleRec({enemies[i]->position.x + enemies[i]->frameRec.width / 2,
                                     enemies[i]->position.y + enemies[i]->frameRec.height / 2},
                                    enemies[i]->aggroRadius, player->collisionBox) &&
            enemies[i]->defeated == false) {
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
            DrawTexture(this->items[i]->texture, this->items[i]->levelPosition.x, this->items[i]->levelPosition.y, WHITE);
        }
    }

    // Draw player after NPCs
    player->Draw();

}



void LevelScene::DrawMap()
{
    TraceLog(LOG_INFO,"DRAWMAP START*******************************");

    Vector2 vec = {0, 0};
    Rectangle rec = {0, 0, levelMap["tilewidth"], levelMap["tileheight"]};

    int tileWidth = levelMap["tilewidth"];
    int tileHeight = levelMap["tileheight"];
    int tileColumCount = levelTilesetDescription["columns"];

    for (auto const &layer : levelMap["layers"]) {
        if (layer["type"] == "tilelayer" && layer["visible"]) {
            for (auto const &tileId : layer["data"]) {
                if (tileId != 0) {
                    rec.x = (float) ((int) tileId - 1 % (int) levelTilesetDescription["columns"]) *
                            (float) levelMap["tilewidth"];
                    rec.y = (float) floor((float) tileId / (float) levelTilesetDescription["columns"]) *
                            (float) levelMap["tilewidth"];
                    std::cout<<"DRAWING MAP ......................"<<std::endl;
                    DrawTextureRec(tileAtlasTexture, rec, vec, WHITE);
                }

                vec.x += (float) levelMap["tilewidth"];
                if (vec.x >= (float) layer["width"] * (float) levelMap["tilewidth"]) {
                    vec.x = 0;
                    vec.y += (float) levelMap["tileheight"];
                }
            }
            vec = {0, 0};
        }
        TraceLog(LOG_INFO, "DRAW END ******************************");
    }

    /*for (auto const &layer : levelMap["layers"]) {
        if (layer["type"] == "tilelayer" && layer["visible"]) {
            for (auto const &tileId : layer["data"]) {
                if (tileId != 0) {
                    rec.x = (float) ((int) tileId - 1 % (int) tileColumCount) *
                            (float) tileWidth;
                    rec.y = (float) floor((float) tileId / (float) tileColumCount) *
                            (float) tileWidth;

                    DrawTextureRec(tileAtlasTexture, rec, vec, WHITE);
                }

                vec.x += (float) tileWidth;

                if (vec.x >= (float) layer["width"] * (float) tileWidth) {
                    vec.x = 0;
                    vec.y += (float) tileHeight;
                }
            }
        }
    }*/



}

