//
// Created by 22max on 15.09.2022.
//

#pragma once

#include "Enemy.h"

class Boss : public Enemy{
public:
    Boss(int posX, int posY, std::vector<std::string> dialogue);

};

