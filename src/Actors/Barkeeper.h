//
// Created by 22max on 18.08.2022.
//

#pragma once

#include "Actor.h"

class Barkeeper : public Actor {

    // Attributes
public:
    bool firstInteraction;

    int stockBomb;
    int stockFrisbee;

    // Methods
public:
    Barkeeper(int posX, int posY, std::vector<std::string> dialogue_);
};
