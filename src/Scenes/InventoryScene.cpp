#include "InventoryScene.h"
#include "raylib.h"
#include "config.h"


InventoryScene::InventoryScene()
{

}

void InventoryScene::CustomUpdate()
{
    // Check Changes

}

void InventoryScene::CustomDraw()
{
    this->DrawInventory();
}
void InventoryScene::DrawInventory()
{
    // Draw basics, Background, Text,
    ClearBackground(GRAY);
    /*Rectangle rectOut = {100, 100, Game::ScreenWidth-200, Game::ScreenHeight-200 };
    DrawRectangle(100, 100, Game::ScreenWidth-200, Game::ScreenHeight-200, LIGHTGRAY);
    DrawRectangleLinesEx(rectOut, 5,BLACK);
    */
    Texture2D inventoryImg = LoadTexture("../../assets/graphics/UI/Shop&Inventory/InventoryNew.png");
    DrawTexture(inventoryImg,100,100, WHITE);
    DrawText("Inventory", Game::ScreenWidth/2-100,110, 30, RED);

    /*Rectangle rectIn = {120, 150, Game::ScreenWidth-240, Game::ScreenHeight-270 };
    DrawRectangle(rectIn.width/2, 150, rectIn.width/2, rectIn.height, RED);
    DrawRectangleLinesEx(rectIn, 5,BLACK);
     */

    // Draw item imgs
    for (int i = 0; i <=items.size() ; ++i) {
        DrawTextureEx(items[i].texture, slotPos[i].x, slotPos[i].y, 0, 50%);
        // Draw count of "uses"
    }
}

void InventoryScene::AddItem(Item newItem)
{
    if (items.size() <= slotMaxCount)
    {
        items.push_back(newItem);
    }else{
        // Tell User that the inventory is fulls

    }
}

void InventoryScene::RemoveItem(Item delItem)
{
    // Check whether the item is in the list.
    // Remove item
    //


}


