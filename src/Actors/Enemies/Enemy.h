//
// Created by Maximilian R�ck on 05.06.2022.
//

#pragma once

#include "../Actor.h"
#include "../enums.h"
#include "CombatStructs.h"


class Enemy : public Actor {

    // Attributes
public:
    float maxHP;
    float currentHP;

    Level enemyLevel;

    float aggroRadius;
    bool detectedPlayer = false;

    float damagePunch;
    float damageNecklace;
    float damageTazer;

    Texture2D spritesheetIdle;

    CombatSheet spritesheetAttackPunch;
    CombatSheet spritesheetAttackNecklace;
    CombatSheet spritesheetAttackTazer;

    CombatSheet spritesheetReactPunch;
    CombatSheet spritesheetReactBottlecap;
    CombatSheet spritesheetReactLaser;
    CombatSheet spritesheetReactFrisbee;
    CombatSheet spritesheetReactBomb;


	//Methods
public:
    void Update();
    void Draw();

};
