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
            // Load Tutorial level png
            tutorialLevelBackgroundIMG = LoadTexture("./assets/maps/TutorialLevel/TutorialLevel.json");
            break;
        case Wardrobe:
           /* ifStreamFile.open("assets/maps/tilset.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File tileset.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelTilesetDescription;
            ifStreamFile.close();*/


            // Load Level room "Wardrobe"
            ifStreamFile.open("./assets/maps/Floor01/Wardrobe.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File Wardrobe.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;
        case Floor:
            // Load Level room "Floor"
            ifStreamFile.open("./assets/maps/Floor01/Floor.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File Floor.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;
        case VIPRoom:;
            // Load Level room "VIP-Room"
            ifStreamFile.open("./assets/maps/Floor01/VIPRoom.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File VIPRoom.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;
        case Storage:
            // Load Level room "StorageRoom"
            ifStreamFile.open("./assets/maps/Floor01/StorageRoom.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File StorageRoom.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;
        case Dancefloor:
            // Load Level room "DanceFloor"
            ifStreamFile.open("./assets/maps/Floor01/DanceFloor.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File DanceFloor.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;
        case WCM:
            // Load Level room "WC Man"
            ifStreamFile.open("./assets/maps/Floor01/WCM.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File WCM.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;
        case WCW:
            // Load Level room "WC Woman"
            ifStreamFile.open("./assets/maps/Floor01/WCW.json");
            if(!ifStreamFile.is_open()){
                TraceLog(LOG_INFO, "JSON-ERROR: File WCW.json is not available");
            }
            assert(ifStreamFile.is_open());
            ifStreamFile >> levelMap;
            ifStreamFile.close();
            break;
        default:
            TraceLog(LOG_INFO, "Levelroom Parameter error");
            break;
    };

    // Push the layer ID in vector
    for (auto const layer : levelTilesetDescription["layers"]) {

        tileAtlas.push_back(layer["id"]);
    };

    // Laod tilst as JSOB
    ifStreamFile.open("assets/maps/tilset.json");
    if(!ifStreamFile.is_open()){
        TraceLog(LOG_INFO, "JSON-ERROR: File tileset.json is not available");
    }
    assert(ifStreamFile.is_open());
    ifStreamFile >> levelTilesetDescription;
    ifStreamFile.close();

    // Level Tileset as PNG "./assets/maps/Tileset_Floor_1.PNG" /   "./assets/maps/tilset1.png"
    tileAtlasTexture = LoadTexture("./assets/maps/tilset1.png");



    // 1. Erstes die Json vom Ttleset laden
    /*std::ifstream levelTilesetJson("assets/maps/Floor_1_in_Tiles.json");
    if (!levelTilesetJson.is_open()){
        TraceLog(LOG_INFO, "JSON-ERROR: File is not available");
    }
    levelTilesetDescription = nlohmann::json::parse(levelTilesetJson);
    levelTilesetJson.close();*/




    // tileset als json "assets/maps/Floor01/floor_1_in_tiles.json"  / "assets/maps/tilset.json"
    /*ifStreamFile.open("assets/maps/tilset.json");
    if(!ifStreamFile.is_open()){
        TraceLog(LOG_INFO, "JSON-ERROR: File tileset.json is not available");
    }
    assert(ifStreamFile.is_open());
    ifStreamFile >> levelTilesetDescription;
    ifStreamFile.close();

    TraceLog(LOG_INFO, "Array durch2");*/




    // Fertiges Level als JSON "./assets/maps/Floor_1.jSON"   / "./assets/maps/msp_als_json.json"
    //std::ifstream levelMapFile("./assets/maps/msp_als_json.json");
    //levelMap = nlohmann::json::parse(levelMapFile);
    //levelMapFile.close();




    /*ifStreamFile.open("./assets/maps/Floor01/Wardrobe.json");
    if(!ifStreamFile.is_open()){
        TraceLog(LOG_INFO, "JSON-ERROR: File Level.json is not available");
    }
    assert(ifStreamFile.is_open());
    ifStreamFile >> levelMap;
    ifStreamFile.close();

    TraceLog(LOG_INFO, "Array durch3");

    // Level Tileset as PNG "./assets/maps/Tileset_Floor_1.PNG" /   "./assets/maps/tilset1.png"
    tileAtlasTexture = LoadTexture("./assets/maps/tilset1.png");*/





    //2. die Json überprüfen ob die Datei geöffnet ist
    // Bei Fehler meldung -> Siehe tipp!!
    /*ifStreamFile.open(levelTilesetDescription);
    if(!ifStreamFile.is_open()){
        TraceLog(LOG_INFO, "JSON-ERROR: File is not available");
    }
    assert(ifStreamFile.is_open());
    ifStreamFile >> levelTilesetDescription;
    ifStreamFile.close();*/





    //TraceLog(LOG_INFO, "Array durch4");
    //Tile IDs in einem Vector<int> speichern
    //for (auto const layer : levelTilesetDescription["layers"]) {
    //
    //    tileAtlas.push_back(layer["id"]);
    //};


    //TraceLog(LOG_INFO, "Array durch5");
    //std::cout << "bis hier her"<< std::endl;


    // Level initialisation


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
    // Draw player after NPCs
    player->Draw();

}


void LevelScene::DrawMap()
{
    if (!tutorailLeveLActive)
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
        TraceLog(LOG_INFO, "ende zeichnen");
    }else if (tutorailLeveLActive)
    {
        Rectangle rectangle = {100,220};
        Vector2 vector2 = {0,0};
        DrawTexture(tutorialLevelBackgroundIMG, 0,0,BLACK);
        TraceLog(LOG_INFO, "Background drawed");
    }

    TraceLog(LOG_INFO, "anfang zeichnen");
    // Tipp:Fehler ausgeben lassen mit "TraceLog(LOG_INFO, "ProtectTiles constructor called")";

    // tilesetDescriptionFile -> json vom Tileset
    // levelMapFile -> json von dem fertigen Level
    // tileAtlasTexture -> ist das Bild von dem Tileset also das Tileset selbst


    // 1. Erstes die Json vom Ttleset laden
   /*std::ifstream tilesetDescriptionFile("assets/maps/Floor_1_in_Tiles.json");
    nlohmann::json tilesetDescription = nlohmann::json::parse(tilesetDescriptionFile);
    tilesetDescriptionFile.close();*/

    //2. die Json überprüfen ob die Datei geöffnet ist
    // Bei Fehler meldung -> Siehe tipp!!


    //3. Überprüfen der Layer
    // zbs Layer == visible

    //4. Tile IDs in einen Vector<int> speichern



    // Nur das Zeichnen hier, das Laden vorher im Konstrucktor
    // Level tielset as JSON
    /*std::ifstream tilesetDescriptionFile("assets/maps/Floor_1_in_Tiles.json");
    nlohmann::json tilesetDescription = nlohmann::json::parse(tilesetDescriptionFile);
    tilesetDescriptionFile.close();*/

    // Level Tileset as PNG
    /*Texture2D tileAtlasTexture = LoadTexture("../assets/maps/Tileset_Floor_1.PNG");*/

    // Levelmap as JSON
    /*std::ifstream levelMapFile("assets/maps/Floor_1_in_Tiles.json");*/

    /*nlohmann::json levelMap = nlohmann::json::parse(levelMapFile);
    levelMapFile.close(); */
    /////////////




}

