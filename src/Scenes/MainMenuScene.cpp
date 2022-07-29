//
// Created by Munchkin on 24.05.2022.
//

#include "MainMenuScene.h"

#include <iostream>

MainMenuScene::MainMenuScene() {
    this->active_button = 0;

    this->button1 = new game::Button(LoadTexture("assets/graphics/ui/combat/Button.png"),
                                     LoadTexture("assets/graphics/ui/combat/Button.png"),
                                     100,
                                     100,
                                     true);

    this->button2 = new game::Button(LoadTexture("assets/graphics/ui/combat/Button.png"),
                                     LoadTexture("assets/graphics/ui/combat/Button.png"),
                                     100,
                                     200,
                                     false);

    this->button3 = new game::Button(LoadTexture("assets/graphics/ui/combat/Button.png"),
                                     LoadTexture("assets/graphics/ui/combat/Button.png"),
                                     100,
                                     300,
                                     false);

    this->buttons.push_back(button1);
    this->buttons.push_back(button2);
    this->buttons.push_back(button3);

    this->switchScene = false;
}

MainMenuScene::~MainMenuScene() {
    delete button1;
    delete button2;
    delete button3;
}

void MainMenuScene::Update() {
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

void MainMenuScene::Draw() {
    for (auto& button : buttons)
    {
        DrawText("This is the Main Menu.\nPlease use the arrow keys to select your desired option:\nThen press Enter to continue.",
                 10, 10, 30, LIGHTGRAY);

        DrawTexture(button->getTexture(), button->pos_x, button->pos_y, WHITE);
    }
}
