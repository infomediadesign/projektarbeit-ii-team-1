//
// Created by Munchkin on 15.09.2022.
//

#include "MainControls.h"


#include <iostream>

extern float volSfx;

MainControls::MainControls()
{
    //background texture
    Image mainMenuBackground = LoadImage("assets/graphics/ui/menu/mainMenuBackground.png");
    ImageResize(&mainMenuBackground, GetScreenWidth(), GetScreenHeight());
    this->background = LoadTextureFromImage(mainMenuBackground);
    UnloadImage(mainMenuBackground);

    //CreditBox
    Image creditBoxImage = LoadImage("assets/graphics/ui/menu/mainMenuBox.png");
    ImageResize(&creditBoxImage, creditBoxImage.width*3, creditBoxImage.height*3);
    this->controlBox = LoadTextureFromImage(creditBoxImage);
    UnloadImage(creditBoxImage);

//Text with font
    this->font1 = LoadFont("assets/graphics/ui/Habbo.ttf");

//Sound
    this->uiBlip = LoadSound("assets/audio/sfx/uiBlip.wav");
    this->uiBlip2 = LoadSound("assets/audio/sfx/uiBlip2.wav");

    SetSoundVolume(uiBlip, volSfx);
    SetSoundVolume(uiBlip2, volSfx);

    Message1 = "Controls";
    Message2 = "Walking/Menu Navigation: WASD/Arrow Keys\n" //WASD noch einbauen!!!
               "Interactions/Dialogue/Confirmations: E\n"
               "Inventory: I\n"
               "Skill Tree: C\n"
               "Menu: ESC\n"
               "Menu Confirmation: ENTER";

    fontPosition1 = {GetScreenWidth()/2 -
                     MeasureTextEx(font1, Message1.c_str(), (float)100, 1).x/2,
                     GetScreenHeight() - (float)100/2 - 850};

    fontPosition2 = {(GetScreenWidth()/2 + 450) -
                     MeasureTextEx(font1, Message2.c_str(), (float)100, 1).x/2,
                     GetScreenHeight() - (float)100/2 - 700};

//Buttons
    this->active_button = 0;

    this->buttonReturnMainMenu = new game::Button("Return (Esc)",
                                                  GetScreenWidth()/2 - 315,
                                                  GetScreenHeight()/2 + 300,
                                                  50, 1, YELLOW, WHITE);

    this->buttonReturnMainMenu->active = true;

    this->buttons.push_back(buttonReturnMainMenu);

    this->switchScene = false;
}

MainControls::~MainControls() {
    delete buttonReturnMainMenu;
}

void MainControls::CustomUpdate() {
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        buttons[active_button]->active = false;
        if (active_button < buttons.size() - 1)
            active_button++;
        else active_button = 0;

        buttons[active_button]->active = true;
        PlaySound(this->uiBlip);
    }

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
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
        PlaySound(this->uiBlip2);
        this->switchTo = MAINMENU;
        this->switchScene = true;
        std::cout << "Button Nr. " << active_button << "was pushed..." << std::endl;
    }
}

void MainControls::CustomDraw() {

    //Textures
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(controlBox, (GetScreenWidth() - controlBox.width)/2, (GetScreenHeight() - controlBox.height)/2, WHITE);

    //Messages
    DrawTextEx(font1, Message1.c_str(), fontPosition1, 100, 1, WHITE);
    DrawTextEx(font1, Message2.c_str(), fontPosition2, 50, 1, WHITE);

    //Buttons
    for (auto& button : buttons)
    {
        button->Draw();
    }
}

void MainControls::Unload() {
    UnloadFont(font1);
    UnloadSound(uiBlip);
    UnloadSound(uiBlip2);
    UnloadTexture(background);
    UnloadTexture(controlBox);
}