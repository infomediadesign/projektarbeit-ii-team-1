#include "LevelScene.h"
#include <vector>

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>


LevelScene::LevelScene()
{
    TraceLog(LOG_INFO, "Array durch");
    // 1. Erstes die Json vom Ttleset laden
    /*std::ifstream levelTilesetJson("assets/maps/Floor_1_in_Tiles.json");
    if (!levelTilesetJson.is_open()){
        TraceLog(LOG_INFO, "JSON-ERROR: File is not available");
    }
    levelTilesetDescription = nlohmann::json::parse(levelTilesetJson);
    levelTilesetJson.close();*/

    // tileset als json "assets/maps/Floor_1_in_Tiles.json"  / "assets/maps/tilset.json"
    ifStreamFile.open("assets/maps/tilset.json");
    if(!ifStreamFile.is_open()){
        TraceLog(LOG_INFO, "JSON-ERROR: File tileset.json is not available");
    }
    assert(ifStreamFile.is_open());
    ifStreamFile >> levelTilesetDescription;
    ifStreamFile.close();

    TraceLog(LOG_INFO, "Array durch2");

    // Fertiges Level als JSON "./assets/maps/Floor_1.jSON"   / "./assets/maps/msp_als_json.json"
    //std::ifstream levelMapFile("./assets/maps/msp_als_json.json");
    //levelMap = nlohmann::json::parse(levelMapFile);
    //levelMapFile.close();

    ifStreamFile.open("./assets/maps/msp_als_json.json");
    if(!ifStreamFile.is_open()){
        TraceLog(LOG_INFO, "JSON-ERROR: File Level.json is not available");
    }
    assert(ifStreamFile.is_open());
    ifStreamFile >> levelMap;
    ifStreamFile.close();

    TraceLog(LOG_INFO, "Array durch3");

    // Level Tileset as PNG "./assets/maps/Tileset_Floor_1.PNG" /   "./assets/maps/tilset1.png"
    tileAtlasTexture = LoadTexture("./assets/maps/tilset1.png");

    //2. die Json überprüfen ob die Datei geöffnet ist
    // Bei Fehler meldung -> Siehe tipp!!
    /*ifStreamFile.open(levelTilesetDescription);
    if(!ifStreamFile.is_open()){
        TraceLog(LOG_INFO, "JSON-ERROR: File is not available");
    }
    assert(ifStreamFile.is_open());
    ifStreamFile >> levelTilesetDescription;
    ifStreamFile.close();*/

    TraceLog(LOG_INFO, "Array durch4");
    //Tile IDs in einem Vector<int> speichern
    for (auto const layer : levelTilesetDescription["layers"]) {

        tileAtlas.push_back(layer["id"]);
    };


    TraceLog(LOG_INFO, "Array durch5");
    std::cout << "bis hier her"<< std::endl;
}

void LevelScene::CustomUpdate()
{
// Player Kollision hier überprüfen und dann "CheckActorCollision()" aufrufen
// Alle "Update()" aller Objekte in dem Level hier aufrufen
}

void LevelScene::CustomDraw()
{
// Alle "Draw()" Methoden aller Objekte in dem Level aufrufen
}



void LevelScene::DrawMap()
{
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
    //////////////

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

}

