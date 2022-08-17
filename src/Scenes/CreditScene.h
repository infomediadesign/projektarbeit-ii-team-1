//
// Created by Munchkin on 17.08.2022.
//
#pragma once
#include "raylib.h"

#include "Button.h"
#include <vector>

#ifndef RAYLIBSTARTER_CREDITSCENE_H
#define RAYLIBSTARTER_CREDITSCENE_H


class CreditScene {
    //Attributes
public:

    Texture2D creditBox;
    Font font1;

    std::string Message1;
    std::string Message2;
    Vector2 fontPosition1;
    Vector2 fontPosition2;

public:
    game::Button* buttonReturnMainMenu;

    int active_button;

    std::vector<game::Button*> buttons;

    bool switchScene; // temporary

    // Methods
public:

    CreditScene();
    ~CreditScene();

    void Update();
    void Draw();
    void Unload();
};


#endif //RAYLIBSTARTER_CREDITSCENE_H
