//
// Created by Munchkin on 24.05.2022.
//

#include "BattleScene.h"
#include <iostream>
#include "../Items/Bomb.h"
#include "../Items/Frisbee.h"
#include "../Items/Longdrink.h"

BattleScene::BattleScene(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy)
{
    this->endBattle = false;
    this->gameOver = false;

    this->controlsLocked = false;
    this->animationPlaying = false;
    this->attackSource = sourcePlayer;
    this->attackType = punchPlayer;

    this->playPlayerIdle = true;
    this->playEnemyIdle = true;

    this->player = player;
    this->enemy = enemy;
    
    this->player->turn(up);
    this->enemy->turn(down);
    this->player->moveLockAbsolute = true;

    this->background = LoadTexture("assets/graphics/ui/combat/background.png");

    Vector2 camTarget = {0, 0};
    this->camera.target = camTarget;
    this->camera.offset = camTarget;
    this->camera.zoom = 2;
    this->camera.rotation = 0;

    this->player->position.x = GetScreenWidth() * 0.125;
    this->player->position.y = GetScreenHeight() * 0.225;

    this->enemy->position.x = GetScreenWidth() * 0.2917;
    this->enemy->position.y = GetScreenHeight() * 0.0724;

    this->player->currentFrame = 0;
    this->enemy->currentFrame = 0;

    this->framesCounter = 0;
    this->frameSpeed = 8;

    this->timerFramesWaited = 0;

    this->frameRecPlayer.x = 0;
    this->frameRecPlayer.y = 0;
    this->frameRecEnemy.x = 0;
    this->frameRecEnemy.y = 0;

    this->enemyStunnedFor = 0;
    this->playerTurn = true;
    this->attackSelected = false;
    this->enemyNextAttack = punchEnemy;

    this->font = LoadFont("assets/graphics/ui/Habbo.ttf");

    // Setup for items
    this->hasBottlecapGun = false;
    this->hasPunchGun = false;
    this->hasLaserGun = false;
    this->punchGunUses = 0;
    this->laserGunUses = 0;
    this->bottlecapGunDmg = 0;
    this->laserGunDmg = 0;
    this->punchGunDmg = 0;
    this->frisbeeUses = 0;
    this->bombUses = 0;


    for (int i = 0; i < this->player->inventory.size(); i++)
    {
        switch (this->player->inventory[i]->type)
        {
            case itemPunchGun:
                this->hasPunchGun = true;
                this->punchGunUses = this->player->inventory[i]->uses;
                this->punchGunDmg = this->player->inventory[i]->damage;
                break;
            case itemLaserGun:
                this->hasLaserGun = true;
                this->laserGunUses = this->player->inventory[i]->uses;
                this->bottlecapGunDmg = this->player->inventory[i]->damage;
                break;
            case itemBottlecapGun:
                this->hasBottlecapGun = true;
                this->laserGunDmg = this->player->inventory[i]->damage;
                break;
            case itemBomb:
                this->bombUses = this->player->inventory[i]->uses;
                break;
            case itemFrisbee:
                this->frisbeeUses = this->player->inventory[i]->uses;
        }
    }

    this->updateHpBars();
    this->endBattle = false;

    this->state = Main;
    this->initMainMenu();
}

void BattleScene::Update() {
    this->framesCounter++;

    if (this->player->currentHP <= 0)
    {
        this->gameOver = true;
    }

    if (this->playerTurn == true && this->animationPlaying == false)
    {
        this->menuNavigation();

        if (this->attackSelected == true) {
            this->playerAttack();
        }
    }
    if (this->playerTurn == false && this->animationPlaying == false)
    {
        this->enemyAttack();
    }


    if (animationPlaying == true)
    {
        this->playAnimation();
    }
    animateIdle();
}

