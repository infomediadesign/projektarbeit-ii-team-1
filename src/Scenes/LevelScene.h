#ifndef RAYLIBSTARTER_LEVELSCENE_H
#define RAYLIBSTARTER_LEVELSCENE_H

#pragma once
#include "Scenes.h"
#include "../Actors/Enemies/Enemy.h"
#include "../Actors/Player.h"
#include "../Actors/enums.h"


#include <nlohmann/json.hpp>
#include <fstream>
#include <map>
#include "vector"


class LevelScene : public Scenes {
private:
    //bool tutoriallevelActiv = true;
    std::string tilesetJsonPath;
    std::string tilesetPngPath;


    Camera2D cameraLs;

    int screenWidth;
    int screenHeight;

    Vector2 mousePos;
public:
    std::string currentLevelRooms;
    Level currentLevel;

    Rectangle recLevelExit = {850, 850, 150, 100};

    bool switchNextLevel = false;
    bool switchNextRoom = false;
    bool switchLevelScene = false;
    Level nextLevel;
    LevelRooms nextRoom;
    Vector2 newPlayerPos;


    Rectangle testrec ={200,320,60,160};

    std::map<std::string,BoxCollioder> currentExitBoxes {};
    std::map<std::string, BoxCollioder> tutorialExitBoxes {{"tutorial",    BoxCollioder {Rectangle{1870, 680, 60, 400}, false, false,
                                                                                        Level01, Dancefloor, {650,1050}}}};

    std::map<std::string, BoxCollioder> lvl01ExitBoxes {{"wardrobe",    BoxCollioder {Rectangle{1460, 1120, 60, 200}, false, false,
                                                                                      Level01, Dancefloor, {0,0}, }},
                                                        {"vipRoom",     BoxCollioder{Rectangle {440,140,160, 60}, false, false,
                                                                                 Level01, Floor, {0,0}}},
                                                        {"storageRoom", BoxCollioder{Rectangle {1220,360,60,200}, false, false,
                                                                                     Level01, Dancefloor, {0,0}}},
                                                        {"hallway",     BoxCollioder{Rectangle {1700,160,60,320}, false, false,
                                                                                 Rooftop, RoofTop, {0,0}}},
                                                        {"hallway2",    BoxCollioder{Rectangle {0,160,60,320}, false, false,
                                                                                  Level01, Dancefloor, {0,0}}},
                                                        {"hallway3",    BoxCollioder{Rectangle {820,160,120,60}, false, false,
                                                                                  Level01, WCW, {0,0}}},
                                                        {"hallway4", BoxCollioder{Rectangle {1140,160,120,60}, false, false,
                                                                                  Level01, WCM, {0,0}}},
                                                        {"hallway5", BoxCollioder{Rectangle {320,420,160,60}, false, false,
                                                                                  Level01, VIPRoom, {0,0}}},
                                                        {"danceFloor", BoxCollioder{Rectangle {0,320,60,160}, false, false,
                                                                                    Level01, Storage, {350,350}}},
                                                        {"danceFloor2", BoxCollioder{Rectangle {0,1680,60,160}, false, false,
                                                                                     Level01, Wardrobe, {620,620}}},
                                                        {"danceFloor3", BoxCollioder{Rectangle {1960,800,60,160}, false, false,
                                                                                     Level01, Floor, {0,0}}},
                                                        {"wcWoman", BoxCollioder{Rectangle {640,860,200,60}, false, false,
                                                                                 Level01, Floor, {0,0}}},
                                                        {"wcMan", BoxCollioder{Rectangle {240,940,160,60}, false, false,
                                                                               Level01, Floor, {0,0}}}};
    
    std::map<std::string,BoxCollioder> lvl02ExitBoxes {};
    std::map<std::string,BoxCollioder> roofTopExitBoxes {{"roofTop", BoxCollioder{Rectangle {0, 00, 10,10}, false, false,
                                                                                  Rooftop, Finished, {0,0}}}};
    // ===== level exit box count =====
    std::map<std::string,int> currentExitCount {};
    std::map<std::string,int> lvl01ExitCount {{"wardrobe", 1},
                                              {"vipRoom", 1},
                                              {"storageRoom", 1},
                                              {"hallway", 5},
                                              {"danceFloor", 1},
                                              {"wcWoman", 1},
                                              {"wcMan", 1}};
    std::map<std::string,int> lvl02ExitCount {};
    std::map<std::string,int> roofTopExitCount {{"roofTop", 1}};
    // ===== level exit box count =====
    // ===== tilemap json paths =====
    std::map<std::string, std::string> tutorialLevel {{"",""}};
    std::map<std::string, std::string> level01 {{"tilesetJson","./assets/maps/Floor01/TilesetFloor01.json"},
                                                {"tilesetPng","./assets/maps/Floor01/TilesetFloor01.png"},
                                                {"wardrobe","./assets/maps/Floor01/wardrobe/wardrobeTilemap2.json"},
                                                {"vipRoom", "./assets/maps/Floor01/vipRoom/viproom.json"},
                                                {"storageRoom", "./assets/maps/Floor01/storageRoom/storageroom.json"},
                                                {"hallway","./assets/maps/Floor01/hallway/hallway.json"},
                                                {"danceFloor","./assets/maps/Floor01/mainRoom/mainhall.json"},
                                                {"wcWoman", "./assets/maps/Floor01/wcWoman/WCwoman.json"},
                                                {"wcMan","./assets/maps/Floor01/wcMan/WCman.json"}};
    std::map<std::string, std::string> level02 {};
    std::map<std::string, std::string> roofTop {{"tilesetJson","./assets/maps/Rooftop/TileSet_rooftop.json"},
                                                {"tilesetPng", "./assets/maps/Rooftop/TileSet_rooftop.png"},
                                                {"roofTop", "./assets/maps/Rooftop/rooftop.json"}};
    // ===== tilemap json paths =====

    nlohmann::json levelTilesetDescription;
    nlohmann::json levelMap;
    Texture2D tileAtlasTexture;

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
    std::vector<std::shared_ptr<Item>> items;

    LevelScene(LevelRooms levelRooms, Level currentLevel, std::shared_ptr<Player> player);

    LevelScene(Level currentLevel, std::string currentLevelRoom, std::shared_ptr<Player> player);

    LevelScene();

    void DrawMap();

    void CheckCollision();

    void CustomUpdate() override;
    void CustomDraw() override;

protected:
    ;

};


#endif //RAYLIBSTARTER_LEVELSCENE_H
