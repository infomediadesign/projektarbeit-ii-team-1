//
// Created by Munchkin on 22.07.2022.
//

#include "Button.h"

game::Button::Button(std::string Text, float pos_x, float pos_y, float fontSize, float fontSpacing, Color colorSelected, Color colorNotSelected)
{
this->Text = Text;
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
    UnloadFont(font1);
}

void game::Button::Draw()
{
    Vector2 Positioning;

    Positioning.x = Position.x - MeasureTextEx(font1, Text.c_str(), fontSize, fontSpacing).x / 2;
    Positioning.y = Position.y;

    if (this->blocked == false)
    {
        DrawTextEx(font1, Text.c_str(), Positioning, fontSize, fontSpacing, colorNotSelected);
    }
    else
    {
        DrawTextEx(font1, Text.c_str(),Positioning , fontSize, fontSpacing, ORANGE);
    }

    if (active == true)
    {
        DrawRectangleLines(Positioning.x, Positioning.y,
                           MeasureTextEx(font1, Text.c_str(), fontSize, fontSpacing).x,
                           MeasureTextEx(font1, Text.c_str(), fontSize, fontSpacing).y, colorSelected);
    }
}