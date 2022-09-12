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

    float collisionOffset;

protected:

    std::string name;

    std::vector<std::string> dialogue;
    std::vector<int> diaSwitches; // This is a crutch for the upgraded dialogue system

    bool isActive = true;

    // dialogue?

    // Methods
public:

    void Update();

    void Draw();

    std::string getName();

    void setName(std::string name_); //For test purposes only

    std::vector<std::string> getDialogue() {return this->dialogue;};
    std::vector<int> getDiaSwitches() {return this->diaSwitches;};
    void setDiaSwitches(std::vector<int> switches) {this->diaSwitches = switches;};

    // onInteraction()?

};
