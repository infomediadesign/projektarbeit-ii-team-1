//
// Created by 22max on 19.08.2022.
//

#include "ShopBarkeeper.h"

ShopBarkeeper::ShopBarkeeper(std::shared_ptr<Player> player, std::shared_ptr<Barkeeper> barkeeper)
{
    this->drawLevelBackground = false; // NOT FINAL, HAS TO BE CHANGED WHEN LEVELS WORK
    this->switchScene = false;

    this->panelPos = {static_cast<float>(GetScreenWidth() / 3.5), static_cast<float>(GetScreenHeight() / 20)};

    this->player = player;
    this->barkeeper = barkeeper;

    this->panelTexture = LoadTexture("assets/graphics/ui/shopAndInv/shopBarkeeper.png");

    //this->bombTexture = LoadImage("assets/graphics/items/weapons/bomb.png");
    //this->frisbeeTexture = LoadImage("assets/graphics/items/weapons/frisbee.png");
    //this->longdrinkTexture = LoadImage("assets/graphics/items/heal/longdrink.png");

    this->activeButton = 0;
    this->updateButtons();

}

void ShopBarkeeper::CustomUpdate()
{
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        buttons[activeButton]->active = false;
        if (activeButton < buttons.size() - 1)
            activeButton++;
        else activeButton = 0;

        buttons[activeButton]->active = true;
    }

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        buttons[activeButton]->active = false;
        if (activeButton == 0)
            activeButton = (int)buttons.size() - 1;
        else activeButton--;

        buttons[activeButton]->active = true;
    }

    if (IsKeyPressed(KEY_E))
    {
        if (this->buttons[this->activeButton]->blocked == false) {
            switch (this->activeButton) {
                case 0:
                    this->player->money = this->player->money - this->bomb.price;
                    this->player->inventory.push_back(std::make_shared<Bomb>());
                    this->barkeeper->stockBomb--;
                    break;
                case 1:
                    this->player->money = this->player->money - this->frisbee.price;
                    this->player->inventory.push_back(std::make_shared<Frisbee>());
                    this->barkeeper->stockFrisbee--;
                    break;
                case 2:
                    this->player->money = this->player->money - this->longdrink.price;
                    this->player->inventory.push_back(std::make_shared<Longdrink>());
            }
    }
        else
        {
            // Play blocked button sound
        }
        this->updateButtons();
    }
    if (IsKeyPressed(KEY_ESCAPE))
    {
        this->switchTo = GAME;
        this->switchScene = true;
    }
}

void ShopBarkeeper::CustomDraw()
{

    DrawTexture(this->panelTexture, this->panelPos.x, this->panelPos.y, WHITE);

    for (int i = 0; i < this->buttons.size(); i++)
    {
        buttons[i]->Draw();
    }

    //DrawTexture(this->bombTexture, panelPos.x + GetScreenWidth() * 0.01, panelPos.y + GetScreenHeight() * 0.01, WHITE);
    //DrawTexture(this->frisbeeTexture, panelPos.x + GetScreenWidth() * 0.01, panelPos.y + GetScreenHeight() * 0.1, WHITE);
    //DrawTexture(this->longdrinkTexture, panelPos.x + GetScreenWidth() * 0.01, panelPos.y + GetScreenHeight() * 0.05, WHITE);
}

void ShopBarkeeper::updateButtons()
{
    this->buttons.clear();
    std::string workingString;

    // i translates to: 0 = Bomb, 1 = Frisbee, 2 = Heal
    for (int i = 0; i < 3; i++)
    {
        workingString.clear(); // Just to be safe
        TraceLog(LOG_INFO, "Buttons: Adding stock...");
        switch(i)
        {
            case 0:
                workingString = std::to_string(this->barkeeper->stockBomb);
                workingString.append("x ");
                break;
            case 1:
                workingString = std::to_string(this->barkeeper->stockFrisbee);
                workingString.append("x ");
        }
        TraceLog(LOG_INFO, "Buttons: Added stock");
        switch(i)
        {
            case 0:
                workingString.append("Discobomb ");
                break;
            case 1:
                workingString.append("Frisbee ");
                break;
            case 2:
                workingString.append("Longdrink ");
        }
        workingString.push_back('(');
        switch(i)
        {
            case 0:
                workingString.append(std::to_string(this->bomb.price));
                break;
            case 1:
                workingString.append(std::to_string(this->frisbee.price));
                break;
            case 2:
                workingString.append(std::to_string(this->longdrink.price));
        }
        workingString.append("$)");
        float height;
        switch (i)
        {
            case 0:
                height = GetScreenHeight() * 0.2;
                break;
            case 1:
                height = GetScreenHeight() * 0.475;
                break;
            case 2:
                height = GetScreenHeight() * 0.725;
        }

        this->buttons.push_back(std::make_shared<game::Button>(workingString.c_str(),
                                                         this->panelPos.x + GetScreenWidth() * 0.285,
                                                         height,
                                                         50, 1, YELLOW, WHITE));
        this->buttons[this->activeButton]->active = true;
    }
    // Disable buttons
    if (this->player->money < this->bomb.price || this->barkeeper->stockBomb <= 0)
    {
        buttons[0]->blocked = true;
    }
    if (this->player->money < this->bomb.price || this->barkeeper->stockFrisbee <= 0)
    {
        buttons[1]->blocked = true;
    }
    if (this->player->money < this->bomb.price)
    {
        buttons[2]->blocked = true;
    }
}
