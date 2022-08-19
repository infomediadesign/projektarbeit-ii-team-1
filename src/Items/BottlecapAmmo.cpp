//
// Created by 22max on 15.08.2022.
//

#include "BottlecapAmmo.h"

BottlecapAmmo::BottlecapAmmo(Vector2 position)
{
    this->levelPosition = position;
    this->type = itemBottlecapAmmo;
    this->name = "Bottle Cap";
    this->texture = LoadTexture("assets/graphics/items/bomb.png"); // No texture yet
    this->price = 0;
    this->upgraded = false; // Not upgradable
    this->damage = 0;
    this->uses = 0;
    this->showInLevel = true;
}
