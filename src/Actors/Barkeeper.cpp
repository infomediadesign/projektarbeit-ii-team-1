//
// Created by 22max on 18.08.2022.
//

#include "Barkeeper.h"

#define COLLISION_OFFSET 0.4

Barkeeper::Barkeeper(int posX, int posY, Texture2D spritesheet_, std::vector<std::string> dialogue_)
{
    this->name = "Barkeeper";
    this->position.x = posX;
    this->position.y = posY;

    this->spritesheet = spritesheet_;
    this->frameRec.width = this->spritesheet.width / 4;
    this->frameRec.height = this->spritesheet.height / 4;

    this->collisionBox.x = posX + frameRec.width * (COLLISION_OFFSET / 2);
    this->collisionBox.y = posY;
    this->collisionBox.height = frameRec.height;
    this->collisionBox.width = frameRec.width - frameRec.width * COLLISION_OFFSET;

    this->dialogue = dialogue_;

    this->firstInteraction = true;
}
