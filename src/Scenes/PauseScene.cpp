//
// Created by Munchkin on 24.05.2022.
//

#include "PauseScene.h"

#include <iostream>

extern float volSfx;

PauseScene::PauseScene()
{
    //PauseMenuBox
    Image pauseMenuBoxImage = LoadImage("assets/graphics/ui/menu/mainMenuBox.png");
    ImageResize(&pauseMenuBoxImage, pauseMenuBoxImage.width*2.5, pauseMenuBoxImage.height*2.5);
    this->pauseMenuBox = LoadTextureFromImage(pauseMenuBoxImage);
    UnloadImage(pauseMenuBoxImage);

    //Text with font
    this->font1 = LoadFont("assets/graphics/ui/Habbo.ttf");

    //Sound
    this->uiBlip = LoadSound("assets/audio/sfx/uiBlip.wav");
    this->uiBlip2 = LoadSound("assets/audio/sfx/uiBlip2.wav");

    Message1 = "Pause Menu";

    fontPosition1 = {GetScreenWidth()/2 -
                    MeasureTextEx(font1, Message1.c_str(), (float)100, 1).x/2,
                    GetScreenHeight() - (float)100/2 - 750};

    //Buttons
    this->active_button = 0;

    this->buttonReturnGame = new game::Button("Return to Game",
                                              GetScreenWidth()/2,
                                              GetScreenHeight()/2 - 100,
                                              50, 1, YELLOW, WHITE);
    this->buttonReturnGame->active = true;

    this->buttonPauseOptions = new game::Button("Options",
                                                GetScreenWidth()/2,
                                                GetScreenHeight()/2,
                                           50, 1, YELLOW, WHITE);

    this->buttonReturnMainMenu = new game::Button("Return to Main Menu",
                                                  GetScreenWidth()/2,
                                                  GetScreenHeight()/2 + 100,
                                        50, 1, YELLOW, WHITE);

    this->buttons.push_back(buttonReturnGame);
    this->buttons.push_back(buttonPauseOptions);
    this->buttons.push_back(buttonReturnMainMenu);

    this->switchScene = false;
}

PauseScene::~PauseScene() {
    delete buttonReturnGame;
    delete buttonPauseOptions;
    delete buttonReturnMainMenu;
}

void PauseScene::CustomUpdate() {
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
        if (this->buttonPauseOptions->active == true)
        {
            PlaySound(this->uiBlip2);
            this->switchTo = PAUSEOPTIONS;
        }
        if (this->buttonReturnGame->active == true)
        {
            PlaySound(this->uiBlip2);
            this->switchTo = GAME;
        }
        if (this->buttonReturnMainMenu->active == true)
        {
            PlaySound(this->uiBlip2);
            this->switchTo = MAINMENU; //confirmation before leaving game?
        }

        this->switchScene = true;
        std::cout << "Button Nr. " << active_button << " was pushed..." << std::endl;
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        this->switchScene = true;
        std::cout << "Button Nr. " << active_button << "was pushed..." << std::endl;
    }
}

void PauseScene::CustomDraw() {

    //Textures
    DrawTexture(pauseMenuBox, (GetScreenWidth() - pauseMenuBox.width)/2, (GetScreenHeight() - pauseMenuBox.height)/2, WHITE);

    //Messages
    DrawTextEx(font1, Message1.c_str(), fontPosition1, 100, 1, WHITE);

    //Buttons
    for (auto& button : buttons)
    {
        button->Draw();
    }
}

void PauseScene::Unload() {
    UnloadFont(font1);
    UnloadSound(uiBlip);
    UnloadSound(uiBlip2);
    UnloadTexture(pauseMenuBox);
}
