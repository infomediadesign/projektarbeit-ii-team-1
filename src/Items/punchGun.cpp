//
// Created by Munchkin on 04.08.2022.
//

#include "PunchGun.h"

#define COLLISION_OFFSET 0.4

PunchGun::PunchGun(Vector2 position)
{
    this->levelPosition = position;
    this->type = itemPunchGun;
    this->name = "Punch-Gun";
    this->texture = LoadTexture("assets/graphics/items/weapons/punchGun.png");
    this->price = 0; // Cannot be bought
    this->upgraded = false;
    this->damage = 14;
    this->uses = 6;
    this->showInLevel = true;


//Collision Box
this->collisionBox.width = this->texture.width;
this->collisionBox.height = this->texture.height;
this->collisionBox.x = this->levelPosition.x;
this->collisionBox.y = this->levelPosition.y;
}

void PunchGun::Draw()
{
    DrawTextureRec(this->texture, this->collisionBox, this->levelPosition, WHITE);
}