void BattleScene::Draw()
{
    BeginMode2D(this->camera);

    // Everything to be drawn goes here! (Between BeginMode2D() and EndMode2D() )

    DrawTexture(background, 0, 0, WHITE);

    if (this->playPlayerIdle == true)
    {
        this->player->Draw();
    }
    if (this->playEnemyIdle == true)
    {
        this->enemy->Draw();
    }
    if (this->playPlayerIdle == false)
    {
        // Draw player animation
        Vector2 playerPosition;

        playerPosition.x = GetScreenWidth() * 0.0833;
        playerPosition.y = GetScreenHeight() * 0.0768;

        DrawTextureRec(this->playerAnimation.sheet, this->frameRecPlayer, playerPosition, WHITE);
    }
    if (this->playEnemyIdle == false)
    {
        // Draw enemy animation
        Vector2 enemyPosition;
        if (this->attackType == bomb || this->attackType == laser)
        {
            enemyPosition.x = GetScreenWidth() * 0.25;
            enemyPosition.y = GetScreenHeight() - GetScreenHeight() * 1.076;
        }
        else
        {
            enemyPosition.x = GetScreenWidth() * 0.2917;
            enemyPosition.y = GetScreenHeight() * 0.072;
        }
            DrawTextureRec(this->enemyAnimation.sheet, this->frameRecEnemy, enemyPosition, WHITE);
    }

    // Draw HP bars

    // Player HP
    Vector2 playerHpPos;
    playerHpPos.x = GetScreenWidth() * 0.03;
    playerHpPos.y = GetScreenHeight() * 0.2;
    DrawTexture(this->playerHpBar, playerHpPos.x, playerHpPos.y, WHITE);
    DrawTextEx(this->font, this->player->getName().c_str(),
               {static_cast<float>(playerHpPos.x + GetScreenWidth() * 0.048 - MeasureTextEx(this->font, this->player->getName().c_str(), 20, 1).x/2),
                static_cast<float>(playerHpPos.y + GetScreenHeight() * 0.077)}, 20, 1, BLACK);

    // Enemy HP
    Vector2 enemyHpPos;
    enemyHpPos.x = GetScreenWidth() * 0.389;
    enemyHpPos.y = GetScreenHeight() - GetScreenHeight() * 1.043;
    DrawTexture(this->enemyHpBar, enemyHpPos.x, enemyHpPos.y, WHITE);
    DrawTextEx(this->font, this->enemy->getName().c_str(),
               {static_cast<float>(enemyHpPos.x + GetScreenWidth() * 0.048 - MeasureTextEx(this->font, this->enemy->getName().c_str(), 20, 1).x/2),
                static_cast<float>(enemyHpPos.y + GetScreenHeight() * 0.077)}, 20, 1, BLACK);


    // Draw other UI elements

    for (auto& button : buttons)
    {
        button->Draw();
    }

    EndMode2D();
}

void BattleScene::animateIdle() {


    if (this->playPlayerIdle == true)
    {
        this->player->playIdle = true;

        this->player->framesCounter++;

        if (this->player->framesCounter >= (60 / this->player->frameSpeed))
        {
            this->player->framesCounter = 0;
            this->player->currentFrame++;

            if (this->player->currentFrame > 3)
            {
                this->player->currentFrame = 0;
            }

            this->player->frameRec.x = (float) this->player->currentFrame * (float) this->player->spritesheet.width / 4;
        }

        if (this->playEnemyIdle == true)
        {
            this->enemy->framesCounter++;
            if (this->enemy->framesCounter >= (60 / this->enemy->frameSpeed))
            {
                this->enemy->framesCounter = 0;
                this->enemy->currentFrame++;

                if (this->enemy->currentFrame > 3)
                {
                    this->enemy->currentFrame = 0;
                }

                this->enemy->frameRec.x = (float) this->enemy->currentFrame * (float) this->enemy->spritesheet.width / 4;
                this->enemy->framesCounter++;
            }
        }

    }
}

