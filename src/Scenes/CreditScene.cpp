//
// Created by Munchkin on 17.08.2022.
//

#include "CreditScene.h"

#include <iostream>

extern float volSfx;

CreditScene::CreditScene()
{
    //background texture
    Image mainMenuBackground = LoadImage("assets/graphics/ui/menu/mainMenuBackground.png");
    ImageResize(&mainMenuBackground, GetScreenWidth(), GetScreenHeight());
    this->background = LoadTextureFromImage(mainMenuBackground);
    UnloadImage(mainMenuBackground);

    //CreditBox
    Image creditBoxImage = LoadImage("assets/graphics/ui/menu/mainMenuBox.png");
    ImageResize(&creditBoxImage, creditBoxImage.width*3, creditBoxImage.height*3);
    this->creditBox = LoadTextureFromImage(creditBoxImage);
    UnloadImage(creditBoxImage);

//Text with font
this->font1 = LoadFont("assets/graphics/ui/Habbo.ttf");

//Sound
    this->uiBlip = LoadSound("assets/audio/sfx/uiBlip.wav");
    this->uiBlip2 = LoadSound("assets/audio/sfx/uiBlip2.wav");

Message1 = "Credits";
Message2 = "Game Design: Marko Lapadatovic, Leah Berner\nLead Artist: Leah Berner\nArtist: Marko Lapadatovic\nLead Programmer: Maximilian Roeck\nProgrammer: Lena White, Sefer Tokdilli\nSound Artist: Maximilian Roeck";

fontPosition1 = {GetScreenWidth()/2 -
                 MeasureTextEx(font1, Message1.c_str(), (float)100, 1).x/2,
                 GetScreenHeight() - (float)100/2 - 850};

fontPosition2 = {(GetScreenWidth()/2 + 450) -
                 MeasureTextEx(font1, Message2.c_str(), (float)100, 1).x/2,
                 GetScreenHeight() - (float)100/2 - 700};

//Buttons
    this->active_button = 0;

    this->buttonReturnMainMenu = new game::Button("Return to Main Menu (Esc)",
                                              GetScreenWidth()/2 - 250,
                                              GetScreenHeight()/2 + 300,
                                              50, 1, YELLOW, WHITE);

    this->buttonReturnMainMenu->active = true;

    this->buttons.push_back(buttonReturnMainMenu);

    this->switchScene = false;
}

CreditScene::~CreditScene() {
        delete buttonReturnMainMenu;
}

void CreditScene::CustomUpdate() {
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

    if (IsKeyPressed(KEY_ESCAPE))
    {
        if(this->buttonReturnMainMenu->active == true)
        {
            PlaySound(this->uiBlip2);
            this->switchTo = MAINMENU;
        }
        this->switchScene = true;
        std::cout << "Button Nr. " << active_button << "was pushed..." << std::endl;
    }
}

void CreditScene::CustomDraw() {

    //Textures
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(creditBox, (GetScreenWidth() - creditBox.width)/2, (GetScreenHeight() - creditBox.height)/2, WHITE);

    //Messages
    DrawTextEx(font1, Message1.c_str(), fontPosition1, 100, 1, WHITE);
    DrawTextEx(font1, Message2.c_str(), fontPosition2, 50, 1, WHITE);

    //Buttons
    for (auto& button : buttons)
    {
        button->Draw();
    }
}

void CreditScene::Unload() {
    UnloadFont(font1);
    UnloadSound(uiBlip);
    UnloadSound(uiBlip2);
    UnloadTexture(background);
    UnloadTexture(creditBox);
}