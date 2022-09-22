//
// Created by Munchkin on 04.08.2022.
//

#include "BottlecapGun.h"

BottlecapGun::BottlecapGun(Vector2 position)
{
    this->levelPosition = position;
    this->type = itemBottlecapGun;
    this->name = "Bottle cap-Gun";
    this->texture = LoadTexture("assets/graphics/items/weapons/bottlecapGun.png");
    this->price = 0; // Cannot be bought
    this->upgraded = false;
    this->damage = 16;
    this->uses = 0; // Depends on player ammo
    this->showInLevel = true;

//Collision Box
this->collisionBox.width = this->texture.width;
this->collisionBox.height = this->texture.height;
this->collisionBox.x = this->levelPosition.x;
this->collisionBox.y = this->levelPosition.y;
}

void BottlecapGun::Draw()
{
    DrawTextureRec(this->texture, this->collisionBox, this->levelPosition, WHITE);
}