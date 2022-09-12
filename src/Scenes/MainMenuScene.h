//
// Created by Munchkin on 24.05.2022.
//

#pragma once

#ifndef RAYLIBSTARTER_MAINMENUSCENE_H
#define RAYLIBSTARTER_MAINMENUSCENE_H

#include "MenuScenes.h"
#include "raylib.h"
#include "../Actors/enums.h"

#include "Button.h"
#include <vector>

    class MainMenuScene : public MenuScenes
            {
        // Attributes
            public:
                Texture2D background;
                Texture2D mainMenuBox;
                Font font1;

                std::string Message1;
                Vector2 fontPosition1;

                //SFX
                Sound uiBlip; //navigate
                Sound uiBlip2; //confirm

    public:
        game::Button* buttonNewGame;
        game::Button* buttonOptions;
        game::Button* buttonCredits;
        game::Button* buttonExit;

        int active_button;

        std::vector<game::Button*> buttons;

        // Methods
    public:

        MainMenuScene();
        ~MainMenuScene();

        void CustomUpdate() override;
        void CustomDraw() override;
        void Unload();
};

#endif //RAYLIBSTARTER_MAINMENUSCENE_H
