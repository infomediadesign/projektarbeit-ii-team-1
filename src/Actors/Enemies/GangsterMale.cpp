//
// Created by 22max on 26.07.2022.
//

#include "GangsterMale.h"
#include <iostream>

#define COLLISION_OFFSET 0.4

GangsterMale::GangsterMale(int posX, int posY, Level enemyLevel, std::vector<std::string> dialogue)
{

    this->enemyLevel = enemyLevel;

    this->position.x = posX;
    this->position.y = posY;

    this->aggroRadius = 100;

    // Load textures

    this->spritesheet = LoadTexture("assets/graphics/character/npcIdle/gangsterMale/gangsterMale.png");

    this->spritesheetAttackPunch.sheet = LoadTexture("assets/graphics/combatAnimations/attack/gangsterMale/punch.png");
    this->spritesheetAttackPunch.spriteCount = 4;
    this->spritesheetAttackNecklace.sheet = LoadTexture("assets/graphics/combatAnimations/attack/gangsterMale/necklace.png");
    this->spritesheetAttackNecklace.spriteCount = 7;
    this->spritesheetAttackTazer.sheet = LoadTexture("assets/graphics/combatAnimations/attack/gangsterMale/tazer.png");
    this->spritesheetAttackTazer.spriteCount = 6;
    this->spritesheetReactPunch.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/gangsterMale/punch.png");
    this->spritesheetReactPunch.spriteCount = 5;
    this->spritesheetReactBottlecap.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/gangsterMale/bottlecap.png");
    this->spritesheetReactBottlecap.spriteCount = 11;
    this->spritesheetReactLaser.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/gangsterMale/laser.png");
    this->spritesheetReactLaser.spriteCount = 4;
    this->spritesheetReactBomb.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/gangsterMale/bomb.png");
    this->spritesheetReactBomb.spriteCount = 10;
    this->spritesheetReactFrisbee.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/gangsterMale/frisbee.png");
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
            this->maxHP = 80;
            this->damagePunch = 6;
            this->damageNecklace = 12;
            this->damageTazer = 20;
            this->money = 100;
            break;
        case Rooftop:
            this->maxHP = 100;
            this->damagePunch = 12;
            this->damageNecklace = 20;
            this->damageTazer = 28;
            this->money = 150;
            break;
        case VIP:
            this->maxHP = 100;
            this->damagePunch = 6;
            this->damageNecklace = 12;
            this->damageTazer = 20;
            this->money = 120;
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
