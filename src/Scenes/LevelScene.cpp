#include "LevelScene.h"

void LevelScene()
{

}

void update()
{
// Player Kolliosn hier überprüfen und dann "CheckActorCollision()" aufrufen
// Alle "Update()" aller Objekte in dem Level hier aufrufen
}

void Draw()
{
// Alle "Draw()" Mthoden aller Objekte in dem Level aufrufen
}

// JSON tilemap description
//std::ifstream tilesetDescriptionFile("assets/maps/TilesetDescriptionFile.json");
//nlohmann::json tilesetDescription = nlohmann::json::parse(tilesetDescriptionFile);
//tilesetDescriptionFile.close();

std::ifstream levelMapFile("assets/maps/Floor_1_in_Tiles.json");

nlohmann::json levelMap = nlohmann::json::parse(levelMapFile);
levelMapFil::close();

//Texture2D tileAtlasTexture = LoadTexture((tilesetDescription["image"].get<std::string>()).c_str());
//Map
void LevelScene::DrawMap()
{

    Vector2 vec = {0, 0};
    Rectangle rec = {0, 0, levelMap["width"], levelMap["height"]};

    for (auto const &layer : levelMap["layers"]) {
        if (layer["type"] == "layer" && layer["visible"]) {
            for (auto const &tileId : layer["data"]) {
                if (tileId != 0) {
                    rec.x = (float) ((int) tileId - 1 % (int) tilesetDescription["columns"]) *
                            (float) levelMap["width"];
                    rec.y = (float) floor((float) tileId / (float) tilesetDescription["columns"]) *
                            (float) levelMap["width"];

                    DrawTextureRec(tileAtlasTexture, rec, vec, WHITE);
                }

                vec.x += (float) levelMap["width"];
                if (vec.x >= (float) layer["width"] * (float) levelMap["width"]) {
                    vec.x = 0;
                    vec.y += (float) levelMap["height"];
                }
            }
        }
    }
}