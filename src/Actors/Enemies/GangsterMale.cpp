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


    // Load textures

    this->spritesheet = LoadTexture("assets/graphics/character/npcIdle/gangsterMale/gangsterMale.png");

    this->spritesheetAttackPunch = LoadTexture("assets/graphics/combatAnimations/attack/gangsterMale/punch.png");
    this->spritesheetAttackNecklace = LoadTexture("assets/graphics/combatAnimations/attack/gangsterMale/necklace.png");
    this->spritesheetAttackTazer = LoadTexture("assets/graphics/combatAnimations/attack/gangsterMale/tazer.png");
    this->spritesheetReactPunch = LoadTexture("assets/graphics/combatAnimations/reaction/gangsterMale/punch.png");
    this->spritesheetReactBottlecap = LoadTexture("assets/graphics/combatAnimations/reaction/gangsterMale/bottlecap.png");
    this->spritesheetReactLaser = LoadTexture("assets/graphics/combatAnimations/reaction/gangsterMale/laser.png");
    this->spritesheetReactBomb = LoadTexture("assets/graphics/combatAnimations/reaction/gangsterMale/bomb.png");
    this->spritesheetReactFrisbee = LoadTexture("assets/graphics/combatAnimations/reaction/gangsterMale/frisbee.png");


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
