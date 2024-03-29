//
// Created by 22max on 20.08.2022.
//

#include "ShopDealer.h"

#include <iostream> // For tests only

extern float volSfx;

ShopDealer::ShopDealer(std::shared_ptr<Player> player)
{
    TraceLog(LOG_INFO, "Shop constructor called");

    this->drawLevelBackground = true;
    this->switchScene = false;

    this->panelPos = {static_cast<float>(GetScreenWidth() * 0.305), static_cast<float>(GetScreenHeight() * 0.25)};

    this->player = player;

    this->panelTexture = LoadTexture("assets/graphics/ui/shopAndInv/shopDealer.png");

    this->uiBlip = LoadSound("assets/audio/sfx/uiBlip.wav");
    SetSoundVolume(this->uiBlip, volSfx);
    this->uiBlip2 = LoadSound("assets/audio/sfx/uiBlip2.wav");
    SetSoundVolume(this->uiBlip2, volSfx);
    this->uiBlocked = LoadSound("assets/audio/sfx/uiBlocked.wav");
    SetSoundVolume(this->uiBlocked, volSfx);
    this->soundBuy = LoadSound("assets/audio/sfx/kaching.wav");
    SetSoundVolume(this->soundBuy, volSfx);

    // Check for Items
    TraceLog(LOG_INFO, "Checking items");
    for (int i = 0; i < this->player->inventory.size(); i++)
    {
        switch (this->player->inventory[i]->type)
        {
            case itemPunchGun:
                this->hasPunchGun = true;
                this->punchGunPtr = this->player->inventory[i];
                break;
            case itemBottlecapGun:
                this->hasBottlecapGun = true;
                this->bottlecapGunPtr = this->player->inventory[i];
                break;
            case itemLaserGun:
                this->hasLaserGun = true;
                this->laserGunPtr = this->player->inventory[i];
                break;
        }
    }

    this->activeButton = 0;
    this->updateButtons();
}

