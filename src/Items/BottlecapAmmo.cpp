//
// Created by 22max on 15.08.2022.
//

#include "BottlecapAmmo.h"

BottlecapAmmo::BottlecapAmmo(Vector2 position)
{
    this->levelPosition = position;
    this->type = itemBottlecapAmmo;
    this->name = "Bottle Cap";
    this->texture = LoadTexture("assets/graphics/items/weapons/BottlecapAmmo.png");
    this->price = 0;
    this->upgraded = false; // Not upgradable
    this->damage = 0;
    this->uses = 0;
    this->showInLevel = true;

    //Collision Box
    this->collisionBox.width = this->texture.width;
    this->collisionBox.height = this->texture.height;
    this->collisionBox.x = this->levelPosition.x;
    this->collisionBox.y = this->levelPosition.y;
}

void BottlecapAmmo::Draw()
{
    DrawTextureRec(this->texture, this->collisionBox, this->levelPosition, WHITE);
}
