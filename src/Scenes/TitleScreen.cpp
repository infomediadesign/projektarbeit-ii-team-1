//
// Created by Munchkin on 31.08.2022.
//

#include "TitleScreen.h"
#include <vector>

TitleScreen::TitleScreen()
{
    //Logo Image
    Image titleScreen = LoadImage("assets/graphics/ui/Logo02.png");
    ImageResize(&titleScreen, 500, 500);
    Texture2D logo = LoadTextureFromImage(titleScreen);
    UnloadImage(titleScreen);

    //Text with font
    this->font1 = LoadFont("assets/graphics/ui/Habbo.ttf");

    Message1 = "Welcome to the Game!";
    Message2 = "Please press Enter to continue.";

    fontPosition1 = {GetScreenWidth()/2 -
                     MeasureTextEx(font1, Message1.c_str(), (float)100, 1).x/2,
                     GetScreenHeight() - (float)100/2 - 300};

    fontPosition2 = {(GetScreenWidth()/2 + 450) -
                     MeasureTextEx(font1, Message2.c_str(), (float)100, 1).x/2,
                     GetScreenHeight() - (float)100/2 - 250};

    switchScene = false;
}

TitleScreen::~TitleScreen()
{

}

void TitleScreen::CustomUpdate()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        TraceLog(LOG_INFO, "Switching to main menu...");
        this->switchTo = MAINMENU;
        this->switchScene = true;
    }
}

void TitleScreen::CustomDraw()
{
    //Textures
    DrawTexture(logo, (GetScreenWidth() - logo.width)/2, (GetScreenHeight() - logo.height)/4, WHITE); //2 ursprünglich

    //Messages
    DrawTextEx(font1, Message1.c_str(), fontPosition1, 100, 1, WHITE);
    DrawTextEx(font1, Message2.c_str(), fontPosition2, 50, 1, WHITE);
}

void TitleScreen::Unload()
{
    UnloadFont(font1);
    UnloadTexture(logo);
}