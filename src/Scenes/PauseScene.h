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
    Font font1;

    std::string Message1;
    Vector2 fontPosition1;

public:
    game::Button* buttonReturnGame;
    game::Button* buttonPauseOptions;
    game::Button* buttonReturnMainMenu;

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
