//
// Created by Maximilian R�ck on 05.06.2022.
//

// This file shouldn't be in the Actors-Folder
// However, I've failed to find a way to include this file if it isn't

#pragma once
#include "string"
#include "raylib.h"

enum GameScreen
{
    TITLESCREEN,
    MAINMENU,
    MAINOPTIONS,
    MAINCONTROLS,
    CREDITS,
    GAME,
    BATTLE,
    PAUSEMENU,
    PAUSEOPTIONS,
    PAUSECONTROLS,
    SHOP_BARKEEPER,
    SHOP_DEALER,
    TESTSCENE,
    INVENTORY,
    SKILLTREE
};

enum Direction
{
    up,
    down,
    left,
    right
};

enum GameState{Started, Paused, Stopped};
enum Level{Tutorial, Level01, Level02, Rooftop, VIP};

enum LevelRooms{TutorialLevel, RoofTop, Wardrobe, Floor, VIPRoom, Storage, Dancefloor, WCM, WCW};

enum BattleState
{
    Main,
    Attack,
    Items
};

// Enums for the battle-scene
enum AttackSource
{
    sourcePlayer,
    sourceEnemy
};
enum AttackType
{
    // Player attack types
    punchPlayer,
    punchGun,
    bottlecap,
    laser,
    bomb,
    frisbee,

    heal,

    // Enemy attack types
    punchEnemy,
    necklace,
    tazer
};

enum ItemType
{
    itemPunchGun,
    itemBottlecapGun,
    itemLaserGun,
    itemBomb,
    itemFrisbee,
    itemHeal,
    itemBottlecapAmmo
};

struct BoxCollioder {
    Rectangle rec;
    bool nextLevel = false;
    bool nextRoom = false;
    std::string nextLevelName;
    std::string nextRoomName;
};