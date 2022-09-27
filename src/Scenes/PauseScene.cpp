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

    //Confirmation Box
    /*Image confirmationBoxImage = LoadImage("assets/graphics/ui/menu/mainMenuBox.png");
    ImageResize(&confirmationBoxImage, confirmationBoxImage.width*2, confirmationBoxImage.height*1);
    this->confirmationBox = LoadTextureFromImage(confirmationBoxImage);
    UnloadImage(confirmationBoxImage);*/

    //Text with font
    this->font1 = LoadFont("assets/graphics/ui/Habbo.ttf");

    //Sound
    this->uiBlip = LoadSound("assets/audio/sfx/uiBlip.wav");
    this->uiBlip2 = LoadSound("assets/audio/sfx/uiBlip2.wav");

    SetSoundVolume(uiBlip, volSfx);
    SetSoundVolume(uiBlip2, volSfx);

    Message1 = "Pause Menu";
    //Message2 = "Are you sure you want to exit?";

    fontPosition1 = {GetScreenWidth()/2 -
                    MeasureTextEx(font1, Message1.c_str(), (float)100, 1).x/2,
                    GetScreenHeight() - (float)100/2 - 750};

    /*fontPosition2 = {GetScreenWidth()/2 -
                     MeasureTextEx(font1, Message2.c_str(), (float)50, 1).x/2,
                     GetScreenHeight() - (float)50/2 - 500};*/

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

    this->buttonControls = new game::Button("Controls",
                                            GetScreenWidth()/2,
                                            GetScreenHeight()/2 + 100,
                                            50, 1, YELLOW, WHITE);


    this->buttonReturnMainMenu = new game::Button("Return to Main Menu",
                                                  GetScreenWidth()/2,
                                                  GetScreenHeight()/2 + 200,
                                        50, 1, YELLOW, WHITE);

    this->buttons.push_back(buttonReturnGame);
    this->buttons.push_back(buttonPauseOptions);
    this->buttons.push_back(buttonControls);
    this->buttons.push_back(buttonReturnMainMenu);

    //this->Confirmation();

    this->switchScene = false;
}

PauseScene::~PauseScene() {
    delete buttonReturnGame;
    delete buttonPauseOptions;
    delete buttonControls;
    delete buttonReturnMainMenu;
    //delete buttonYes;
    //delete buttonNo;
}

void PauseScene::CustomUpdate() {
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

    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
    {
        buttons[active_button]->active = false;
        if (active_button < buttons.size() - 1)
            active_button++;
        else active_button = 0;

        buttons[active_button]->active = true;
        PlaySound(this->uiBlip);
    }

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
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
        if(this->buttonControls->active == true)
        {
            PlaySound(this->uiBlip2);
            this->switchTo = PAUSECONTROLS;
        }
        if (this->buttonReturnGame->active == true)
        {
            PlaySound(this->uiBlip2);
            this->switchTo = GAME;
        }
        if (this->buttonReturnMainMenu->active == true)
        {
            /*if(this->buttonYes->active == true)
            {
                PlaySound(this->uiBlip2);
                this->switchTo = MAINMENU;
            }
            if (this->buttonNo->active == true)
            {
                PlaySound(this->uiBlip2);
                //this->switchTo = PAUSEMENU; //do i need this, when i already am in Pausemenu? is there a better way to get out of confirmation screen?
            }*/
            this->switchTo = MAINMENU; //eventuell rausnehmen, wenn confirmation box implementiert wird
            PlaySound(this->uiBlip2);
        }

        this->switchScene = true;
        std::cout << "Button Nr. " << active_button << " was pushed..." << std::endl;
    }

}

void PauseScene::CustomDraw() {

    //Textures
    DrawTexture(pauseMenuBox, (GetScreenWidth() - pauseMenuBox.width)/2, (GetScreenHeight() - pauseMenuBox.height)/2, WHITE);

    //Messages
    DrawTextEx(font1, Message1.c_str(), fontPosition1, 100, 1, WHITE);

    /*if (this->buttonReturnMainMenu->active == true)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            DrawTexture(confirmationBox, (GetScreenWidth() - confirmationBox.width)/2, (GetScreenHeight() - confirmationBox.height)/2, WHITE);
            DrawTextEx(font1, Message2.c_str(), fontPosition2, 50, 1, WHITE);
        }
    }*/

    //Buttons
    for (auto& button : buttons)
    {
        button->Draw();
    }
}

/*void PauseScene::Confirmation()
{

    //if (IsKeyPressed(KEY_ENTER))
    //{
        if (this->buttonReturnMainMenu->active == true)
        {
            this->active_button = 0;

            this->buttonYes = new game::Button("Yes",
                                               GetScreenWidth()/2 + 100,
                                               GetScreenHeight()/2 + 300,
                                               50, 1, YELLOW, WHITE);

            this->buttonYes->active = true;

            this->buttonNo = new game::Button("No",
                                              GetScreenWidth()/2 + 150,
                                              GetScreenHeight()/2 + 300,
                                              50, 1, YELLOW, WHITE);

            this->buttons.push_back(buttonYes);
            this->buttons.push_back(buttonNo);

            this->switchScene = false;

            if (IsKeyPressed(KEY_ENTER))
            {
                if (this->buttonYes->active == true)
                {
                    //if (IsKeyPressed(KEY_ENTER)) {
                        PlaySound(this->uiBlip2);
                        this->switchTo = MAINMENU;
                    //}
                }
                if (this->buttonNo->active == true)
                {
                    // (IsKeyPressed(KEY_ENTER)) {
                        PlaySound(this->uiBlip2);
                        this->switchTo = PAUSEMENU; //do i need this, when i already am in Pausemenu? is there a better way to get out of confirmation screen?
                    //}
                }
                PlaySound(this->uiBlip2);
                this->switchScene = true;
                std::cout << "Button Nr. " << active_button << " was pushed..." << std::endl;
            }
        }
    //}

    if (this->buttonReturnMainMenu->active == true) // == makes the program crash, but = doesnt display it correctly
    {
        this->buttonYes = new game::Button("Yes",
                                           GetScreenWidth()/2 + 100,
                                           GetScreenHeight()/2 + 300,
                                           50, 1, YELLOW, WHITE);

        this->buttonNo = new game::Button("No",
                                          GetScreenWidth()/2 + 150,
                                          GetScreenHeight()/2 + 300,
                                          50, 1, YELLOW, WHITE);

        this->buttons.push_back(buttonYes);
        this->buttons.push_back(buttonNo);
    }
}*/

void PauseScene::Unload() {
    UnloadFont(font1);
    UnloadSound(uiBlip);
    UnloadSound(uiBlip2);
    UnloadTexture(pauseMenuBox);
    //UnloadTexture(confirmationBox);
}