void BattleScene::playAnimation() {
    // Plays animation
    if (animationPlaying == true) {

        this->frameRecPlayer.width = this->playerAnimation.sheet.width / this->playerAnimation.spriteCount;
        this->frameRecPlayer.height = this->playerAnimation.sheet.height;

        this->frameRecEnemy.width = this->enemyAnimation.sheet.width / this->enemyAnimation.spriteCount;
        this->frameRecEnemy.height = this->enemyAnimation.sheet.height;

        // When the player is attacking
        if (this->attackSource == sourcePlayer) {
            if (this->framesCounter >= (60 / this->frameSpeed)) {
                this->framesCounter = 0;
                this->currentFramePlayer++;

                // Plays animation only when delay matches the frames waited
                if (this->timerFramesWaited > this->playerAnimation.delay) {
                    std::cout << "[DEBUG] End idle and start animation (enemy)" << std::endl;
                    this->playEnemyIdle = false;
                    this->currentFrameEnemy++;
                } else {
                    std::cout << "[DEBUG] Wait for animation and idle (enemy)" << std::endl;
                    this->playEnemyIdle = true;
                    this->timerFramesWaited++;
                    this->currentFrameEnemy = -1;
                }
            }
        }

        // When the enemy is attacking
        if (this->attackSource == sourceEnemy) {
            this->playEnemyIdle = false;
            if (this->framesCounter >= (60 / this->frameSpeed)) {
                this->framesCounter = 0;
                this->currentFrameEnemy++;

                // Plays animation only when delay matches the frames waited
                if (this->timerFramesWaited > this->enemyAnimation.delay) {
                    std::cout << "[DEBUG] End idle and start animation (player)" << std::endl;
                    this->playPlayerIdle = false;
                    this->currentFramePlayer++;
                } else {
                    std::cout << "[DEBUG] Wait for animation and idle (player)" << std::endl;
                    this->playPlayerIdle = true;
                    this->timerFramesWaited++;
                    this->currentFramePlayer = -1;
                }
            }
        }
        // Makes up for the fact that frisbee sheets have a sprite worth of empty space
        int spriteCountAdjusted = this->playerAnimation.spriteCount;
        if (this->attackType == frisbee)
        {
            spriteCountAdjusted--;
        }
        if (this->currentFramePlayer >= spriteCountAdjusted) {
            this->playPlayerIdle = true;
        }
        if (this->currentFrameEnemy >= this->enemyAnimation.spriteCount) {
            this->playEnemyIdle = true;
        }
        // Reset everything after animation has finished playing
        if (this->currentFramePlayer > this->playerAnimation.spriteCount &&
            this->currentFrameEnemy > this->enemyAnimation.spriteCount) {
            this->player->currentFrame = 0;
            this->currentFramePlayer = 0;
            this->enemy->currentFrame = 0;
            this->currentFrameEnemy = 0;
            this->animationPlaying = false;
            this->timerFramesWaited = 0;
        }
        // Advance frameRecs
        this->frameRecPlayer.x = (float) this->currentFramePlayer * (float) this->playerAnimation.sheet.width /
                                 this->playerAnimation.spriteCount;
        this->frameRecEnemy.x = (float) this->currentFrameEnemy * (float) this->enemyAnimation.sheet.width /
                                this->enemyAnimation.spriteCount;
    }
}




void BattleScene::startAnimation()
{
    // This part decides which animation is going to play based on the attackType-attribute
    switch (this->attackType)
    {
        case punchPlayer:
            this->playerAnimation = this->player->spritesheetAttackPunch;
            this->enemyAnimation = this->enemy->spritesheetReactPunch;
            break;
        case punchGun:
            this->playerAnimation = this->player->spritesheetAttackPunchGun;
            this->enemyAnimation = this->enemy->spritesheetReactPunch;
            break;
        case bottlecap:
            this->playerAnimation = this->player->spritesheetAttackBottlecap;
            this->enemyAnimation = this->enemy->spritesheetReactBottlecap;
            break;
        case laser:
            this->playerAnimation = this->player->spritesheetAttackLaser;
            this->enemyAnimation = this->enemy->spritesheetReactLaser;
            break;
        case bomb:
            this->playerAnimation = this->player->spritesheetAttackBomb;
            this->enemyAnimation = this->enemy->spritesheetReactBomb;
            break;
        case frisbee:
            this->playerAnimation = this->player->spritesheetAttackFrisbee;
            this->enemyAnimation = this->enemy->spritesheetReactFrisbee;
            break;
        case punchEnemy:
            this->playerAnimation = this->player->spritesheetReactPunch;
            this->enemyAnimation = this->enemy->spritesheetAttackPunch;
            break;
        case necklace:
            this->playerAnimation = this->player->spritesheetReactPunch;
            this->enemyAnimation = this->enemy->spritesheetAttackNecklace;
            break;
        case tazer:
            this->playerAnimation = this->player->spritesheetReactTazer;
            this->enemyAnimation = this->enemy->spritesheetAttackTazer;
            break;
        default:
            std::cout << "[DEBUG] Error while selecting combat animations. Punch animations are being selected" << std::endl;
            this->playerAnimation = this->player->spritesheetAttackPunch;
            this->enemyAnimation = this->enemy->spritesheetReactPunch;
    }

    if (this->attackSource == sourcePlayer) {
        this->animationPlaying = true;
        this->playPlayerIdle = false;
        this->framesCounter = 0;
        this->currentFrameEnemy = 0;
        this->currentFramePlayer = 0;
    }
    if (this->attackSource == sourceEnemy) {
        this->animationPlaying = true;
        this->playPlayerIdle = false;
        this->framesCounter = 0;
        this->currentFrameEnemy = 0;
        this->currentFramePlayer = 0;
    }
}

