//
// Created by Maximilian Röck on 05.06.2022.
//

#pragma once

#include "raylib.h"
#include <string>
#include <vector>

class Prop {

    // Attributes
public:

    Vector2 position;

    Texture2D activeTexture;

    //For test purposes
    std::vector<std::string> dialogue;

    Rectangle collisionBox;

private:

    std::string name;

    bool isActive = true;

    // dialogue?

    // Methods
public:

    void Update();

    std::string getName();

    void setName(std::string name_); //For test purposes only

    // onInteraction()?

};
