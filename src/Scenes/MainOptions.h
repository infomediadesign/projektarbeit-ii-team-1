//
// Created by Munchkin on 01.09.2022.
//

#pragma once

#ifndef RAYLIBSTARTER_MAINOPTIONS_H
#define RAYLIBSTARTER_MAINOPTIONS_H

#include "MenuScenes.h"
#include "raylib.h"
#include "../Actors/enums.h"

#include "Button.h"
#include <vector>

//STILL NEEDS TO BE WORKED OVER
class MainOptions : public MenuScenes {
    // Attributes
public:
    Texture2D background;
    Texture2D mainOptionsBox;
    Texture2D optionBar1;
    Texture2D optionBar100;
    Texture2D optionButton;
    Font font1;

    std::string Message1;
    Vector2 fontPosition1;

public:
    game::Button* buttonMusic;
    game::Button* buttonSFX;
    game::Button* buttonBrightness;
    game::Button* buttonFullscreen;
    game::Button* buttonOn;
    game::Button* buttonOff;
    game::Button* buttonReturnMainMenu;

    int active_button;

    std::vector<game::Button*> buttons;

    // Methods
public:

    MainOptions();
    ~MainOptions();

    void CustomUpdate() override;
    void CustomDraw() override;
    void Unload();
};


#endif //RAYLIBSTARTER_MAINOPTIONS_H
