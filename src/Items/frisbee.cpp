//
// Created by Munchkin on 04.08.2022.
//

#include "frisbee.h"


frisbee::frisbee()
{
    this->type = itemFrisbee;
    this->name = "Frisbee";
    this->texture = LoadTexture("assets/graphics/items/frisbee.png");
    this->price = 30;
    this->upgraded = false; // Not upgradable
    this->damage = 20;
    this->uses = 1;
    this->showInLevel = false;
}
