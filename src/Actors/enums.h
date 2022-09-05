//
// Created by Maximilian R�ck on 05.06.2022.
//

// This file shouldn't be in the Actors-Folder
// However, I've failed to find a way to include this file if it isn't

#pragma once

enum GameScreen
{
    TITLESCREEN,
    MAINMENU,
    MAINOPTIONS,
    CREDITS,
    GAME,
    BATTLE,
    PAUSEMENU,
    PAUSEOPTIONS,
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
enum Level{Tutorial, Level01, Rooftop, VIP};

enum LevelRooms{TutorialLevel, Wardrobe, Floor, VIPRoom, Storage, Dancefloor, WCM, WCW};

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