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

    Rectangle collisionBox;

protected:

    std::string name;

    std::vector<std::string> dialogue;

    bool isActive = true;

    // dialogue?

    // Methods
public:

    void Update();

    void Draw();

    std::string getName();

    void setName(std::string name_); //For test purposes only

    std::vector<std::string> getDialogue() {return this->dialogue;};

    // onInteraction()?

};
