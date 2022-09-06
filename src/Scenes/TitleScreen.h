//
// Created by Munchkin on 31.08.2022.
//

#pragma once
#include "raylib.h"
#include "Scenes.h"
#include "MenuScenes.h"

#include <vector>
#include <string>

#ifndef RAYLIBSTARTER_TITLESCREEN_H
#define RAYLIBSTARTER_TITLESCREEN_H


class TitleScreen : public Scenes
        {
    //Attributes
        public:

            Texture2D logo;
            Font font1;

    //SFX
    Sound uiBlip; //navigate
    Sound uiBlip2; //confirm

            std::string Message1;
            std::string Message2;
            Vector2 fontPosition1;
            Vector2 fontPosition2;

        public:

// Methods
        public:
            TitleScreen();
            ~TitleScreen();

            void CustomUpdate() override;
            void CustomDraw() override;
            void Unload();
};


#endif //RAYLIBSTARTER_TITLESCREEN_H
