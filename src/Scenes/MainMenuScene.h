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
                Texture2D background;
                Texture2D mainMenuBox;
                Font font1;

                std::string Message1;
                Vector2 fontPosition1;

    public:
        game::Button* buttonNewGame;
        game::Button* buttonOptions;
        game::Button* buttonCredits;
        game::Button* buttonExit;

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
