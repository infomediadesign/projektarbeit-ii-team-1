//

// Created by Munchkin on 24.05.2022.
//

#include "MainMenuScene.h"

#include <iostream>

MainMenuScene::MainMenuScene() {
    //background texture
    Image mainMenuBackground = LoadImage("assets/graphics/ui/menu/mainMenuBackground.png");
    ImageResize(&mainMenuBackground, GetScreenWidth(), GetScreenHeight());
    this->background = LoadTextureFromImage(mainMenuBackground);
    UnloadImage(mainMenuBackground);

    //MainMenuBox
    Image mainMenuBoxImage = LoadImage("assets/graphics/ui/menu/mainMenuBox.png");
    ImageResize(&mainMenuBoxImage, mainMenuBoxImage.width*2.5, mainMenuBoxImage.height*2.5);
    this->mainMenuBox = LoadTextureFromImage(mainMenuBoxImage);
    UnloadImage(mainMenuBoxImage);

    //Text with font
    this->font1 = LoadFont("assets/graphics/ui/Habbo.ttf");

    Message1 = "Main Menu";

    fontPosition1 = {GetScreenWidth()/2 -
                    MeasureTextEx(font1, Message1.c_str(), (float)100, 1).x/2,
                    GetScreenHeight() - (float)100/2 -750};

    //Buttons
    this->active_button = 0;

    this->buttonNewGame = new game::Button("New Game",
                                           GetScreenWidth()/2,
                                           GetScreenHeight()/2 - 100,
                                     50, 1, YELLOW, WHITE);
    this->buttonNewGame->active = true;

    this->buttonOptions = new game::Button("Options",
                                           GetScreenWidth()/2,
                                           GetScreenHeight()/2,
                                           50, 1, YELLOW, WHITE);

    this->buttonCredits = new game::Button("Credits",
                                           GetScreenWidth()/2,
                                           GetScreenHeight()/2 + 100,
                                           50, 1, YELLOW, WHITE);

    this->buttonExit = new game::Button("Exit",
                                        GetScreenWidth()/2,
                                        GetScreenHeight()/2 + 200,
                                        50, 1, YELLOW, WHITE);

    this->buttons.push_back(buttonNewGame);
    this->buttons.push_back(buttonOptions);
    this->buttons.push_back(buttonCredits);
    this->buttons.push_back(buttonExit);

    this->switchScene = false;
}

MainMenuScene::~MainMenuScene() {
    delete buttonNewGame;
    delete buttonOptions;
    delete buttonCredits;
    delete buttonExit;
}

void MainMenuScene::CustomUpdate() {
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

    if (IsKeyPressed(KEY_ENTER))
    {
        this->switchScene = true;
        this->switchTo = TESTSCENE; // HAS TO BE REPLACED WITH "GAME" WHEN POSSIBLE!!
        std::cout << "Button Nr. " << active_button << " was pushed..." << std::endl;
    }

    //Skips right ahead, basically skips main menu but why??
    /*if (this->buttonNewGame->active == true)
    {
        this->switchScene = true;
    }*/

}

void MainMenuScene::CustomDraw() {

    //Textures
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(mainMenuBox, (GetScreenWidth() - mainMenuBox.width)/2, (GetScreenHeight() - mainMenuBox.height)/2, WHITE);

    //Messages
    DrawTextEx(font1, Message1.c_str(),fontPosition1, 100, 1,WHITE);

    //Buttons
    for (auto& button : buttons)
    {
       button->Draw();
    }
}

void MainMenuScene::Unload() {
    UnloadFont(font1);
    UnloadTexture(background);
    UnloadTexture(mainMenuBox);
}