//
// Created by Munchkin on 01.09.2022.
//

#include "MainOptions.h"

#include <iostream>

extern float volSfx;

MainOptions::MainOptions()
{
    //background texture
    Image mainOptionsBackground = LoadImage("assets/graphics/ui/menu/mainMenuBackground.png");
    ImageResize(&mainOptionsBackground, GetScreenWidth(), GetScreenHeight());
    this->background = LoadTextureFromImage(mainOptionsBackground);
    UnloadImage(mainOptionsBackground);

    //MainOptionsBox
    Image mainMenuBoxImage = LoadImage("assets/graphics/ui/menu/mainMenuBox.png");
    ImageResize(&mainMenuBoxImage, mainMenuBoxImage.width*3, mainMenuBoxImage.height*3);
    this->mainOptionsBox = LoadTextureFromImage(mainMenuBoxImage);
    UnloadImage(mainMenuBoxImage);

    //OptionBars
    this->optionBar1 = LoadTexture("assets/graphics/ui/menu/Optionbar/Optionsbalken 1.png");
    this->optionBar100 = LoadTexture("assets/graphics/ui/menu/Optionbar/Optionsbalken100.png");

    //OptionsButton
    this->optionButton = LoadTexture("assets/graphics/ui/menu/Optionbar/Options-Button.png");

    //Text with font
    this->font1 = LoadFont("assets/graphics/ui/Habbo.ttf");

    //Sound
    this->uiBlip = LoadSound("assets/audio/sfx/uiBlip.wav");
    this->uiBlip2 = LoadSound("assets/audio/sfx/uiBlip2.wav");

    Message1 = "Options";
    Message2 = "On";
    Message3 = "Off";

    fontPosition1 = {GetScreenWidth()/2 -
                     MeasureTextEx(font1, Message1.c_str(), (float)100, 1).x/2,
                     GetScreenHeight() - (float)100/2 - 850};

    fontPosition2 = {GetScreenWidth()/2 - 25 -
                     MeasureTextEx(font1, Message2.c_str(), (float)50, 1).x/2,
                     GetScreenHeight() - (float)50/2 - 375};

    fontPosition3 = {GetScreenWidth()/2 + 130 -
                     MeasureTextEx(font1, Message3.c_str(), (float)50, 1).x/2,
                     GetScreenHeight() - (float)50/2 - 375};

    //Buttons
    this->active_button = 0;

    this->buttonMusic = new game::Button("Music",
                                           GetScreenWidth()/2 - 300,
                                           GetScreenHeight()/2 - 200,
                                           50, 1, YELLOW, WHITE);
    this->buttonMusic->active = true;

    this->buttonSFX = new game::Button("SFX",
                                           GetScreenWidth()/2 - 300,
                                           GetScreenHeight()/2 - 100,
                                           50, 1, YELLOW, WHITE);

    this->buttonBrightness = new game::Button("Brightness",
                                           GetScreenWidth()/2 - 300,
                                           GetScreenHeight()/2,
                                           50, 1, YELLOW, WHITE);

    this->buttonFullscreen = new game::Button("Fullscreen",
                                        GetScreenWidth()/2 - 300,
                                        GetScreenHeight()/2 + 100,
                                        50, 1, YELLOW, WHITE);

    this->buttonReturnMainMenu = new game::Button("Return to Main Menu (Esc)",
                                              GetScreenWidth()/2 - 200,
                                              GetScreenHeight()/2 + 250,
                                              50, 1, YELLOW, WHITE);

    this->buttons.push_back(buttonMusic);
    this->buttons.push_back(buttonSFX);
    this->buttons.push_back(buttonBrightness);
    this->buttons.push_back(buttonFullscreen);
    this->buttons.push_back(buttonReturnMainMenu);

    this->switchScene = false;
}

MainOptions::~MainOptions() {
    delete buttonMusic;
    delete buttonSFX;
    delete buttonBrightness;
    delete buttonFullscreen;
    delete buttonReturnMainMenu;
}

void MainOptions::CustomUpdate() {
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
        if (this->buttonFullscreen->active == true)
        {
            PlaySound(this->uiBlip2);
            ToggleFullscreen();
        }
        std::cout << "Button Nr. " << active_button << " was pushed..." << std::endl;
    }

    if(IsKeyPressed(KEY_ESCAPE))
    {
        PlaySound(this->uiBlip2);
        this->switchTo = MAINMENU;
        this->switchScene = true;
        std::cout << "Button Nr. " << active_button << " was pushed..." << std::endl;
    }
}

void MainOptions::CustomDraw() {

    //Textures
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(mainOptionsBox, (GetScreenWidth() - mainOptionsBox.width)/2, (GetScreenHeight() - mainOptionsBox.height)/2, WHITE);

    //OptionBarTextures
    //DrawTexture(optionBar1, (GetScreenWidth() - optionBar1.width)/2, (GetScreenHeight() - optionBar1.height)/2, WHITE);
    DrawTexture(optionBar100, (GetScreenWidth() - optionBar100.width)/2 + 100, (GetScreenHeight() - optionBar100.height)/2 - 175, WHITE);
    DrawTexture(optionBar100, (GetScreenWidth() - optionBar100.width)/2 + 100, (GetScreenHeight() - optionBar100.height)/2 - 75, WHITE);
    DrawTexture(optionBar100, (GetScreenWidth() - optionBar100.width)/2 + 100, (GetScreenHeight() - optionBar100.height)/2 + 25, WHITE);

    //OptionButton
    DrawTexture(optionButton, (GetScreenWidth() - optionBar100.width)/2 + 100, (GetScreenHeight() - optionBar100.height)/2 + 125, WHITE);
    DrawTexture(optionButton, (GetScreenWidth() - optionBar100.width)/2 + 250, (GetScreenHeight() - optionBar100.height)/2 + 125, WHITE);

    if (IsWindowFullscreen())
    {
        DrawTexture(optionButton, (GetScreenWidth() - optionBar100.width)/2 + 100, (GetScreenHeight() - optionBar100.height)/2 + 125, YELLOW);
    }
    else
    {
        DrawTexture(optionButton, (GetScreenWidth() - optionBar100.width)/2 + 250, (GetScreenHeight() - optionBar100.height)/2 + 125, YELLOW);
    }

    //Messages
    DrawTextEx(font1, Message1.c_str(),fontPosition1, 100, 1,WHITE);
    DrawTextEx(font1, Message2.c_str(),fontPosition2, 50, 1,WHITE);
    DrawTextEx(font1, Message3.c_str(),fontPosition3, 50, 1,WHITE);

    //Buttons
    for (auto& button : buttons)
    {
        button->Draw();
    }
}

void MainOptions::Unload() {
    UnloadFont(font1);
    UnloadSound(uiBlip);
    UnloadSound(uiBlip2);
    UnloadTexture(background);
    UnloadTexture(mainOptionsBox);
    UnloadTexture(optionBar1);
    UnloadTexture(optionBar100);
    UnloadTexture(optionButton);
}