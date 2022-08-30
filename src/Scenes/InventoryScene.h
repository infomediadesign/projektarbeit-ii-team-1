//
// Created by Munchkin on 24.05.2022.
//

#pragma once
#include "MenuScenes.h"
#include "Structs.h"
#include "vector"
#include "memory"
#include "../Actors/enums.h"
#include "../Actors/player.h"
#include "../Items/item.h"
#include "../Items/Bomb.h"
#include "../Items/BottlecapAmmo.h"
#include "../Items/BottlecapGun.h"
#include "../Items/Frisbee.h"
#include "../Items/LaserGun.h"
#include "../Items/Longdrink.h"
#include "../Items/PunchGun.h"

class InventoryScene : public MenuScenes {
private:
    ;
public:
    const int slotMaxCount = 20;
    Font font1;
    //std::vector<Item> items;
    std::shared_ptr<Player> player;

    //= {Item01(type itemPunchGun, name "test02", price 100, damage 0.2, uses 1),
      //                          Item02(type itemBomb, name "test02", price 50, damage 0.2, uses 2);



    //};

    // Slot positions
    std::vector<Vector2> slotPos ={Vector2 {20,20}, Vector2 {12,13}, Vector2{14,15}, Vector2 {16,17},
                                   Vector2 {18,19}, Vector2 {20,21}, Vector2{22,23}, Vector2 {23,24},
                                   Vector2 {25,26}, Vector2 {27,28}, Vector2{29,30}, Vector2 {31,32},
                                   Vector2 {10,11}, Vector2 {12,13}, Vector2{14,15}, Vector2 {16,17},
                                   Vector2 {10,11}, Vector2 {12,13}, Vector2{14,15}, Vector2 {16,17}
    };

    InventoryScene(std::shared_ptr<Player> player);
    void CustomUpdate() override;
    void CustomDraw() override;
    void DrawInventory();
    void AddItem(Item newItem);
    void RemoveItem(Item delItem);
    void LoadInventory();
    void SaveInventory();

protected:
    ;
};


