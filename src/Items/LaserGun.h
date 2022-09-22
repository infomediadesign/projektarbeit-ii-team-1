//
// Created by Munchkin on 04.08.2022.
//

#ifndef RAYLIBSTARTER_LASERGUN_H
#define RAYLIBSTARTER_LASERGUN_H

#include "Item.h"
#include <vector>
#include <memory>

class LaserGun : public Item {

public:
    LaserGun(Vector2 position);

public:
    void Draw();

    void interact(std::vector<std::shared_ptr<Item>> items);
};


#endif //RAYLIBSTARTER_LASERGUN_H
