//
// Created by Munchkin on 04.08.2022.
//

#ifndef RAYLIBSTARTER_PUNCHGUN_H
#define RAYLIBSTARTER_PUNCHGUN_H

#include "Item.h"
#include <vector>
#include <memory>

class PunchGun : public Item {

public:
    PunchGun(Vector2 position);

public:
    void Draw();

    void interact(std::vector<std::shared_ptr<Item>> items);
};


#endif //RAYLIBSTARTER_PUNCHGUN_H
