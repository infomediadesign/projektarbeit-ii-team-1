#ifndef RAYLIBSTARTER_LEVELSCENE_H
#define RAYLIBSTARTER_LEVELSCENE_H

#pragma once
#include "config.h"
#include "Scenes.h"
#include "../Actors/Enemies/Enemy.h"
#include "../Actors/Player.h"
#include "../Actors/enums.h"


#include <nlohmann/json.hpp>
#include <fstream>
#include "vector"


class LevelScene : public Scenes {
    private:
    ;
    public:
    LevelRooms levelRooms;

    bool tutorailLeveLActive = false;

    nlohmann::json levelTilesetDescription;
    nlohmann::json levelMap;
    Texture2D tileAtlasTexture;
    Texture2D tutorialLevelBackgroundIMG;

    std::ifstream ifStreamFile;

    std::vector<Enemy> listOfNPCs;
    std::vector<int> tileAtlas;


    // Level attributes
    std::shared_ptr<Player> player;

    std::vector<std::shared_ptr<Actor>> allActors;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Actor>> actors;
    std::vector<std::shared_ptr<Barkeeper>> barkeepers;
    std::vector<std::shared_ptr<Dealer>> dealers;

    LevelScene(LevelRooms levelRooms);
    LevelScene(Level currentLevel);

    void DrawMap();

    void Test();


    void CustomUpdate() override;
    void CustomDraw() override;

    protected:
    ;

};


#endif //RAYLIBSTARTER_LEVELSCENE_H
