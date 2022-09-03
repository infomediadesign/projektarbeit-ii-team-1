//
// Created by 22max on 20.08.2022.
//

#ifndef RAYLIBSTARTER_SHOPDEALER_H
#define RAYLIBSTARTER_SHOPDEALER_H

#include "MenuScenes.h"
#include "Button.h"
#include "../Actors/Player.h"
#include "../Actors/Dealer.h"
#include "../Items/PunchGun.h"
#include "../Items/BottlecapGun.h"
#include "../Items/LaserGun.h"

class ShopDealer : public MenuScenes{
// Attributes
public:
    std::shared_ptr<Player> player;

    Texture2D panelTexture;
    Vector2 panelPos;

    std::vector<std::shared_ptr<game::Button>> buttons;
    int activeButton;
    //Image bombTexture;
    //Image frisbeeTexture;
    //Image longdrinkTexture;

    // Demo items
    //PunchGun punchGun({1,1});
    //BottlecapGun bottlecapGun({1,1});
    //LaserGun laserGun({1,1});


    bool hasPunchGun;
    std::shared_ptr<Item> punchGunPtr;
    bool hasBottlecapGun;
    std::shared_ptr<Item> bottlecapGunPtr;
    bool hasLaserGun;
    std::shared_ptr<Item> laserGunPtr;

    // SFX
    Sound uiBlip;
    Sound uiBlip2;
    Sound uiBlocked;

    // Methods
public:
    ShopDealer(std::shared_ptr<Player> player);

protected:
    void CustomUpdate() override;
    void CustomDraw() override;

    void updateButtons();
};


#endif //RAYLIBSTARTER_SHOPDEALER_H
