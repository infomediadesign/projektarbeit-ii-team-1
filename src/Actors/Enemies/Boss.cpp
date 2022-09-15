//
// Created by 22max on 15.09.2022.
//

#include "Boss.h"

//
// Created by 22max on 15.09.2022.
//

#include "Boss.h"

#define COLLISION_OFFSET 0.4

Boss::Boss(int posX, int posY, std::vector<std::string> dialogue)
{
    this->position.x = posX;
    this->position.y = posY;

    this->aggroRadius = 150;

    // Load textures

    this->spritesheet = LoadTexture("assets/graphics/character/npcIdle/boss/boss.png");

    this->spritesheetAttackPunch.sheet = LoadTexture("assets/graphics/combatAnimations/attack/boss/punch.png");
    this->spritesheetAttackPunch.spriteCount = 4;
    this->spritesheetAttackPunch.delay = 0;
    this->spritesheetAttackNecklace.sheet = LoadTexture("assets/graphics/combatAnimations/attack/boss/necklace.png");
    this->spritesheetAttackNecklace.delay = 0;
    this->spritesheetAttackNecklace.spriteCount = 7;
    this->spritesheetAttackTazer.sheet = LoadTexture("assets/graphics/combatAnimations/attack/boss/tazer.png");
    this->spritesheetAttackTazer.spriteCount = 6;
    this->spritesheetAttackTazer.delay = 1;
    this->spritesheetReactPunch.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/boss/punch.png");
    this->spritesheetReactPunch.spriteCount = 5;
    this->spritesheetReactBottlecap.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/boss/bottlecap.png");
    this->spritesheetReactBottlecap.spriteCount = 7;
    this->spritesheetReactLaser.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/boss/laser.png");
    this->spritesheetReactLaser.spriteCount = 4;
    this->spritesheetReactBomb.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/boss/bomb.png");
    this->spritesheetReactBomb.spriteCount = 9;
    this->spritesheetReactFrisbee.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/boss/frisbee.png");
    this->spritesheetReactFrisbee.spriteCount = 5;


    this->frameRec.width = this->spritesheet.width / 4;
    this->frameRec.height = this->spritesheet.height / 4;

    this->collisionBox.x = posX + frameRec.width * (COLLISION_OFFSET / 2);
    this->collisionBox.y = posY;
    this->collisionBox.height = frameRec.height;
    this->collisionBox.width = frameRec.width - frameRec.width * COLLISION_OFFSET;

    this->dialogue = dialogue;


    this->maxHP = 200;
    this->damagePunch = 28;
    this->damageNecklace = 32;
    this->damageTazer = 44;
    this->money = 0;

    this->currentHP = this->maxHP;
}
