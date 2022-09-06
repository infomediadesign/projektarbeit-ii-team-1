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
    Texture2D background;
    Texture2D pauseOptionsBox;
    Font font1;

    //SFX
    Sound uiBlip; //navigate
    Sound uiBlip2; //confirm

    std::string Message1;
    Vector2 fontPosition1;

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
