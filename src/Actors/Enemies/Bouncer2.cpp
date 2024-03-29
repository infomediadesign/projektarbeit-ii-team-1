//
// Created by 22max on 26.07.2022.
//

#include "Bouncer2.h"

#include <iostream>

#define COLLISION_OFFSET 0.4

Bouncer2::Bouncer2(int posX, int posY, Level enemyLevel, std::vector<std::string> dialogue)
{
    this->name  = "Bouncer";

    this->enemyLevel = enemyLevel;

    this->position.x = posX;
    this->position.y = posY;


    // Load textures

    this->spritesheet = LoadTexture("assets/graphics/character/npcIdle/bouncer2/bouncer2.png");

    this->spritesheetAttackPunch.sheet = LoadTexture("assets/graphics/combatAnimations/attack/bouncer2/punch.png");
    this->spritesheetAttackPunch.spriteCount = 7;
    this->spritesheetAttackNecklace.sheet = LoadTexture("assets/graphics/combatAnimations/attack/bouncer2/necklace.png");
    this->spritesheetAttackNecklace.spriteCount = 7;
    this->spritesheetAttackTazer.sheet = LoadTexture("assets/graphics/combatAnimations/attack/bouncer2/tazer.png");
    this->spritesheetAttackTazer.spriteCount = 7;
    this->spritesheetReactPunch.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/bouncer2/punch.png");
    this->spritesheetReactPunch.spriteCount = 6;
    this->spritesheetReactBottlecap.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/bouncer2/bottlecap.png");
    this->spritesheetReactBottlecap.spriteCount = 11;
    this->spritesheetReactLaser.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/bouncer2/laser.png");
    this->spritesheetReactLaser.spriteCount = 4;
    this->spritesheetReactBomb.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/bouncer2/bomb.png");
    this->spritesheetReactBomb.spriteCount = 10;
    this->spritesheetReactFrisbee.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/bouncer2/frisbee.png");
    this->spritesheetReactFrisbee.spriteCount = 5;


    this->frameRec.width = this->spritesheet.width / 4;
    this->frameRec.height = this->spritesheet.height / 4;

    this->collisionBox.x = posX + frameRec.width * (COLLISION_OFFSET / 2);
    this->collisionBox.y = posY;
    this->collisionBox.height = frameRec.height;
    this->collisionBox.width = frameRec.width - frameRec.width * COLLISION_OFFSET;

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
