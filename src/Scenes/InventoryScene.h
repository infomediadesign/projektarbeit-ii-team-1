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
    Font font1;
    // Items in the inventory
    std::vector<Item> items = {PunchGun({0.0}), PunchGun({0.0})};
    // item count
    std::vector< unsigned int> itemCount = {1, 2};
    std::shared_ptr<Player> player;




    // Slot positions
    std::vector<Vector2> slotPos ={Vector2 {20,20}, Vector2 {86,20}, Vector2 {152,20}, Vector2 {218,20}, Vector2 {284,20}, Vector2 {350,21}, Vector2{416,23},
                                   Vector2 {20,86}, Vector2 {86,86}, Vector2 {152,68}, Vector2 {218,86}, Vector2 {284,86}, Vector2 {350,86}, Vector2 {416,86},
                                   Vector2 {20,152}, Vector2 {86,152}, Vector2 {152,152}, Vector2 {218,152}, Vector2 {284,152}, Vector2 {350,152}, Vector2 {416,152},
                                   Vector2 {20,218}, Vector2 {86,218}, Vector2 {152,218}, Vector2 {218,218}, Vector2 {284,218}, Vector2 {350,218}, Vector2 {416,218},
                                   Vector2 {20,284}, Vector2 {86,284}, Vector2 {152,284}, Vector2 {218,284}, Vector2 {284,284}, Vector2 {350,284}, Vector2 {416,284},
                                   Vector2 {20,350}, Vector2 {86,350}, Vector2 {152,350}, Vector2 {218,350}, Vector2 {284,350}, Vector2 {350,350}, Vector2 {416,350},
                                   Vector2 {20,416}, Vector2 {86,416}, Vector2 {152,416}, Vector2 {218,416}, Vector2 {284,416}, Vector2 {350,416}, Vector2 {416,416}
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


