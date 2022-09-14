#ifndef RAYLIBSTARTER_LEVELSCENE_H
#define RAYLIBSTARTER_LEVELSCENE_H

#pragma once
#include "Scenes.h"
#include "../Actors/Enemies/Enemy.h"
#include "../Actors/Player.h"
#include "../Actors/enums.h"


#include <nlohmann/json.hpp>
#include <fstream>
#include "vector"


class LevelScene : public Scenes {
    private:
    //bool tutoriallevelActiv = true;
    public:

    LevelRooms levelRooms;

    nlohmann::json levelTilesetDescription;
    nlohmann::json levelMap;
    Texture2D tileAtlasTexture;

    std::ifstream ifStreamFile;

    std::vector<Enemy> listOfNPCs;
    std::vector<int> tileAtlas;

    Texture2D tutorialLevelBackgroundImg;

    // Level attributes
    std::shared_ptr<Player> player;

    std::vector<std::shared_ptr<Actor>> allActors;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Actor>> actors;
    std::vector<std::shared_ptr<Barkeeper>> barkeepers;
    std::vector<std::shared_ptr<Dealer>> dealers;
    std::vector<std::shared_ptr<Item>> items;

    LevelScene(LevelRooms levelRooms);

    LevelScene();


    void DrawMap();

    void Test();


    void CustomUpdate() override;
    void CustomDraw() override;

    protected:
    ;

};


#endif //RAYLIBSTARTER_LEVELSCENE_H
