//
// Created by Munchkin on 15.09.2022.
//

#ifndef RAYLIBSTARTER_MAINCONTROLS_H
#define RAYLIBSTARTER_MAINCONTROLS_H

#pragma once
#include "raylib.h"
#include "../Actors/enums.h"
#include "MenuScenes.h"

#include "Button.h"
#include <vector>



class MainControls : public MenuScenes {
    //Attributes
public:

    Texture2D background;
    Texture2D controlBox;
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

    MainControls();
    ~MainControls();

    void CustomUpdate() override;
    void CustomDraw() override;
    void Unload();
};


#endif //RAYLIBSTARTER_MAINCONTROLS_H
