#include "InventoryScene.h"
#include "raylib.h"
#include "config.h"
#include "../Items/PunchGun.h"
#include "iostream"

extern float volSfx;

InventoryScene::InventoryScene(std::shared_ptr<Player> player)
{
    PunchGun test({1, 1});
    //this->items.push_back(test);
    this->player = player;
    font1 = LoadFont("../../assets/graphics/ui/Habbo.ttf");

    //Sound
    this->uiBlip = LoadSound("assets/audio/sfx/uiBlip.wav");
    this->uiBlip2 = LoadSound("assets/audio/sfx/uiBlip2.wav");

    SetSoundVolume(uiBlip, volSfx);
    SetSoundVolume(uiBlip2, volSfx);

    items= {};
    this->drawLevelBackground = true;
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
    Color purple = {255,0,255,255};
    Rectangle recBackground = {0,0 ,Game::ScreenWidth, Game::ScreenHeight};
    DrawRectangleRec(recBackground, Fade(purple,0.8));

    ColorAlpha(LIGHTGRAY,  0.7);
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
    Rectangle recInventoryBackground ={posInventoryImg.x, posInventoryImg.y, float(inventoryImg.width), float(inventoryImg.height)};

    DrawRectangleRec(recInventoryBackground, Color {220, 22, 220, 255});
    DrawTexture(inventoryImg,posInventoryImg.x,posInventoryImg.y, WHITE);

    // Draw all items from the inventory
    int size = items.size();
    for (int i = 0; i < itemCount.size(); i++) {
        DrawTextureEx(player->inventory[i]->texture, {posInventoryImg.x + slotPos[i].x,posInventoryImg.y + slotPos[i].y}, 0, 1, WHITE);
        DrawTextEx( font1, std::to_string(itemCount[i]).c_str(), {posInventoryImg.x + slotPos[i].x + 40,posInventoryImg.y + slotPos[i].y + 40}, 26, 1, VIOLET);
        TraceLog(LOG_INFO,"Inventory-Items gezeichnet: ");
        std::cout <<"was soll das "<< items[i].name << std::endl;
    }

}

// Add item to the inventory
void InventoryScene::AddItem(Item newItem)
{
    int itemPresent = 0;
    int slotPosPresentItem = 0;
    for (int i = 0; i <=items.size() ; i++) {
        if (items[i].type == newItem.type)
        {
            itemPresent++;
            slotPosPresentItem = i;
        }
    }

    if (itemPresent >0)
    {
        itemCount[slotPosPresentItem]++;
    }else if (itemPresent ==0)
    {
        items.push_back(newItem);
        itemCount.push_back(1);
    }

}

// Remove item from inventory
void InventoryScene::RemoveItem(Item delItem)
{
    int itemPresent = 0;
    int slotPosPresentItem = 0;

    // Check if item is present
    for (int i = 0; i <=items.size() ; ++i) {
        if (items[i].type = delItem.type)
        {
            itemPresent ++;
            slotPosPresentItem = i;
        }
    }

    if (itemPresent >0)
    {
        items.erase(items.begin()+slotPosPresentItem);
        if (slotPosPresentItem >0)
        {
            itemCount[slotPosPresentItem]--;
        }else{
            itemCount[slotPosPresentItem] = 0;
        }

    }
}


