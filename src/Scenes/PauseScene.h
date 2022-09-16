//
// Created by Munchkin on 24.05.2022.
//

#pragma once

#ifndef RAYLIBSTARTER_PAUSESCENE_H
#define RAYLIBSTARTER_PAUSESCENE_H

#include "MenuScenes.h"
#include "raylib.h"

#include "Button.h"
#include <vector>

class PauseScene : public MenuScenes
        {
        //Attributes
        public:

    Texture2D pauseMenuBox;
    //Texture2D confirmationBox;
    Font font1;

    //SFX
    Sound uiBlip; //navigate
    Sound uiBlip2; //confirm

    std::string Message1;
    //std::string Message2;
    Vector2 fontPosition1;
   // Vector2 fontPosition2;

public:
    game::Button* buttonReturnGame;
    game::Button* buttonPauseOptions;
    game::Button* buttonControls;
    game::Button* buttonReturnMainMenu;
    /*game::Button* buttonYes;
    game::Button* buttonNo;*/

    int active_button;

    std::vector<game::Button*> buttons;

    // Methods
public:

    PauseScene();
    ~PauseScene();

    void CustomUpdate() override;
    void CustomDraw() override;
    void Unload();
        };


#endif //RAYLIBSTARTER_PAUSESCENE_H