void BattleScene::playerAttack()
{
    // First: Items (Using items doesn't end the turn)
    this->attackSource = sourcePlayer;
    bool stopSearch = false; // Used for stopping item search when healing / attacking with the bottle cap gun

    switch (this->attackType)
    {
        case punchPlayer:
            this->enemy->currentHP = this->enemy->currentHP - 6;
            this->playerTurn = false;
            this->enemyStunnedFor--;
            this->startAnimation();
            break;
        case punchGun:
            this->enemy->currentHP = this->enemy->currentHP - this->punchGunDmg;
            this->punchGunUses--;
            this->playerTurn = false;
            this->enemyStunnedFor--;
            this->startAnimation();
            break;
        case laser:
            this->enemy->currentHP = this->enemy->currentHP - this->laserGunDmg;
            this->laserGunUses--;
            this->playerTurn = false;
            this->enemyStunnedFor--;
            this->startAnimation();
            break;
        case bottlecap:
            this->enemy->currentHP = this->enemy->currentHP - this->bottlecapGunDmg;
            // Remove ammo
            for (int i = 0; (i < this->player->inventory.size()) && stopSearch == false; i++) {
                if (this->player->inventory[i]->type == itemBottlecapAmmo)
                {
                    this->player->inventory.erase(this->player->inventory.begin() + i);
                    stopSearch = true;
                }
            }
            this->playerTurn = false;
            this->enemyStunnedFor--;
            this->startAnimation();
            break;
        case frisbee:
            this->enemy->currentHP = this->enemy->currentHP - 20;
            this->frisbeeUses--;
            this->startAnimation();
            break;
        case bomb:
            this->enemyStunnedFor = 2;
            this->bombUses--;
            this->startAnimation();
            break;
        case heal:
            this->player->currentHP = this->player->currentHP + 20;
            if (this->player->currentHP > this->player->maxHP)
            {
                this->player->currentHP = this->player->maxHP;
            }
            // Remove item
            for (int i = 0; (i < this->player->inventory.size()) && stopSearch == false; i++) {
                if (this->player->inventory[i]->type == itemHeal) {
                    this->player->inventory.erase(this->player->inventory.begin() + i);
                    stopSearch = true;
                }
            }
            break;
    }

    this->attackSelected = false;

    this->updateHpBars();
}

void BattleScene::enemyAttack()
{
    if (this->enemyStunnedFor <= 0)
    {
        this->attackSource = sourceEnemy;
        this->attackType = this->enemyNextAttack;

        switch (this->enemyNextAttack) {
            case punchEnemy:
                this->player->currentHP = this->player->currentHP - this->enemy->damagePunch;
                this->enemyNextAttack = necklace;
                break;
            case necklace:
                this->player->currentHP = this->player->currentHP - this->enemy->damageNecklace;
                this->enemyNextAttack = tazer;
                break;
            case tazer:
                this->player->currentHP = this->player->currentHP - this->enemy->damageTazer;
                this->enemyNextAttack = punchEnemy;
                break;
        }
        this->startAnimation();
    }
    this->playerTurn = true;
    this->updateHpBars();
}

