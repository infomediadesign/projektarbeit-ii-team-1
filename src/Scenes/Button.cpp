//
// Created by Munchkin on 22.07.2022.
//

#include "Button.h"

Texture2D game::Button::getTexture() {
    if (active)
        return this->texture_active;

    return this->texture_inactive;
}

game::Button::Button(Texture2D texture_active, Texture2D texture_inactive, int pos_x, int pos_y, bool active)
        : texture_active(texture_active), texture_inactive(texture_inactive), pos_x(pos_x), pos_y(pos_y), active(active)
{

}

game::Button::~Button()
{
    UnloadTexture(this->texture_active);
    UnloadTexture(this->texture_inactive);
}

// game