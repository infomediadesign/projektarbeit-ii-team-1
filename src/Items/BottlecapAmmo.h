//
// Created by 22max on 15.08.2022.
//

#ifndef RAYLIBSTARTER_BOTTLECAPAMMO_H
#define RAYLIBSTARTER_BOTTLECAPAMMO_H

#include "Item.h"
#include <vector>
#include <memory>

class BottlecapAmmo : public Item {
public:
    BottlecapAmmo(Vector2 position);

public:
    void Draw();

    void interact(std::vector<std::shared_ptr<Item>> items);
};


#endif //RAYLIBSTARTER_BOTTLECAPAMMO_H
