//
// Created by Munchkin on 04.08.2022.
//

#include "Frisbee.h"


Frisbee::Frisbee()
{
    this->type = itemFrisbee;
    this->name = "Frisbee";
    this->texture = LoadTexture("assets/graphics/items/weapons/frisbee.png");
    this->price = 30;
    this->upgraded = false; // Not upgradable
    this->damage = 20;
    this->uses = 1;
    this->showInLevel = false;
}
