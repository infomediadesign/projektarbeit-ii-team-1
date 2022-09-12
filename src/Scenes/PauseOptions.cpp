//
// Created by Munchkin on 05.09.2022.
//

#include "PauseOptions.h"

#include <iostream>

extern float volSfx;

PauseOptions::PauseOptions()
{
    //background texture
    Image mainMenuBackground = LoadImage("assets/graphics/ui/menu/mainMenuBackground.png");
    ImageResize(&mainMenuBackground, GetScreenWidth(), GetScreenHeight());
    this->background = LoadTextureFromImage(mainMenuBackground);
    UnloadImage(mainMenuBackground);

    //MainMenuBox
    Image mainMenuBoxImage = LoadImage("assets/graphics/ui/menu/mainMenuBox.png");
    ImageResize(&mainMenuBoxImage, mainMenuBoxImage.width*2.5, mainMenuBoxImage.height*2.5);
    this->pauseOptionsBox = LoadTextureFromImage(mainMenuBoxImage);
    UnloadImage(mainMenuBoxImage);

    //Text with font
    this->font1 = LoadFont("assets/graphics/ui/Habbo.ttf");

    //Sound
    this->uiBlip = LoadSound("assets/audio/sfx/uiBlip.wav");
    this->uiBlip2 = LoadSound("assets/audio/sfx/uiBlip2.wav");

    Message1 = "Options";

    fontPosition1 = {GetScreenWidth()/2 -
                     MeasureTextEx(font1, Message1.c_str(), (float)100, 1).x/2,
                     GetScreenHeight() - (float)100/2 -750}; //ursprünglich (float)font1.baseSize/2 - 250};

    //Buttons
    this->active_button = 0;

    this->buttonMusic = new game::Button("Music",
                                         GetScreenWidth()/2,
                                         GetScreenHeight()/2 - 100,
                                         50, 1, YELLOW, WHITE);
    this->buttonMusic->active = true;

    this->buttonSFX = new game::Button("SFX",
                                       GetScreenWidth()/2,
                                       GetScreenHeight()/2,
                                       50, 1, YELLOW, WHITE);

    this->buttonBrightness = new game::Button("Brightness",
                                              GetScreenWidth()/2,
                                              GetScreenHeight()/2 + 100,
                                              50, 1, YELLOW, WHITE);

    this->buttonFullscreen = new game::Button("Fullscreen",
                                              GetScreenWidth()/2,
                                              GetScreenHeight()/2 + 200,
                                              50, 1, YELLOW, WHITE);

    this->buttonReturnPauseMenu = new game::Button("Return to Main Menu (Esc)",
                                                  GetScreenWidth()/2,
                                                  GetScreenHeight()/2 + 200,
                                                  50, 1, YELLOW, WHITE);

    this->buttons.push_back(buttonMusic);
    this->buttons.push_back(buttonSFX);
    this->buttons.push_back(buttonBrightness);
    this->buttons.push_back(buttonFullscreen);
    this->buttons.push_back(buttonReturnPauseMenu);

    this->switchScene = false;
}

PauseOptions::~PauseOptions() {
    delete buttonMusic;
    delete buttonSFX;
    delete buttonBrightness;
    delete buttonFullscreen;
    delete buttonReturnPauseMenu;
}

void PauseOptions::CustomUpdate() {
    if (IsKeyPressed(KEY_DOWN))
    {
        buttons[active_button]->active = false;
        if (active_button < buttons.size() - 1)
            active_button++;
        else active_button = 0;

        buttons[active_button]->active = true;
        PlaySound(this->uiBlip);
    }

    if (IsKeyPressed(KEY_UP))
    {
        buttons[active_button]->active = false;
        if (active_button == 0)
            active_button = (int)buttons.size() - 1;
        else active_button--;

        buttons[active_button]->active = true;
        PlaySound(this->uiBlip);
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        if (this->buttonReturnPauseMenu->active == true)
        {
            PlaySound(this->uiBlip2);
            this->switchTo = MAINMENU;
        }
        this->switchScene = true;
        std::cout << "Button Nr. " << active_button << " was pushed..." << std::endl;
    }
}

void PauseOptions::CustomDraw() {

    //Textures
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(pauseOptionsBox, (GetScreenWidth() - pauseOptionsBox.width)/2, (GetScreenHeight() - pauseOptionsBox.height)/2, WHITE);

    //Messages
    DrawTextEx(font1, Message1.c_str(),fontPosition1, 100, 1,WHITE);

    //Buttons
    for (auto& button : buttons)
    {
        button->Draw();
    }
}

void PauseOptions::Unload() {
    UnloadFont(font1);
    UnloadSound(uiBlip);
    UnloadSound(uiBlip2);
    UnloadTexture(background);
    UnloadTexture(pauseOptionsBox);
}