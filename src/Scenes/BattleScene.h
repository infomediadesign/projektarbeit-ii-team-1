//
// Created by Munchkin on 24.05.2022.
//

#pragma once

#include "MenuScenes.h"
#include "../Actors/Player.h"
#include "../Actors/Enemies/Enemy.h"
#include "../Actors/enums.h"
#include "Button.h"

#include <memory>


class BattleScene : public MenuScenes {

    // Attributes
public:
    std::shared_ptr<Player> player;
    std::shared_ptr<Enemy> enemy;

    Vector2 playerPrevPos;
    Direction playerFacing;
    Vector2 enemyPrevPos;

    bool controlsLocked;
    bool animationPlaying;

    bool playPlayerIdle;
    bool playEnemyIdle;

    AttackSource attackSource;
    AttackType attackType;

    Texture2D background;

    Camera2D camera;

    // Animation-related
    int framesCounter;
    int frameSpeed;
    int currentFramePlayer;
    int currentFrameEnemy;
    Rectangle frameRecPlayer;
    Rectangle frameRecEnemy;

    // Animation timer
    int timerFramesWaited;

    CombatSheet playerAnimation;
    CombatSheet enemyAnimation;

    // Core-System related
    AttackType enemyNextAttack;
    bool playerTurn;
    bool attackSelected;
    int enemyStunnedFor;
    bool endBattle;
    bool moneyGranted;

    // Core-System Items
    bool hasPunchGun;
    int punchGunUses;
    float punchGunDmg;
    bool hasLaserGun;
    int laserGunUses;
    float laserGunDmg;
    bool hasBottlecapGun;
    float bottlecapGunDmg;
    int bombUses;
    int frisbeeUses;

    // UI related
    Font font;
    Texture2D playerHpBar;
    Texture2D enemyHpBar;
    BattleState state;
    int activeButton;
    std::vector<std::shared_ptr<game::Button>> buttons;

    // For battle start animation
    int counterBattleStart;
    int battleStartCurrentFrame;
    Texture2D battleStartTex;
    Rectangle battleStartRec;
    bool playBattleStart;

    // For busted animation
    int counterBusted;
    int bustedCurrentFrame;
    Texture2D bustedTex;
    Rectangle bustedRec;
    bool playBusted;
    bool fadeOut;
    float fadeOutValue;

    // SFX & Music
    int soundTimer;
    int soundTimerTarget;

    Music music;

    Sound soundUiBlip;
    Sound soundUiBlip2;
    Sound soundUiBlocked;
    Sound soundTazer;
    Sound soundWhip;
    Sound soundWhipCrack;
    Sound soundBomb;
    Sound soundLaser;
    Sound soundPunch;

    // Methods
public:
BattleScene(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy);
~BattleScene();

void CustomUpdate() override;
void CustomDraw() override;

void animateIdle();
void playAnimation();
void startAnimation();

void playerAttack();
void enemyAttack();

void updateHpBars();

void menuNavigation();
void initMainMenu();

void playSfx();

void stopBattle();
};
