//
// Created by 22max on 20.08.2022.
//

#include "Dealer.h"

#define COLLISION_OFFSET 0.4

Dealer::Dealer(int posX, int posY, std::vector<std::string> dialogue_)
{
    this->name = "Dealer";
    this->position.x = posX;
    this->position.y = posY;

    this->spritesheet = LoadTexture("assets/graphics/character/npcIdle/npcMerchant/Dealer.png");
    this->frameRec.width = this->spritesheet.width / 4;
    this->frameRec.height = this->spritesheet.height / 4;

    this->collisionBox.x = posX + frameRec.width * (COLLISION_OFFSET / 2);
    this->collisionBox.y = posY;
    this->collisionBox.height = frameRec.height;
    this->collisionBox.width = frameRec.width - frameRec.width * COLLISION_OFFSET;

    this->dialogue = dialogue_;

    this->turn(down);

    this->firstInteraction = true;
}
