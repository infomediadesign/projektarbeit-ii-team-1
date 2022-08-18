//
// Created by Munchkin on 24.05.2022.
//

#ifndef RAYLIBSTARTER_INVENTORYSCENE_H
#define RAYLIBSTARTER_INVENTORYSCENE_H

#include "MenuScenes.h"
#include "Structs.h"
#include "vector"

class InventoryScene : MenuScenes {
private:
    ;
public:
    const int slotCount = 20;

    InventoryScene();
    void CustomUpdate() override;
    void CustomDraw() override;
    void DrawInventory();
    void AddItem();
    void RemoveItem();
    void LoadInventory();
    void SaveInventory();

protected:
    ;
};


#endif //RAYLIBSTARTER_INVENTORYSCENE_H
