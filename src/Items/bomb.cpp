//
// Created by Munchkin on 04.08.2022.
//

#include "Bomb.h"

Bomb::Bomb()
{
    this->type = itemBomb;
    this->name = "Discobomb";
    this->texture = LoadTexture("assets/graphics/items/bomb.png");
    this->price = 20;
    this->upgraded = false; // Not upgradable
    this->damage = 0;
    this->uses = 1;
    this->showInLevel = false;
}
