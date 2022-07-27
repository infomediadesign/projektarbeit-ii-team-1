//
// Created by Maximilian R�ck on 05.06.2022.
//

#pragma once

#include "../Actor.h"
#include "../enums.h"

class Enemy : public Actor {

    // Attributes
public:
    float maxHP;
    float currentHP;

    Level enemyLevel;

    float aggroRadius;

    float damagePunch;
    float damageNecklace;
    float damageTazer;

    Texture2D spritesheetIdle;

    Texture2D spritesheetAttackPunch;
    Texture2D spritesheetAttackNecklace;
    Texture2D spritesheetAttackTazer;

    Texture2D spritesheetReactPunch;
    Texture2D spritesheetReactBottlecap;
    Texture2D spritesheetReactLaser;
    Texture2D spritesheetReactFrisbee;
    Texture2D spritesheetReactBomb;


	//Methods
public:
    void Update();
    void Draw();

	//onInteraction();

};