void BattleScene::updateHpBars() {
    // Player HP bar

    float playerPercentage = this->player->currentHP / this->player->maxHP;
    // Adjusts percentage: We have 50 different HP bar textures, so the percentage can't exceed 50
    playerPercentage = playerPercentage * 50;

    if (this->player->currentHP <= 0) {
        this->playerHpBar = LoadTexture("assets/graphics/ui/combat/hp0.png");
    }
    else
    {
        std::string directoryString = "assets/graphics/ui/combat/hp";
        std::string workingString = std::to_string((int) playerPercentage);

        for (int i = 0; i < workingString.size(); i++) {
            directoryString.push_back(workingString[i]);
        }
        directoryString.push_back('.');
        directoryString.push_back('p');
        directoryString.push_back('n');
        directoryString.push_back('g');

        this->playerHpBar = LoadTexture(directoryString.c_str());
    }

    // Enemy HP bar

    float enemyPercentage = this->enemy->currentHP / this->enemy->maxHP;
    // Adjusts percentage: We have 50 different HP bar textures, so the percentage can't exceed 50
    enemyPercentage = enemyPercentage * 50;

    if (this->enemy->currentHP <= 0) {
        this->enemyHpBar = LoadTexture("assets/graphics/ui/combat/hp0.png");
    }
    else
    {
        std::string directoryString = "assets/graphics/ui/combat/hp";
        std::string workingString = std::to_string((int) enemyPercentage);

        for (int i = 0; i < workingString.size(); i++) {
            directoryString.push_back(workingString[i]);
        }
        directoryString.push_back('.');
        directoryString.push_back('p');
        directoryString.push_back('n');
        directoryString.push_back('g');

        this->enemyHpBar = LoadTexture(directoryString.c_str());
    }
}

