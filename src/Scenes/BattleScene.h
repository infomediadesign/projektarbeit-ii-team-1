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

    bool controlsLocked;
    bool animationPlaying;

    bool playPlayerIdle;
    bool playEnemyIdle;

    Texture2D background;

    Camera2D camera;

    // Animation-related
    int framesCounter;
    int frameSpeed;
    int currentFramePlayer;
    int currentFrameEnemy;
    Rectangle frameRecPlayer;
    Rectangle frameRecEnemy;

    // Timer
    int timerFramesWaited;

    CombatSheet playerAnimation;
    CombatSheet enemyAnimation;

    // Methods
public:
BattleScene(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy);

void Update();
void Draw();

void initializeBattle();

void animateIdle();
void playAnimation();

};
