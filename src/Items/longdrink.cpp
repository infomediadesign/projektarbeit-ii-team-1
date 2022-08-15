//
// Created by Munchkin on 04.08.2022.
//

#include "longdrink.h"

longdrink::longdrink()
{
    this->type = itemHeal;
    this->name = "Longdrink";
    this->texture = LoadTexture("assets/graphics/items/bomb.png"); // No texture yet
    this->price = 30;
    this->upgraded = false; // Not upgradable
    this->damage = 0;
    this->uses = 0; // Depends on how many are in the player's inventory
    this->showInLevel = false;
}
