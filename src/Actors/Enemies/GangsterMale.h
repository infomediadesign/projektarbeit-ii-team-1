//
// Created by 22max on 26.07.2022.
//

#pragma once

#include "Enemy.h"

class GangsterMale : public Enemy {
public:
    GangsterMale(int posX, int posY, Level enemyLevel, std::vector<std::string> dialogue);

};

