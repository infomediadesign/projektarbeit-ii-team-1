//
// Created by 22max on 26.07.2022.
//

#include "Bouncer1.h"
#include <iostream>

#define COLLISION_OFFSET 0.4

Bouncer1::Bouncer1(int posX, int posY, Level enemyLevel, std::vector<std::string> dialogue)
{
    this->enemyLevel = enemyLevel;

    this->position.x = posX;
    this->position.y = posY;


    // Load textures

    this->spritesheet = LoadTexture("assets/graphics/character/npcIdle/bouncer1/bouncer1.png");

    this->spritesheetAttackPunch.sheet = LoadTexture("assets/graphics/combatAnimations/attack/bouncer1/punch.png");
    this->spritesheetAttackPunch.spriteCount = 7;
    this->spritesheetAttackPunch.delay = 0;
    this->spritesheetAttackNecklace.sheet = LoadTexture("assets/graphics/combatAnimations/attack/bouncer1/necklace.png");
    this->spritesheetAttackNecklace.spriteCount = 7;
    this->spritesheetAttackNecklace.delay = 0;
    this->spritesheetAttackTazer.sheet = LoadTexture("assets/graphics/combatAnimations/attack/bouncer1/tazer.png");
    this->spritesheetAttackTazer.spriteCount = 7;
    this->spritesheetAttackTazer.delay = 2;
    this->spritesheetReactPunch.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/bouncer1/punch.png");
    this->spritesheetReactPunch.spriteCount = 6;
    this->spritesheetReactBottlecap.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/bouncer1/bottlecap.png");
    this->spritesheetReactBottlecap.spriteCount = 11;
    this->spritesheetReactLaser.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/bouncer1/laser.png");
    this->spritesheetReactLaser.spriteCount = 4;
    this->spritesheetReactBomb.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/bouncer1/bomb.png");
    this->spritesheetReactBomb.spriteCount = 10;
    this->spritesheetReactFrisbee.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/bouncer1/frisbee.png");
    this->spritesheetReactFrisbee.spriteCount = 5;


    this->frameRec.width = this->spritesheet.width / 4;
    this->frameRec.height = this->spritesheet.height / 4;

    this->collisionBox.x = posX + frameRec.width * (COLLISION_OFFSET / 2);
    this->collisionBox.y = posY;
    this->collisionBox.height = frameRec.height;
    this->collisionBox.width = frameRec.width - frameRec.width * COLLISION_OFFSET;

    this->name = "Bouncer";
    this->dialogue = dialogue;

    this->aggroRadius = 30;

    switch (enemyLevel)
    {
        case Tutorial:
            this->maxHP = 50;
            this->damagePunch = 6;
            this->money = 150;
            break;
        case Level01:
            this->maxHP = 150;
            this->damagePunch = 8;
            this->damageNecklace = 14;
            this->damageTazer = 22;
            this->money = 150;
            break;
        default:
            std::cout << "Error with enemy level: Used stats for Level01" << std::endl;
            this->maxHP = 150;
            this->damagePunch = 8;
            this->damageNecklace = 14;
            this->damageTazer = 22;
            this->money = 150;
    }
    this->currentHP = this->maxHP;


}
