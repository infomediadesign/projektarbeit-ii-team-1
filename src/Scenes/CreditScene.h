//
// Created by Munchkin on 17.08.2022.
//
#pragma once
#include "raylib.h"
#include "../Actors/enums.h"
#include "MenuScenes.h"

#include "Button.h"
#include <vector>

#ifndef RAYLIBSTARTER_CREDITSCENE_H
#define RAYLIBSTARTER_CREDITSCENE_H


class CreditScene : public MenuScenes {
    //Attributes
public:

    Texture2D background;
    Texture2D creditBox;
    Font font1;

    //SFX
    Sound uiBlip; //navigate
    Sound uiBlip2; //confirm

    std::string Message1;
    std::string Message2;
    Vector2 fontPosition1;
    Vector2 fontPosition2;

public:
    game::Button* buttonReturnMainMenu;

    int active_button;

    std::vector<game::Button*> buttons;

    // Methods
public:

    CreditScene();
    ~CreditScene();

    void CustomUpdate() override;
    void CustomDraw() override;
    void Unload();
};


#endif //RAYLIBSTARTER_CREDITSCENE_H
