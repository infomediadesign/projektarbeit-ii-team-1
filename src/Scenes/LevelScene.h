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


public:
    std::string currentLevelRooms;
    Level currentLevel;

    Rectangle recLevelExit = {850, 850, 150, 100};
    bool switchNextLevel = false;
    bool switchNextRoom = false;
    std::string nextLevel;
    std::string nextRoom;

    std::map<std::string,BoxCollioder> currentExitBoxes {};
    std::map<std::string, BoxCollioder> lvl01ExitBoxe { {"wardrobe", BoxCollioder {Rectangle{1460, 1120, 60, 200}, false, false, "level01", "danceFloor"}},
                                                        {"vipRoom", BoxCollioder{Rectangle {440,140,160, 60}, false, false, "level01", "hallway"}},
                                                        {"storageRoom", BoxCollioder{Rectangle {1220,360,60,200}, false, false, "level01", "danceFloor"}},
                                                        {"hallway", BoxCollioder{Rectangle {1700,160,60,320}, false, false, "level01", "hallway"}},
                                                        {"hallway2", BoxCollioder{Rectangle {0,160,60,320}, false, false, "level01", "hallway"}},
                                                        {"hallway3", BoxCollioder{Rectangle {820,160,120,60}, false, false, "level01", "hallway"}},
                                                        {"hallway4", BoxCollioder{Rectangle {1140,160,120,60}, false, false, "level01", "hallway"}},
                                                        {"hallway5", BoxCollioder{Rectangle {320,420,160,60}, false, false, "level01", "hallway"}},
                                                        {"danceFloor", BoxCollioder{Rectangle {0,320,60,160}, false, false, "level01", "hallway"}},
                                                        {"danceFloor2", BoxCollioder{Rectangle {0,1680,60,160}, false, false, "level01", "hallway"}},
                                                        {"danceFloor3", BoxCollioder{Rectangle {1960,800,60,160}, false, false, "level01", "hallway"}},
                                                        {"wcWoman", BoxCollioder{Rectangle {640,860,200,60}, false, false, "level01", "hallway"}},
                                                        {"wcMan", BoxCollioder{Rectangle {240,940,160,60}, false, false, "level01", "hallway"}}};
    
    std::map<std::string,BoxCollioder> lvl02ExitBoxes {};
    std::map<std::string,BoxCollioder> roofTopExitBoxes {{"roofTop", BoxCollioder{Rectangle {0, 00, 10,10}, false, false, "level01", "hallway"}}};
    // ===== level exit box count =====
    std::map<std::string,int> currentExitCount {};
    std::map<std::string,int> lvl01ExitCount {{"wardrobe", 1},
                                              {"vipRoom", 1},
                                              {"storageRoom", 1},
                                              {"hallway", 5},
                                              {"danceFloor", 3},
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

    void Test();


    void CustomUpdate() override;
    void CustomDraw() override;

protected:
    ;

};


#endif //RAYLIBSTARTER_LEVELSCENE_H
