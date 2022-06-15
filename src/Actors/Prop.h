//
// Created by Maximilian R�ck on 05.06.2022.
//

#pragma once

#include "raylib.h"
#include <string>

class Prop {

	// Attributes
public:

    Vector2 position;

    Texture2D activeTexture;

    int interactionRadius = 100;

    //For test purposes
    std::string dialogue;

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
