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

class PauseScene : MenuScenes
        {
        //Attributes
        public:

    Texture2D pauseMenuBox;
    Font font1;

    std::string Message;
    Vector2 fontPosition;

public:
    game::Button* buttonReturnGame;
    game::Button* buttonPauseOptions;
    game::Button* buttonReturnMainMenu;

    int active_button;

    std::vector<game::Button*> buttons;

    bool switchScene; // temporary

    // Methods
public:

    PauseScene();
    ~PauseScene();

    void Update();
    void Draw();
        };


#endif //RAYLIBSTARTER_PAUSESCENE_H
