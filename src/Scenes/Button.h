//
// Created by Munchkin on 22.07.2022.
//

#include "raylib.h"

#pragma once

namespace game {

    class Button {
    public:
        Texture2D texture_active;
        Texture2D texture_inactive;

        int pos_x;
        int pos_y;

        Button() = delete;
        Button(Texture2D texture_active, Texture2D texture_inactive, int pos_x, int pos_y, bool active);

        ~Button();

        bool active;
        Texture2D getTexture();
    };

} // game