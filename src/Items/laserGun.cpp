//
// Created by Munchkin on 04.08.2022.
//

#include "LaserGun.h"

LaserGun::LaserGun(Vector2 position) {
    this->levelPosition = position;
    this->type = itemLaserGun;
    this->name = "Laser-Gun";
    this->texture = LoadTexture("assets/graphics/items/weapons/Lasergun.png");
    this->price = 0; // Cannot be bought
    this->upgraded = false;
    this->damage = 20;
    this->uses = 2;
    this->showInLevel = true;

//Collision Box
this->collisionBox.width = this->texture.width;
this->collisionBox.height = this->texture.height;
this->collisionBox.x = this->levelPosition.x;
this->collisionBox.y = this->levelPosition.y;
}

void LaserGun::Draw()
{
    DrawTextureRec(this->texture, this->collisionBox, this->levelPosition, WHITE);
}