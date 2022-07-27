//
// Created by Munchkin on 24.05.2022.
//

#pragma once

#include "MenuScenes.h"
#include "../Actors/Player.h"
#include "../Actors/Enemies/Enemy.h"

#include <memory>


class BattleScene : MenuScenes {

    // Attributes
public:
    std::shared_ptr<Player> player;
    std::shared_ptr<Enemy> enemy;

    Texture2D background;

    Camera2D camera;

    //Animation-related
    int framesCounter;

    // Methods
public:
BattleScene(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy);

void Update();
void Draw();

void initializeBattle();

void animateIdle();

};
