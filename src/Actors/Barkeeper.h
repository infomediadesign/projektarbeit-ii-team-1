//
// Created by 22max on 18.08.2022.
//

#ifndef RAYLIBSTARTER_BARKEEPER_H
#define RAYLIBSTARTER_BARKEEPER_H

#include "Actor.h"

class Barkeeper : public Actor {

    // Attributes
public:
    bool firstInteraction;


    // Methods
public:
    Barkeeper(int posX, int posY, Texture2D spritesheet_, std::vector<std::string> dialogue_);
};


#endif //RAYLIBSTARTER_BARKEEPER_H
