//
// Created by 22max on 20.08.2022.
//

#pragma once
#include "Actor.h"

class Dealer : public Actor{
    // Attributes
public:
    bool firstInteraction;

    // Methods
public:
    Dealer(int posX, int posY, std::vector<std::string> dialogue_);
};
