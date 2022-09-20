//
// Created by Munchkin on 05.09.2022.
//

#include "PauseOptions.h"

#include <iostream>

extern float volMusic;
extern float volSfx;
extern float brightness;

PauseOptions::PauseOptions()
{
  //PauseOptionsBox
    Image mainMenuBoxImage = LoadImage("assets/graphics/ui/menu/mainMenuBox.png");
    ImageResize(&mainMenuBoxImage, mainMenuBoxImage.width*3, mainMenuBoxImage.height*3);
    this->pauseOptionsBox = LoadTextureFromImage(mainMenuBoxImage);
    UnloadImage(mainMenuBoxImage);

    //OptionBars
    this->optionBar = LoadTexture("assets/graphics/ui/menu/Optionbar/Option10.png");

    //OptionsButton
    this->optionButton = LoadTexture("assets/graphics/ui/menu/Optionbar/OptionsButton.png");

    //Text with font
    this->font1 = LoadFont("assets/graphics/ui/Habbo.ttf");

    //Sound
    this->uiBlip = LoadSound("assets/audio/sfx/uiBlip.wav");
    this->uiBlip2 = LoadSound("assets/audio/sfx/uiBlip2.wav");
    this->punchSound = LoadSound("assets/audio/sfx/punch.wav");

    this->bomb = LoadSound("assets/audio/sfx/bomb.wav");
    this->chatter = LoadSound("assets/audio/sfx/chatter.wav");
    this->gunshot = LoadSound("assets/audio/sfx/gunshot.wav");
    this->kaching = LoadSound("assets/audio/sfx/kaching.wav");
    this->laser = LoadSound("assets/audio/sfx/laser.wav");
    this->slurp = LoadSound("assets/audio/sfx/slurp.wav");
    this->tazer = LoadSound("assets/audio/sfx/tazer.wav");
    this->uiBlocked = LoadSound("assets/audio/sfx/whip.wav");
    this->whip = LoadSound("assets/audio/sfx/whip.wav");
    this->whipCrack = LoadSound("assets/audio/sfx/whipCrack.wav");

    SetSoundVolume(punchSound, volSfx);
    SetSoundVolume(uiBlip, volSfx);
    SetSoundVolume(uiBlip2, volSfx);
    SetSoundVolume(bomb, volSfx);
    SetSoundVolume(chatter, volSfx);
    SetSoundVolume(gunshot, volSfx);
    SetSoundVolume(kaching, volSfx);
    SetSoundVolume(laser, volSfx);
    SetSoundVolume(slurp, volSfx);
    SetSoundVolume(tazer, volSfx);
    SetSoundVolume(uiBlocked, volSfx);
    SetSoundVolume(whip, volSfx);
    SetSoundVolume(whipCrack, volSfx);

    Message1 = "Options";
    Message2 = "On";
    Message3 = "Off";
    Message4 = "(Use left & right arrow keys to adjust)";

    fontPosition1 = {GetScreenWidth()/2 -
                     MeasureTextEx(font1, Message1.c_str(), (float)100, 1).x/2,
                     GetScreenHeight() - (float)100/2 - 850};

    fontPosition2 = {GetScreenWidth()/2 - 25 -
                     MeasureTextEx(font1, Message2.c_str(), (float)50, 1).x/2,
                     GetScreenHeight() - (float)50/2 - 375};

    fontPosition3 = {GetScreenWidth()/2 + 130 -
                     MeasureTextEx(font1, Message3.c_str(), (float)50, 1).x/2,
                     GetScreenHeight() - (float)50/2 - 375};

    fontPosition4 = {GetScreenWidth()/2 + 175 -
                     MeasureTextEx(font1, Message4.c_str(), (float)25, 1).x/2,
                     GetScreenHeight() - (float)25/2 - 680};

    fontPosition5 = {GetScreenWidth()/2 + 175 -
                     MeasureTextEx(font1, Message4.c_str(), (float)25, 1).x/2,
                     GetScreenHeight() - (float)25/2 - 580};

    fontPosition6 = {GetScreenWidth()/2 + 175 -
                     MeasureTextEx(font1, Message4.c_str(), (float)25, 1).x/2,
                     GetScreenHeight() - (float)25/2 - 480};

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

    this->buttonReturnPauseMenu = new game::Button("Pause Menu (Esc)",
                                                  GetScreenWidth()/2 - 250,
                                                  GetScreenHeight()/2 + 250,
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
        if (this->buttonSFX->active == true)
        {
            PlaySound(this->punchSound);
        }

        if (this->buttonFullscreen->active == true)
        {
            PlaySound(this->uiBlip2);
            ToggleFullscreen();
        }
        std::cout << "Button Nr. " << active_button << " was pushed..." << std::endl;
    }

    if (this->buttonSFX->active == true)
    {
        if (IsKeyPressed(KEY_LEFT))
        {
            if (volSfx >= 0)
            {
                volSfx -= 0.1;
                SetSoundVolume(punchSound, volSfx);
                SetSoundVolume(uiBlip, volSfx);
                SetSoundVolume(uiBlip2, volSfx);
                SetSoundVolume(bomb, volSfx);
                SetSoundVolume(chatter, volSfx);
                SetSoundVolume(gunshot, volSfx);
                SetSoundVolume(kaching, volSfx);
                SetSoundVolume(laser, volSfx);
                SetSoundVolume(slurp, volSfx);
                SetSoundVolume(tazer, volSfx);
                SetSoundVolume(uiBlocked, volSfx);
                SetSoundVolume(whip, volSfx);
                SetSoundVolume(whipCrack, volSfx);
                PlaySound(this->punchSound);
            }
        }
        if (IsKeyPressed(KEY_RIGHT))
        {
            if (volSfx <= 0.9)
            {
                volSfx += 0.1;
                SetSoundVolume(punchSound, volSfx); //"->" damit man sieht dass es ein Attribut ist
                SetSoundVolume(uiBlip, volSfx);
                SetSoundVolume(uiBlip2, volSfx);
                SetSoundVolume(bomb, volSfx);
                SetSoundVolume(chatter, volSfx);
                SetSoundVolume(gunshot, volSfx);
                SetSoundVolume(kaching, volSfx);
                SetSoundVolume(laser, volSfx);
                SetSoundVolume(slurp, volSfx);
                SetSoundVolume(tazer, volSfx);
                SetSoundVolume(uiBlocked, volSfx);
                SetSoundVolume(whip, volSfx);
                SetSoundVolume(whipCrack, volSfx);
                PlaySound(this->punchSound);
            }
        }
    }

    if (this->buttonBrightness->active == true)
    {
        if (IsKeyPressed(KEY_LEFT))
        {
            if (brightness <= 0.9)
            {
                brightness += 0.1;
            }
        }
        if (IsKeyPressed(KEY_RIGHT))
        {
            if (brightness >= 0.1)
            {
                brightness -= 0.1;
            }
        }
    }

    if(IsKeyPressed(KEY_ESCAPE))
    {
        PlaySound(this->uiBlip2);
        this->switchTo = PAUSEMENU;
        this->switchScene = true;
        std::cout << "Button Nr. " << active_button << " was pushed..." << std::endl;
    }
}

