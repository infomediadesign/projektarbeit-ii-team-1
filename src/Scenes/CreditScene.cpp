//
// Created by Munchkin on 17.08.2022.
//

#include "CreditScene.h"

#include <iostream>

CreditScene::CreditScene()
{
    //CreditBox
Image creditBoxImage = LoadImage("assets/graphics/ui/menu/mainMenuBox.png");
ImageResize(&creditBoxImage, creditBoxImage.width*2.5, creditBoxImage.height*2.5);
this->creditBox = LoadTextureFromImage(creditBoxImage);
UnloadImage(creditBoxImage);

//Text with font
this->font1 = LoadFont("assets/graphics/ui/Habbo.ttf");

Message1 = "Credits";
Message2 = "Game Design: Marko Lapadatovic, Leah Berner\nLead Artist: Leah Berner\nArtist: Marko Lapadatovic\nLead Programmer: Maximilian Röck\nProgrammer: Lena White, Sefer Tokdilli\nSound Artist: Maximilian Röck";

fontPosition1 = {GetScreenWidth()/2 -
                 MeasureTextEx(font1, Message1.c_str(), (float)100, 1).x/2,
                 GetScreenHeight() - (float)100/2 - 750};

fontPosition2 = {GetScreenWidth()/2 -
                 MeasureTextEx(font1, Message2.c_str(), (float)100, 1).x/2,
                 GetScreenHeight() - (float)100/2 - 500};

//Buttons
    this->active_button = 0;

    this->buttonReturnMainMenu = new game::Button("Return to Main Menu",
                                              GetScreenWidth()/2,
                                              GetScreenHeight()/2 - 100,
                                              50, 1, YELLOW, WHITE);

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
    }

    if (IsKeyPressed(KEY_UP))
    {
        buttons[active_button]->active = false;
        if (active_button == 0)
            active_button = (int)buttons.size() - 1;
        else active_button--;

        buttons[active_button]->active = true;
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        this->switchTo = MAINMENU;
        this->switchScene = true;
        std::cout << "Button Nr. " << active_button << "was pushed..." << std::endl;
    }
}

void CreditScene::CustomDraw() {

    //Textures
    DrawTexture(creditBox, (GetScreenWidth() - creditBox.width)/2, (GetScreenHeight() - creditBox.height)/2, WHITE);

    //Messages
    DrawTextEx(font1, Message1.c_str(), fontPosition1, 100, 1, WHITE);
    DrawTextEx(font1, Message2.c_str(), fontPosition2, 100, 1, WHITE);

    //Buttons
    for (auto& button : buttons)
    {
        button->Draw();
    }
}

void CreditScene::Unload() {
    UnloadFont(font1);
    UnloadTexture(creditBox);
}