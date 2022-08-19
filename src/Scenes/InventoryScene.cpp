#include "InventoryScene.h"
#include "raylib.h"
#include "config.h"


InventoryScene::InventoryScene()
{
    std::vector<Slot> slots;
    std::vector<Vector2> slotPos ={Vector2 {10,11}, Vector2 {12,13}, Vector2{14,15}, Vector2 {16,17},
                                   Vector2 {18,19}, Vector2 {20,21}, Vector2{22,23}, Vector2 {23,24},
                                   Vector2 {25,26}, Vector2 {27,28}, Vector2{29,30}, Vector2 {31,32},
                                   Vector2 {10,11}, Vector2 {12,13}, Vector2{14,15}, Vector2 {16,17},
                                   Vector2 {10,11}, Vector2 {12,13}, Vector2{14,15}, Vector2 {16,17}};
}



void InventoryScene::CustomUpdate()
{
    // Check Changes

}

void InventoryScene::CustomDraw()
{
    //this->DrawInventory();
}
void InventoryScene::DrawInventory()
{
    /*Rectangle rectOut = {100, 100, Game::ScreenWidth-200, Game::ScreenHeight-200 };
    DrawRectangle(100, 100, Game::ScreenWidth-200, Game::ScreenHeight-200, LIGHTGRAY);
    DrawRectangleLinesEx(rectOut, 5,BLACK);
    */
    Texture2D inventoryImg = LoadTexture("../../assets/graphics/UI/Shop&Inventory/inventory.png");
    DrawTexture(inventoryImg,100,100, WHITE);
    DrawText("Inventory", Game::ScreenWidth/2-100,110, 30, RED);

    /*Rectangle rectIn = {120, 150, Game::ScreenWidth-240, Game::ScreenHeight-270 };
    DrawRectangle(rectIn.width/2, 150, rectIn.width/2, rectIn.height, RED);
    DrawRectangleLinesEx(rectIn, 5,BLACK);
     */
}

void AddItem()
{

}

void RemoveItem()
{

}