//
// Created by Munchkin on 04.08.2022.
//

#include "LaserGun.h"

LaserGun::LaserGun(Vector2 position) {
    this->levelPosition = position;
    this->type = itemLaserGun;
    this->name = "Laser-Gun";
    this->texture = LoadTexture("assets/graphics/items/lasergun.png");
    this->price = 0; // Cannot be bought
    this->upgraded = false;
    this->damage = 20;
    this->uses = 2;
    this->showInLevel = true;
}
