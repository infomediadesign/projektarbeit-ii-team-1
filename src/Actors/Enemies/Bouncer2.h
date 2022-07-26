//
// Created by 22max on 26.07.2022.
//

#ifndef RAYLIBSTARTER_BOUNCER2_H
#define RAYLIBSTARTER_BOUNCER2_H

#include "Enemy.h"

class Bouncer2 : public Enemy {

public:

    Bouncer2(int posX, int posY, Level enemyLevel, std::vector<std::string> dialogue);

};


#endif //RAYLIBSTARTER_BOUNCER2_H
