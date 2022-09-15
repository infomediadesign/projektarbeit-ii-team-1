//
// Created by Munchkin on 04.08.2022.
//

#pragma once

#include "Item.h"
#include <vector>
#include <memory>

class BottlecapGun : public Item {
public:
    BottlecapGun(Vector2 position);

public:
    void Draw();

    void interact(std::vector<std::shared_ptr<Item>> items);
};
