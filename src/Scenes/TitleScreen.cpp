//
// Created by Munchkin on 31.08.2022.
//

#include "TitleScreen.h"
#include <vector>

extern float volSfx;

TitleScreen::TitleScreen()
{
    //Logo Image
    Image titleScreen = LoadImage("assets/graphics/ui/Logo02.png");
    ImageResize(&titleScreen, 500, 500);
    this->logo = LoadTextureFromImage(titleScreen);
    UnloadImage(titleScreen);

    //Text with font
    this->font1 = LoadFont("assets/graphics/ui/Habbo.ttf");

    //Sound
    this->uiBlip = LoadSound("assets/audio/sfx/uiBlip.wav");
    this->uiBlip2 = LoadSound("assets/audio/sfx/uiBlip2.wav");

    Message1 = "Welcome to the Game!";
    Message2 = "Please press Enter to continue.";

    fontPosition1 = {GetScreenWidth()/2 -
                     MeasureTextEx(font1, Message1.c_str(), (float)50, 1).x/2,
                     GetScreenHeight() - (float)100/2 - 300};

    fontPosition2 = {GetScreenWidth()/2 -
                     MeasureTextEx(font1, Message2.c_str(), (float)50, 1).x/2,
                     GetScreenHeight() - (float)100/2 - 250};

    this->switchScene = false;
    this->drawLevelBackground = false;
}

TitleScreen::~TitleScreen()
{

}

void TitleScreen::CustomUpdate()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        TraceLog(LOG_INFO, "Switching to main menu");
        PlaySound(this->uiBlip2);
        this->switchTo = MAINMENU;
        this->switchScene = true;
    }
}

void TitleScreen::CustomDraw()
{
    //Textures
    DrawTexture(logo, (GetScreenWidth() - logo.width)/2, (GetScreenHeight() - logo.height)/4, WHITE);

    //Messages
    DrawTextEx(font1, Message1.c_str(), fontPosition1, 50, 1, WHITE);
    DrawTextEx(font1, Message2.c_str(), fontPosition2, 50, 1, WHITE);
}

void TitleScreen::Unload()
{
    UnloadFont(font1);
    UnloadSound(uiBlip);
    UnloadSound(uiBlip2);
    UnloadTexture(logo);
}