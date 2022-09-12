//
// Created by 22max on 18.08.2022.
//

#include "Barkeeper.h"

#define COLLISION_OFFSET 0.4

Barkeeper::Barkeeper(int posX, int posY, std::vector<std::string> dialogue_)
{
    this->name = "Barkeeper";
    this->position.x = posX;
    this->position.y = posY;

    this->spritesheet = LoadTexture("assets/graphics/character/npcIdle/npcRobot/barkeeper.png");
    this->frameRec.width = this->spritesheet.width / 4;
    this->frameRec.height = this->spritesheet.height / 4;

    this->collisionBox.x = posX + frameRec.width * (COLLISION_OFFSET / 2);
    this->collisionBox.y = posY;
    this->collisionBox.height = frameRec.height;
    this->collisionBox.width = frameRec.width - frameRec.width * COLLISION_OFFSET;

    this->dialogue = dialogue_;

    this->turn(down);

    this->firstInteraction = true;

    this->stockBomb = 3;
    this->stockFrisbee = 3;
}
