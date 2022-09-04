//
// Created by Munchkin on 22.07.2022.
//

#include "Button.h"

game::Button::Button(std::string Text, float pos_x, float pos_y, float fontSize, float fontSpacing, Color colorSelected, Color colorNotSelected)
{
this->Text = Text;
this->centerText = true;
this->Position.x = pos_x;
this->Position.y = pos_y;
this->active = false;

this->fontSize = fontSize;
this->fontSpacing = fontSpacing;
this->colorSelected = colorSelected;
this->colorNotSelected = colorNotSelected;

font1 = LoadFont("assets/graphics/ui/Habbo.ttf");
this->blocked = false;
}

game::Button::~Button()
{

}

void game::Button::Draw() {
    Vector2 Positioning;
    if (this->centerText = true) {
        Positioning.x = Position.x - MeasureTextEx(font1, Text.c_str(), fontSize, fontSpacing).x / 2;
    }
    else
    {
        Positioning.x = Position.x;
    }
    Positioning.y = Position.y;

    if (this->blocked == false)
    {
        DrawTextEx(font1, Text.c_str(), Positioning, fontSize, fontSpacing, colorNotSelected);
    }
    else
    {
        DrawTextEx(font1, Text.c_str(),Positioning , fontSize, fontSpacing, RED);
    }
    if (active == true)
    {
        DrawRectangleLines(Positioning.x, Positioning.y,
                           MeasureTextEx(font1, Text.c_str(), fontSize, fontSpacing).x,
                           MeasureTextEx(font1, Text.c_str(), fontSize, fontSpacing).y, colorSelected);
    }
}

void game::Button::Unload() {
    UnloadFont(font1);
}