//
// Created by Munchkin on 24.05.2022.
//

#include "PauseScene.h"

#include <iostream>

PauseScene::PauseScene()
{
    //Buttons
    this->active_button = 0;

    this->buttonReturnGame = new game::Button(LoadTexture("assets/graphics/ui/combat/Button.png"),
                                           LoadTexture("assets/graphics/ui/combat/Button.png"),
                                           100,
                                           100,
                                           true);

    this->buttonPauseOptions = new game::Button(LoadTexture("assets/graphics/ui/combat/Button.png"),
                                           LoadTexture("assets/graphics/ui/combat/Button.png"),
                                           100,
                                           200,
                                           false);

    this->buttonReturnMainMenu = new game::Button(LoadTexture("assets/graphics/ui/combat/Button.png"),
                                        LoadTexture("assets/graphics/ui/combat/Button.png"),
                                        100,
                                        300,
                                        false);

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

void PauseScene::Update() {
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
        std::cout << "Button Nr. " << active_button << " pushed..." << std::endl;
    }
}

void PauseScene::Draw() {
    for (auto& button : buttons)
    {
        DrawText("This is the Pause Menu.\nPlease use the arrow keys to select your desired option:\nThen press Enter to continue.",
                 10, 10, 30, LIGHTGRAY);

        // DrawTexture("assets/graphics/ui/menu/mainMenuBox.png", Game::ScreenWidth/2 - titleScreen.width/2, Game::ScreenHeight/4 - titleScreen.height/4,WHITE);
        // DrawTexture("assets/graphics/ui/menu/mainMenuBox.png",  screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2,WHITE);

        DrawTexture(button->getTexture(), button->pos_x, button->pos_y, WHITE);
    }
}