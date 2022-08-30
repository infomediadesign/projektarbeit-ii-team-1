//
// Created by Munchkin on 22.07.2022.
//

#include "raylib.h"

#pragma once
#include <string>

namespace game {

    class Button {
    public:

        std::string Text;

        Vector2 Position;

        Button() = delete;
        Button(std::string Text, float pos_x, float pos_y, float fontSize, float fontSpacing, Color colorSelected, Color colorNotSelected);

        ~Button();

        bool active;
        bool blocked;

        Color colorSelected;
        Color colorNotSelected;

        float fontSize;
        float fontSpacing;

        Font font1;
        bool centerText;

        void Draw();
        void Unload();
    };

}
