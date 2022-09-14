#include "LevelScene.h"
#include <vector>

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>


LevelScene::LevelScene(LevelRooms levelRooms)
{
    // ===== MAP GENERATION =====
    this->levelRooms = levelRooms;

    switch (levelRooms) {
        case TutorialLevel:
            // Load Tutorial Level
            tutorialLevelBackgroundImg = LoadTexture("./assets/maps/TutorialLevel/TutorialLevelBackground.png");
            break;

        case Wardrobe:
            // Load room JSON "Wardrobe"
            ifStreamFile.open("./assets/maps/Floor01/Wardrobe.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File Wardrobe.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;

        case Floor:
            // Load room JSON "Floor"
            ifStreamFile.open("./assets/maps/Floor01/Floor.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File Floor.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;

        case VIPRoom:
            // Load room JSON "VIPRoom"
            ifStreamFile.open("./assets/maps/Floor01/VIPRoom.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File VIPRoom.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;

        case Storage:
            // Load room JSON "StorageRoom"
            ifStreamFile.open("./assets/maps/Floor01/StorageRoom.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File StorageRoom.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;

        case Dancefloor:
            // Load room JSON "DanceFloor"
            ifStreamFile.open("./assets/maps/Floor01/DanceFloor.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File DanceFloor.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;

        case WCM:
            // Load room JSON "WC Man"
            ifStreamFile.open("./assets/maps/Floor01/WCMan.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File WCMan.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;

        case WCW:
            // Load room JSON "WC Woman"
            ifStreamFile.open("./assets/maps/Floor01/WCWoman.json");
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

    // tileset als json "assets/maps/Floor01/floor_1_in_tiles.json"  / "assets/maps/tilset.json"
    ifStreamFile.open("assets/maps/tilset.json");
    if(!ifStreamFile.is_open()){
        TraceLog(LOG_INFO, "JSON-ERROR: File tileset.json is not available");
    }
    assert(ifStreamFile.is_open());
    ifStreamFile >> levelTilesetDescription;
    ifStreamFile.close();

    // Level Tileset as PNG "./assets/maps/Tileset_Floor_1.PNG" /   "./assets/maps/tilset1.png"
    tileAtlasTexture = LoadTexture("./assets/maps/tilset1.png");

    //Tile IDs in einem Vector<int> speichern
    for (auto const layer : levelTilesetDescription["layers"]) {

        tileAtlas.push_back(layer["id"]);
    };
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


    player->checkActorCollision(this->allActors);

    // Check if a fight has to be started
    if (player->startCombat == true && player->dialogueManager.dialoguePlaying == false) {
        TraceLog(LOG_INFO, "Starting combat...");
        player->startCombat = false;
        // Start combat with player and player->enemyToFight
        // Has to remember the player's position in the level before battle!

        this->switchTo = BATTLE;
        this->switchScene = true;
    }

    // Check enemy aggro radius collision
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
    if (!tutorialLevelActiv)
    {
        Vector2 vec = {0, 0};
        Rectangle rec = {0, 0, levelMap["width"], levelMap["height"]};

        for (auto const &layer : levelMap["layers"]) {
            if (layer["visible"]) {
                for (auto const &tileId : layer["data"]) {
                    if (tileId != 0) {
                        rec.x = (float) ((int) tileId - 1 % (int) levelTilesetDescription["columns"]) *
                                (float) levelMap["width"];
                        rec.y = (float) floor((float) tileId / (float) levelTilesetDescription["columns"]) *
                                (float) levelMap["width"];

                        DrawTextureRec(tileAtlasTexture, rec, vec, WHITE);
                    }

                    vec.x += (float) levelMap["width"];
                    if (vec.x >= (float) layer["width"] * (float) levelMap["width"]) {
                        vec.x = 0;
                        vec.y += (float) levelMap["height"];
                    }
                }
                vec = {0, 0};
            }
        }
    }else if (tutorialLevelActiv)
    {
        DrawTexture(tutorialLevelBackgroundImg,0,0,WHITE);

    }else
    {
        TraceLog(LOG_INFO, "LevelScene.DrawMap() error, drawing the map not possible ");
    }

}

