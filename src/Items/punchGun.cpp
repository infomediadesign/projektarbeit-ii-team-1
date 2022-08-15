//
// Created by Munchkin on 04.08.2022.
//

#include "punchGun.h"

punchGun::punchGun(Vector2 position)
{
    this->levelPosition = position;
    this->type = itemPunchGun;
    this->name = "Punch-Gun";
    this->texture = LoadTexture("assets/graphics/items/punchGun.png");
    this->price = 0; // Cannot be bought
    this->upgraded = false;
    this->damage = 14;
    this->uses = 6;
    this->showInLevel = true;
}
