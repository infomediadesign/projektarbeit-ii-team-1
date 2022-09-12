//
// Created by Munchkin on 04.08.2022.
//

#include "Longdrink.h"

Longdrink::Longdrink()
{
    this->type = itemHeal;
    this->name = "Longdrink";
    this->texture = LoadTexture("assets/graphics/items/heal/longdrink.png"); // No texture yet
    this->price = 30;
    this->upgraded = false; // Not upgradable
    this->damage = 0;
    this->uses = 0; // Depends on how many are in the player's inventory
    this->showInLevel = false;
}