void ShopDealer::CustomUpdate()
{
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        buttons[activeButton]->active = false;
        if (activeButton < buttons.size() - 1)
            activeButton++;
        else activeButton = 0;

        buttons[activeButton]->active = true;
        PlaySound(this->uiBlip);
    }

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        buttons[activeButton]->active = false;
        if (activeButton == 0)
            activeButton = (int)buttons.size() - 1;
        else activeButton--;

        buttons[activeButton]->active = true;
        PlaySound(this->uiBlip);
    }

    // For tests only, updates Buttons
    if (IsKeyPressed(KEY_O))
    {
        this->updateButtons();
    }



    if (IsKeyPressed(KEY_E))
    {
        if (this->buttons[this->activeButton]->blocked == false)
        {
            PlaySound(this->soundBuy);
            std::string directoryString;
            std::string memoryString;
            std::string directorySecondary;
            switch (this->activeButton) {
                case 0:
                    this->player->augmentationCount++;

                    // Set defense
                    switch (this->player->augmentationCount)
                    {
                        case 1:
                            this->player->defense = 2;
                            break;
                        case 2:
                            this->player->defense = 7;
                            break;
                        case 3:
                            this->player->defense = 12;
                            break;
                        case 4:
                            this->player->defense = 17;
                            break;
                        case 5:
                            this->player->defense = 23;
                            break;
                        case 6:
                            this->player->defense = 28;
                            break;
                        default:
                            this->player->defense = 0;
                    }
                    this->player->money = this->player->money - 90;

                    // Update out of combat spritesheets
                    directoryString = "assets/graphics/character/";
                    if (this->player->genderMale)
                    {
                        directoryString.append("dudeInOrange/");
                    }
                    else
                    {
                        directoryString.append("ladyInYellow/");
                    }
                    memoryString = directoryString;

                    directoryString.append("idle/aug");
                    directoryString.append(std::to_string(this->player->augmentationCount));
                    directoryString.append(".png");

                    player->spritesheetIdle = LoadTexture(directoryString.c_str());

                    directoryString = memoryString;

                    directoryString.append("walkcycle/aug");
                    directoryString.append(std::to_string(this->player->augmentationCount));
                    directoryString.append(".png");

                    player->spritesheet = LoadTexture(directoryString.c_str());

                    // Combat spritesheets
                    directoryString.clear();
                    memoryString.clear();

                    directoryString = "assets/graphics/combatAnimations/attack/";
                    directorySecondary = "assets/graphics/combatAnimations/reaction/";

                    if (player->genderMale == true)
                    {
                        directoryString.append("dudeInOrange/");
                        directorySecondary.append("dudeInOrange/");
                    }
                    else
                    {
                        directoryString.append("ladyInYellow/");
                        directorySecondary.append("ladyInYellow/");
                    }
                    directoryString.append("augmentation");
                    directorySecondary.append("augmentation");

                    directoryString.append(std::to_string(this->player->augmentationCount));
                    directorySecondary.append(std::to_string(this->player->augmentationCount));
                    directoryString.append("/");
                    directorySecondary.append("/");

                    // Attack
                    memoryString = directoryString;

                    directoryString.append("punch.png");
                    this->player->spritesheetAttackPunch.sheet = LoadTexture(directoryString.c_str());
                    directoryString = memoryString;
                    directoryString.append("punchGun.png");
                    this->player->spritesheetAttackPunchGun.sheet = LoadTexture(directoryString.c_str());
                    directoryString = memoryString;
                    directoryString.append("bottlecap.png");
                    this->player->spritesheetAttackBottlecap.sheet = LoadTexture(directoryString.c_str());
                    directoryString = memoryString;
                    directoryString.append("laser.png");
                    this->player->spritesheetAttackLaser.sheet = LoadTexture(directoryString.c_str());
                    directoryString = memoryString;
                    directoryString.append("bomb.png");
                    this->player->spritesheetAttackBomb.sheet = LoadTexture(directoryString.c_str());
                    directoryString = memoryString;
                    directoryString.append("frisbee.png");
                    this->player->spritesheetAttackFrisbee.sheet = LoadTexture(directoryString.c_str());

                    // Reaction
                    memoryString.clear(); // Just in case

                    memoryString = directorySecondary;

                    directorySecondary.append("punch.png");
                    this->player->spritesheetReactPunch.sheet = LoadTexture(directorySecondary.c_str());
                    directorySecondary = memoryString;
                    directorySecondary.append("tazer.png");
                    this->player->spritesheetReactTazer.sheet = LoadTexture(directorySecondary.c_str());

                    break;
                case 1:
                    TraceLog(LOG_INFO, "Upgrading Punch-Gun");
                    this->punchGunPtr->damage = 16;
                    this->player->money = this->player->money - 50;
                    this->punchGunPtr->upgraded = true;
                    break;
                case 2:
                    TraceLog(LOG_INFO, "Upgrading Bottle cap-Gun");
                    this->bottlecapGunPtr->damage = 20;
                    this->player->money = this->player->money - 50;
                    this->bottlecapGunPtr->upgraded = true;
                    break;
                case 3:
                    TraceLog(LOG_INFO, "Upgrading Laser-Gun");
                    this->laserGunPtr->damage = 24;
                    this->player->money = this->player->money - 50;
                    this->laserGunPtr->upgraded = true;
                    break;
            }
        }
        else
        {
            PlaySound(this->uiBlocked);
        }
        this->updateButtons();
    }
    if (IsKeyPressed(KEY_ESCAPE))
    {
        this->switchTo = GAME;
        this->switchScene = true;
        PlaySound(this->uiBlip2);
    }
}

void ShopDealer::CustomDraw()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.7));
    DrawTexture(this->panelTexture, this->panelPos.x, this->panelPos.y, WHITE);

    for (int i = 0; i < this->buttons.size(); i++)
    {
        buttons[i]->Draw();
    }

    //DrawTexture(this->bombTexture, panelPos.x + GetScreenWidth() * 0.01, panelPos.y + GetScreenHeight() * 0.01, WHITE);
    //DrawTexture(this->frisbeeTexture, panelPos.x + GetScreenWidth() * 0.01, panelPos.y + GetScreenHeight() * 0.1, WHITE);
    //DrawTexture(this->longdrinkTexture, panelPos.x + GetScreenWidth() * 0.01, panelPos.y + GetScreenHeight() * 0.05, WHITE);
}