void BattleScene::menuNavigation() {
    std::shared_ptr<game::Button> workingPtr;
    std::string workingString;
    int bottlecapAmmo = 0;
    int healItems = 0;
    bool hasFrisbee = false;
    bool hasBomb = false;
    bool buttonUnlocked;
    if (this->state == Main) {
       if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
            buttons[activeButton]->active = false;
            if (activeButton < buttons.size() - 1)
                activeButton++;
            else activeButton = 0;

            buttons[activeButton]->active = true;
        }

        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            buttons[activeButton]->active = false;
            if (activeButton == 0)
                activeButton = buttons.size() - 1;
            else activeButton--;

            buttons[activeButton]->active = true;
        }
        if (IsKeyPressed(KEY_E)) {
            switch (activeButton) // 0 = Attack | 1 = Items | 2 = Flee
            {
                case 0:
                    this->state = Attack;
                    this->buttons.clear();
                    // Load buttons for Attack
                    this->activeButton = 0; // 0 = Upper left (Punch), 1 = Upper right (PunchGun), 2 = Lower left (BottlecapGun), 3 = lower right (LaserGun)

                    // Punch
                    workingPtr = std::make_shared<game::Button>("Punch",
                                                                GetScreenWidth() * 0.1,
                                                                GetScreenHeight() * 0.395,
                                                                50, 1, YELLOW, WHITE);
                    workingPtr->active = true;
                    this->buttons.push_back(workingPtr);

                    // PunchGun
                    workingPtr = std::make_shared<game::Button>("Punch Gun",
                                                                GetScreenWidth() * 0.35,
                                                                GetScreenHeight() * 0.395,
                                                                50, 1, YELLOW, WHITE);
                    this->buttons.push_back(workingPtr);

                    // BottlecapGun
                    workingPtr = std::make_shared<game::Button>("Bottlecap Gun",
                                                                GetScreenWidth() * 0.1,
                                                                GetScreenHeight() * 0.44,
                                                                50, 1, YELLOW, WHITE);
                    this->buttons.push_back(workingPtr);

                    // LaserGun
                    workingPtr = std::make_shared<game::Button>("Laser Gun",
                                                                GetScreenWidth() * 0.35,
                                                                GetScreenHeight() * 0.44,
                                                                 50, 1, YELLOW, WHITE);

                    this->buttons.push_back(workingPtr);

                    // Adjust button text for uses left
                    this->buttons[1]->Text.push_back(' ');
                    this->buttons[1]->Text.push_back('x');
                    workingString = std::to_string((int) this->punchGunUses);
                    for (int i = 0; i < workingString.size(); i++) {
                        this->buttons[1]->Text.push_back(workingString[i]);
                    }
                    // Check bottlecap gun ammo
                    bottlecapAmmo = 0;
                    for (int i = 0; i < this->player->inventory.size(); i++) {
                        if (this->player->inventory[i]->type == itemBottlecapAmmo) {
                            bottlecapAmmo++;
                        }
                    }
                    this->buttons[2]->Text.push_back(' ');
                    this->buttons[2]->Text.push_back('x');
                    workingString = std::to_string((int) bottlecapAmmo);
                    for (int i = 0; i < workingString.size(); i++) {
                        this->buttons[2]->Text.push_back(workingString[i]);
                    }
                    this->buttons[3]->Text.push_back(' ');
                    this->buttons[3]->Text.push_back('x');
                    workingString = std::to_string((int) this->laserGunUses);
                    for (int i = 0; i < workingString.size(); i++) {
                        this->buttons[3]->Text.push_back(workingString[i]);
                    }
                    break;
                case 1:
                    this->state = Items;
                    this->buttons.clear();
                    this->activeButton = 0;

                    workingPtr = std::make_shared<game::Button>("Frisbee",
                                                                GetScreenWidth() * 0.075,
                                                                GetScreenHeight() * 0.415,
                                                                50, 1, YELLOW, WHITE);
                    workingPtr->active = true;
                    this->buttons.push_back(workingPtr);
                    workingPtr = std::make_shared<game::Button>("Discobomb",
                                                                GetScreenWidth() * 0.24,
                                                                GetScreenHeight() * 0.415,
                                                                50, 1, YELLOW, WHITE);
                    this->buttons.push_back(workingPtr);
                    workingPtr = std::make_shared<game::Button>("Longdrink",
                                                                GetScreenWidth() * 0.42,
                                                                GetScreenHeight() * 0.415,
                                                                50, 1, YELLOW, WHITE);
                    this->buttons.push_back(workingPtr);

                    // Adjust button text for uses left / item count

                    // Just to be sure...
                    hasBomb = false;
                    hasFrisbee = false;
                    healItems = 0;

                    for (int i = 0; i < this->player->inventory.size(); i++)
                    {
                        switch (this->player->inventory[i]->type)
                        {
                            case itemBomb:
                                hasBomb = true;
                                break;
                            case itemFrisbee:
                                hasFrisbee = true;
                                break;
                            case itemHeal:
                                healItems++;
                        }
                    }

                    this->buttons[0]->Text.push_back(' ');
                    this->buttons[0]->Text.push_back('x');
                    if (hasFrisbee == true && this->frisbeeUses > 0) {
                        workingString = std::to_string((int) this->frisbeeUses);
                        for (int i = 0; i < workingString.size(); i++) {
                            this->buttons[0]->Text.push_back(workingString[i]);
                        }
                    }
                    else
                    {
                        this->buttons[0]->Text.push_back('0');
                    }

                    this->buttons[1]->Text.push_back(' ');
                    this->buttons[1]->Text.push_back('x');
                    if (hasBomb == true && bombUses > 0) {
                        workingString = std::to_string((int) this->bombUses);
                        for (int i = 0; i < workingString.size(); i++) {
                            this->buttons[1]->Text.push_back(workingString[i]);
                        }
                    }
                    else
                    {
                        this->buttons[1]->Text.push_back('0');
                    }

                    this->buttons[2]->Text.push_back(' ');
                    this->buttons[2]->Text.push_back('x');
                    workingString = std::to_string((int) healItems);
                    for (int i = 0; i < workingString.size(); i++) {
                        this->buttons[2]->Text.push_back(workingString[i]);
                    }
                    break;
                case 2:
                    this->endBattle = true;
                    break;
            }
        }
    }
        else if (this->state == Attack) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            this->state = Main;
            this->initMainMenu();
        }

        // Enable / Disable buttons
        if (this->hasPunchGun == false || this->punchGunUses <= 0) {
            this->buttons[1]->blocked = true;
        }
        // Check bottlecap gun ammo
        bottlecapAmmo = 0;
        for (int i = 0; i < this->player->inventory.size(); i++) {
            if (this->player->inventory[i]->type == bottlecapAmmo) {
                bottlecapAmmo++;
            }
        }
        if (this->hasBottlecapGun == false || bottlecapAmmo <= 0) {
            this->buttons[2]->blocked = true;
        }
        if (this->hasLaserGun == false || this->laserGunUses <= 0) {
            this->buttons[3]->blocked = true;
        }
        // Menu navigation
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
            buttons[activeButton]->active = false;
            if (this->activeButton != 1 && this->activeButton != 3)
                activeButton++;
            else activeButton--;

            buttons[activeButton]->active = true;
        }
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            this->buttons[this->activeButton]->active = false;
            if (this->activeButton != 0 && this->activeButton != 2)
                this->activeButton--;
            else activeButton++;

            buttons[activeButton]->active = true;
        }
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            this->buttons[this->activeButton]->active = false;
            if (this->activeButton != 2 && this->activeButton != 3)
                this->activeButton = this->activeButton + 2;
            else this->activeButton = this->activeButton - 2;

            buttons[activeButton]->active = true;
        }
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
            this->buttons[this->activeButton]->active = false;
            if (this->activeButton != 0 && this->activeButton != 1)
                this->activeButton = this->activeButton - 2;
            else this->activeButton = this->activeButton + 2;

            buttons[activeButton]->active = true;
        }
        if (IsKeyPressed(KEY_E)) {
            if (this->buttons[activeButton]->blocked == false) {
                switch (this->activeButton) {
                    case 0:
                        this->attackType = punchPlayer;
                        break;
                    case 1:
                        this->attackType = punchGun;
                        break;
                    case 2:
                        this->attackType = bottlecap;
                        break;
                    case 3:
                        this->attackType = laser;
                        break;
                    default:
                        this->attackType = punchPlayer;
                        TraceLog(LOG_INFO, "Error while selecting attacks. Default: playerPunch");
                }
                this->attackSelected = true;
                this->state = Main;
                this->initMainMenu();
            }
            else
            {
                // Play "blocked" sound
            }
        }


    }
        else if (this->state == Items)
        {
            if (IsKeyPressed(KEY_ESCAPE))
            {
                this->state = Main;
                this->initMainMenu();
            }

        // Get items from inventory
        int countBomb = 0;
        int countFrisbee = 0;
        int countHeal = 0;
        for (int i = 0; i < this->player->inventory.size(); i++)
        {
            switch (this->player->inventory[i]->type)
            {
                case itemBomb:
                    countBomb++;
                    break;
                case itemFrisbee:
                    countFrisbee++;
                    break;
                case itemHeal:
                    countHeal++;
            }
        }
        if (countBomb <= 0 || this->bombUses <= 0)
        {
            this->buttons[1]->blocked = true;
        }
        if (countFrisbee <= 0 || this->frisbeeUses <= 0)
        {
            this->buttons[0]->blocked = true;
        }
        if (countHeal <= 0)
        {
            this->buttons[2]->blocked = true;
        }
            if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
                buttons[activeButton]->active = false;
                if (activeButton < buttons.size() - 1)
                    activeButton++;
                else activeButton = 0;

                buttons[activeButton]->active = true;
            }

            if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
                buttons[activeButton]->active = false;
                if (activeButton == 0)
                    activeButton = buttons.size() - 1;
                else activeButton--;

                buttons[activeButton]->active = true;
            }

            if (IsKeyPressed(KEY_E)) {
                if (this->buttons[activeButton]->blocked == false) {
                    switch (this->activeButton) {
                        case 0:
                            this->attackType = frisbee;
                            break;
                        case 1:
                            this->attackType = bomb;
                            break;
                        case 2:
                            this->attackType = heal;
                            break;
                        default:
                            this->attackType = punchPlayer;
                            TraceLog(LOG_INFO, "Error while selecting items. Default: playerPunch");
                    }
                    this->attackSelected = true;
                    this->state = Main;
                    this->initMainMenu();
                }
                else
                {
                    // Play "blocked" sound
                }
            }
    }
}


void BattleScene::initMainMenu()
{
   this->activeButton = 0;
   this->buttons.clear();
    std::shared_ptr<game::Button> workingPtr;
    workingPtr = std::make_shared<game::Button>("Attack",
                                                GetScreenWidth() * 0.1,
                                                GetScreenHeight() * 0.415,
                                                50, 1, YELLOW, WHITE);
    workingPtr->active = true;
    this->buttons.push_back(workingPtr);
    workingPtr = std::make_shared<game::Button>("Items",
                                                GetScreenWidth() * 0.25,
                                                GetScreenHeight() * 0.415,
                                                50, 1, YELLOW, WHITE);
    this->buttons.push_back(workingPtr);
    workingPtr = std::make_shared<game::Button>("Flee",
                                                GetScreenWidth() * 0.35,
                                                GetScreenHeight() * 0.415,
                                                50, 1, YELLOW, WHITE);
    this->buttons.push_back(workingPtr);
}
