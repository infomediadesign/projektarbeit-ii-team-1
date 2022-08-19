#ifndef RAYLIBSTARTER_LEVELSCENE_H
#define RAYLIBSTARTER_LEVELSCENE_H

#include "Scenes.h"
#include "../Actors/Enemies/Enemy.h"


#include <nlohmann/json.hpp>
#include <fstream>
#include "vector"


class LevelScene : public Scenes {
    private:
    ;
    public:
    nlohmann::json levelTilesetDescription;
    nlohmann::json levelMap;
    Texture2D tileAtlasTexture;

    std::ifstream file_;

    std::vector<Enemy> listOfNPCs;
    std::vector<int> tileAtlas;

    LevelScene();

    void DrawMap();

    void Update();
    void Draw();
    void Test();


    void CustomUpdate() override;
    void CustomDraw() override;

    protected:
    ;

};


#endif //RAYLIBSTARTER_LEVELSCENE_H