void ShopDealer::updateButtons()
{
    TraceLog(LOG_INFO, "Updating buttons");
    this->buttons.clear();
    std::string workingString;
    float posX = GetScreenWidth() * 0.5; // Button posX

    workingString = "Augmentation ";
    switch (this->player->augmentationCount)
    {
        case 0:
            workingString.append("(Left arm)");
            break;
        case 1:
            workingString.append("(Right arm)");
            break;
        case 2:
            workingString.append("(Left leg)");
            break;
        case 3:
            workingString.append("(Right leg)");
            break;
        case 4:
            workingString.append("(Left eye)");
            break;
        case 5:
            workingString.append("(Right eye)");
            break;
        case 6:
            workingString.append("(MAXED)");
    }
    if (this->player->augmentationCount < 6)
    {
        workingString.append(" 90$");
    }
    this->buttons.push_back(std::make_shared<game::Button>(workingString.c_str(),
                                                           posX,
                                                           GetScreenHeight() * 0.3,
                                                           50, 1, YELLOW, WHITE));
    TraceLog(LOG_INFO, "Button 1 finished");

    // Upgrades
    workingString.clear(); // Just in case
    workingString = "Upgrade Punch-Gun";
    if (this->hasPunchGun == true)
    {
        if (this->punchGunPtr->upgraded == false)
        {
            TraceLog(LOG_INFO, "Condition met: PunchGun is not upgraded");
            workingString.append(" (50$)");
        }
        else
        {
            TraceLog(LOG_INFO, "Condition met: PunchGun is upgraded");
            workingString.append(" (MAXED)");
        }
    }
    TraceLog(LOG_INFO, "Pushing button 2");
    this->buttons.push_back(std::make_shared<game::Button>(workingString.c_str(),
                                                           posX,
                                                           GetScreenHeight() * 0.395,
                                                           50, 1, YELLOW, WHITE));
    TraceLog(LOG_INFO, "Button 2 finished");
    workingString.clear(); // Just in case
    workingString = "Upgrade Bottle cap-Gun";
    if (this->hasBottlecapGun == true)
    {
        if (this->bottlecapGunPtr->upgraded == false)
        {
            workingString.append(" (50$)");
        }
        else
        {
            workingString.append(" (MAXED)");
        }
    }
    this->buttons.push_back(std::make_shared<game::Button>(workingString.c_str(),
                                                           posX,
                                                           GetScreenHeight() * 0.485,
                                                           50, 1, YELLOW, WHITE));
    TraceLog(LOG_INFO, "Button 3 finished");
    workingString.clear(); // Just in case
    workingString = "Upgrade Laser-Gun";
    if (this->hasLaserGun == true)
    {
        TraceLog(LOG_INFO, "Condition met: Has Laser-Gun");
        if (this->laserGunPtr->upgraded == false)
        {
            TraceLog(LOG_INFO, "Condition met: Laser-Gun is not upgraded");
            workingString.append(" (50$)");
        }
        else
        {
            TraceLog(LOG_INFO, "Condition met: Laser-Gun is already upgraded");
            workingString.append(" (MAXED)");
        }
    }
    this->buttons.push_back(std::make_shared<game::Button>(workingString.c_str(),
                                                           posX,
                                                           GetScreenHeight() * 0.575,
                                                           50, 1, YELLOW, WHITE));
    TraceLog(LOG_INFO, "Button 4 finished");
    // Disable buttons
    TraceLog(LOG_INFO, "Disabling buttons");
    if (this->player->augmentationCount >= 6 || this->player->money < 90)
    {
        buttons[0]->blocked = true;
    }
    if (this->hasPunchGun == true)
    {
        if (this->punchGunPtr->upgraded == true || this->player->money < 50)
        {
            buttons[1]->blocked = true;
        }
    }
    else
    {
        this->buttons[1]->blocked = true;
    }
    if (this->hasBottlecapGun == true)
    {
        if (this->bottlecapGunPtr->upgraded == true || this->player->money < 50)
        {
            this->buttons[2]->blocked = true;
        }
    }
    else
    {
        this->buttons[2]->blocked = true;
    }
    if (this->hasLaserGun == true)
    {
        if (this->laserGunPtr->upgraded == true || this->player->money < 50)
        {
            this->buttons[3]->blocked = true;
        }
    }
    else
    {
        this->buttons[3]->blocked = true;
    }
    this->buttons[this->activeButton]->active = true;
    TraceLog(LOG_INFO, "Finished updating buttons");
}
