//
// Created by Munchkin on 04.08.2022.
//

#pragma once

#include "raylib.h"

#ifndef RAYLIBSTARTER_ITEM_H
#define RAYLIBSTARTER_ITEM_H

#include "../Actors/enums.h"
#include <string>

    class Item {

    public:
        ItemType type;

        std::string name;
        Texture2D texture;

        Vector2 levelPosition; // Position of the Item inside a level
        int price;

        bool upgraded;

        // The damage stat will be ignored for heal items and bombs
        float damage; //--> substract from health points

        int uses; // determines how many times an item / a weapon can be used in a single fight

        bool showInLevel;
        Rectangle collisionBox;


public:
   // virtual void Draw();
    };

#endif //RAYLIBSTARTER_ITEM_H
