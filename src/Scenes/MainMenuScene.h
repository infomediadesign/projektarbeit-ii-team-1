//
// Created by Munchkin on 24.05.2022.
//

#pragma once

#ifndef RAYLIBSTARTER_MAINMENUSCENE_H
#define RAYLIBSTARTER_MAINMENUSCENE_H

#include "MenuScenes.h"
#include "raylib.h"

#include "Button.h"
#include <vector>

    class MainMenuScene : MenuScenes
            {
        // Attributes
    public:
        game::Button* button1;
        game::Button* button2;
        game::Button* button3;

        int active_button;

        std::vector<game::Button*> buttons;

        bool switchScene; // temporary

        // Methods
    public:

        MainMenuScene();
        ~MainMenuScene();

        void Update();
        void Draw();

};

#endif //RAYLIBSTARTER_MAINMENUSCENE_H