void PauseOptions::CustomDraw() {
    //we don't need percentage variables since we already use float
    //however, the variable "brightnessPercentage" is needed, because the bar for brightness is inverted
    float brightnessPercentage = 1 - brightness;

    float RecWidthMusic = optionBar.width - optionBar.width * volMusic;
    float RecWidthSfx = optionBar.width - optionBar.width * volSfx;
    float RecWidthBrightness = optionBar.width - optionBar.width * brightnessPercentage;

    //Textures
    DrawTexture(pauseOptionsBox, (GetScreenWidth() - pauseOptionsBox.width)/2, (GetScreenHeight() - pauseOptionsBox.height)/2, WHITE);

    //OptionBarTextures
    DrawTexture(optionBar, (GetScreenWidth() - optionBar.width)/2 + 100, (GetScreenHeight() - optionBar.height)/2 - 175, WHITE);
    DrawTexture(optionBar, (GetScreenWidth() - optionBar.width)/2 + 100, (GetScreenHeight() - optionBar.height)/2 - 75, WHITE);
    DrawTexture(optionBar, (GetScreenWidth() - optionBar.width)/2 + 100, (GetScreenHeight() - optionBar.height)/2 + 25, WHITE);
    DrawRectangle((GetScreenWidth() - optionBar.width)/2 + 100 + optionBar.width - RecWidthMusic, (GetScreenHeight() - optionBar.height)/2 - 175, RecWidthMusic, 30, BLACK);
    DrawRectangle((GetScreenWidth() - optionBar.width)/2 + 100 + optionBar.width - RecWidthSfx, (GetScreenHeight() - optionBar.height)/2 - 75, RecWidthSfx, 30, BLACK);
    DrawRectangle((GetScreenWidth() - optionBar.width)/2 + 100 + optionBar.width - RecWidthBrightness, (GetScreenHeight() - optionBar.height)/2 + 25, RecWidthBrightness, 30, BLACK);

    //OptionButton
    DrawTexture(optionButton, (GetScreenWidth() - optionBar.width)/2 + 100, (GetScreenHeight() - optionBar.height)/2 + 125, WHITE);
    DrawTexture(optionButton, (GetScreenWidth() - optionBar.width)/2 + 250, (GetScreenHeight() - optionBar.height)/2 + 125, WHITE);

    if (IsWindowFullscreen())
    {
        DrawTexture(optionButton, (GetScreenWidth() - optionBar.width)/2 + 100, (GetScreenHeight() - optionBar.height)/2 + 125, YELLOW);
        DrawRectangleLines(fontPosition2.x, fontPosition2.y,
                           MeasureTextEx(font1, Message2.c_str(), 50, 1).x,
                           MeasureTextEx(font1, Message2.c_str(), 50, 1).y, YELLOW);
    }
    else
    {
        DrawTexture(optionButton, (GetScreenWidth() - optionBar.width)/2 + 250, (GetScreenHeight() - optionBar.height)/2 + 125, YELLOW);
        DrawRectangleLines(fontPosition3.x, fontPosition3.y,
                           MeasureTextEx(font1, Message3.c_str(), 50, 1).x,
                           MeasureTextEx(font1, Message3.c_str(), 50, 1).y, YELLOW);
    }

    //Messages
    DrawTextEx(font1, Message1.c_str(),fontPosition1, 100, 1,WHITE);
    DrawTextEx(font1, Message2.c_str(),fontPosition2, 50, 1,WHITE);
    DrawTextEx(font1, Message3.c_str(),fontPosition3, 50, 1,WHITE);
    DrawTextEx(font1, Message4.c_str(),fontPosition4, 25, 1,WHITE);
    DrawTextEx(font1, Message4.c_str(),fontPosition5, 25, 1,WHITE);
    DrawTextEx(font1, Message4.c_str(),fontPosition6, 25, 1,WHITE);

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
    UnloadSound(punchSound);
    UnloadSound(bomb);
    UnloadSound(chatter);
    UnloadSound(gunshot);
    UnloadSound(kaching);
    UnloadSound(laser);
    UnloadSound(slurp);
    UnloadSound(tazer);
    UnloadSound(uiBlocked);
    UnloadSound(whip);
    UnloadSound(whipCrack);

    UnloadTexture(pauseOptionsBox);
    UnloadTexture(optionBar);
    UnloadTexture(optionButton);
}