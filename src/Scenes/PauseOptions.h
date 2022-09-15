//
// Created by Munchkin on 05.09.2022.
//

#ifndef RAYLIBSTARTER_PAUSEOPTIONS_H
#define RAYLIBSTARTER_PAUSEOPTIONS_H

#pragma once
#include "raylib.h"
#include "Scenes.h"
#include "MenuScenes.h"
#include "Button.h"

#include <vector>
#include <string>

class PauseOptions : public MenuScenes {
    // Attributes
public:
    Texture2D pauseOptionsBox;
    Texture2D optionBar1;
    Texture2D optionBar100;
    Texture2D optionButton;
    Font font1;

    //SFX
    Sound uiBlip; //navigate
    Sound uiBlip2; //confirm
    Sound punchsound;

    std::string Message1;
    std::string Message2;
    std::string Message3;
    std::string Message4;
    Vector2 fontPosition1;
    Vector2 fontPosition2;
    Vector2 fontPosition3;
    Vector2 fontPosition4;
    Vector2 fontPosition5;
    Vector2 fontPosition6;

public:
    game::Button* buttonMusic;
    game::Button* buttonSFX;
    game::Button* buttonBrightness;
    game::Button* buttonFullscreen;
    game::Button* buttonReturnPauseMenu;

    int active_button;

    std::vector<game::Button*> buttons;


    // Methods
public:

    PauseOptions();
    ~PauseOptions();

    void CustomUpdate() override;
    void CustomDraw() override;
    void Unload();
};


#endif //RAYLIBSTARTER_PAUSEOPTIONS_H
