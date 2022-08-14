//
// Created by Munchkin on 04.08.2022.
//

#pragma once

#include "raylib.h"

#ifndef RAYLIBSTARTER_ITEM_H
#define RAYLIBSTARTER_ITEM_H

#include "../Actors/enums.h"

//namespace game{

    //why is this greyed out???
    class Item {

    public:
        ItemType type;

//alles andere zum item
//den kindklassen (einzelne items) werden die attribute zugewiesen
        char itemName;
        int itemTexture; //not int here, but what else??
        int price; //as attribute
        int upgradePrice;
        int damage; //even tho with heal items? //--> substract from health points
        int heal; //add to health points
//what else???
        int uses; //(how) or (times)??? //--> as attribute

        Item() = delete;
        //Item(Texture2D, );
        ~Item();

        bool showInLevel;

        Texture2D getTexture();
    };
//}

#endif //RAYLIBSTARTER_ITEM_H
