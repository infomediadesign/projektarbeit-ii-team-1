#include "InventoryScene.h"
#include "raylib.h"
#include "config.h"
#include "../Items/PunchGun.h"

InventoryScene::InventoryScene(std::shared_ptr<Player> player)
{
    PunchGun test({1, 1});
    //this->items.push_back(test);
    this->player = player;
    font1 = LoadFont("../../assets/graphics/ui/Habbo.ttf");
    items= {};

}

void InventoryScene::CustomUpdate()
{
    // Check Change

    // TEST
    if(IsKeyPressed(KEY_ESCAPE))
    {
        switchTo = GAME;
        switchScene = true;
    }
    // TEST

}

void InventoryScene::CustomDraw()
{
    this->DrawInventory();
}
void InventoryScene::DrawInventory()
{
    // Draw basics, Background, Text,
    Color lightGray = {210,210,210,10};
    Rectangle recBackground = {0,0 ,Game::ScreenWidth, Game::ScreenHeight};
    DrawRectangleRec(recBackground, LIGHTGRAY);

    // Header text
    const std::string inventoryHeaderTxt = "Inventory";
    const Vector2 inventoryTxtSize =  MeasureTextEx(font1, inventoryHeaderTxt.c_str(), 2, 60);
    DrawTextEx( font1, inventoryHeaderTxt.c_str(), {Game::ScreenWidth/2 - (inventoryTxtSize.x/4),110}, 60, 2, BLACK);

    // Close Inventory text
    const std::string escapeInventoryTxt = "Escape to close Inventory";
    //const Vector2 escapeTxtSize =  MeasureTextEx(font1, escapeInventoryTxt.c_str(), 2, 30);
    DrawTextEx( font1, escapeInventoryTxt.c_str(), {20,20}, 30, 1, BLACK);

    //Inventory Image
    Texture2D inventoryImg = LoadTexture("../../assets/graphics/UI/Shop&Inventory/InventoryNew.png");
    Vector2 posInventoryImg = {float (Game::ScreenWidth/2 - (inventoryImg.width/2)),float(Game::ScreenHeight/2 - (inventoryImg.height/2))};

    DrawTexture(inventoryImg,posInventoryImg.x,posInventoryImg.y, WHITE);

    // TEST
    /*Texture2D testimg = LoadTexture("../../assets/graphics/items/weapons/Frisbee.png");
    Texture2D testimg2 = LoadTexture("../../assets/graphics/items/weapons/Frisbee.png");
    DrawTextureEx(testimg, {posInventoryImg.x+20,posInventoryImg.y+20}, 0, 1, WHITE);
    DrawTextureEx(testimg2, {posInventoryImg.x+80,posInventoryImg.y+20}, 0, 1, WHITE);*/
    // TEST

    for (int i = 0; i <player->inventory.size() ; ++i) {

        DrawTextureEx(player->inventory[i]->texture, {posInventoryImg.x+20,posInventoryImg.y+20}, 0, 1, WHITE);
        DrawTextEx( font1, std::to_string(player->inventory[i]->uses).c_str(), {20,20}, 30, 1, BLACK);
    }




    // Draw item imgs
    for (int i = 1; i <=player->inventory.size() ; ++i) {
        DrawTextureEx(player->inventory[i]->texture, {posInventoryImg.x+20,posInventoryImg.y+20}, 0, 1, WHITE);

    }
}

void InventoryScene::AddItem(Item newItem)
{
    //if (items.size() <= slotMaxCount)
    //{
    //    items.push_back(newItem);
    //}else{
        // Tell User that the inventory is fulls

    //}
}

void InventoryScene::RemoveItem(Item delItem)
{
    // Check whether the item is in the list.
    // Remove item
    //


}


