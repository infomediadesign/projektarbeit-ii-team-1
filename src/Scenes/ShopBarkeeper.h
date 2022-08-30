//
// Created by 22max on 19.08.2022.
//

#pragma once

#include "MenuScenes.h"
#include "../Actors/Player.h"
#include "../Actors/Barkeeper.h"
#include "../Items/Bomb.h"
#include "../Items/Frisbee.h"
#include "../Items/Longdrink.h"
#include "Button.h"
#include <memory>
#include <vector>

class ShopBarkeeper : public MenuScenes {

    // Attributes
public:
    std::shared_ptr<Player> player;
    std::shared_ptr<Barkeeper> barkeeper;

    Texture2D panelTexture;
    Vector2 panelPos;

    std::vector<std::shared_ptr<game::Button>> buttons;
    int activeButton;
    //Image bombTexture;
    //Image frisbeeTexture;
    //Image longdrinkTexture;

    // Demo Items
    Bomb bomb;
    Frisbee frisbee;
    Longdrink longdrink;

    // Methods
public:
    ShopBarkeeper(std::shared_ptr<Player> player, std::shared_ptr<Barkeeper> barkeeper);

protected:
    void CustomUpdate() override;
    void CustomDraw() override;

    void updateButtons();
};
