//
// Created by Munchkin on 24.05.2022.
//

#include "BattleScene.h"
#include <iostream>

BattleScene::BattleScene(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy)
{
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

    this->playerTurn = true;
    this->attackSelected = false;
    this->enemyNextAttack = punchEnemy;

    this->updateHpBars();
}

void BattleScene::Update() {
    this->framesCounter++;

    if (this->playerTurn == true && this->animationPlaying == false)
    {
        // Here goes a method for selecting attacks (Hardcoded for now)

        if (IsKeyPressed(KEY_E))
        {
            this->attackType = punchPlayer;
            this->attackSelected = true;
        }

        // Here goes a method for executing a selected attack
        if (this->attackSelected == true)
        {
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
    DrawText(this->player->getName().c_str(), playerHpPos.x + GetScreenWidth() * 0.022, playerHpPos.y + GetScreenHeight() * 0.077, 20, BLACK);

    // Enemy HP
    Vector2 enemyHpPos;
    enemyHpPos.x = GetScreenWidth() * 0.38;
    enemyHpPos.y = GetScreenHeight() - GetScreenHeight() * 1.043;
    DrawTexture(this->enemyHpBar, enemyHpPos.x, enemyHpPos.y, WHITE);
    DrawText(this->enemy->getName().c_str(), enemyHpPos.x + GetScreenWidth() * 0.022, enemyHpPos.y + GetScreenHeight() * 0.077, 20, BLACK);

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

    switch (this->attackType)
    {
        case punchPlayer:
            this->enemy->currentHP = this->enemy->currentHP - 6;
            this->playerTurn = false;
            this->startAnimation();
        case punchGun:
            // If there are uses left:
            //if ()
            // Has to account for upgraded damage
            //this->enemy->currentHP = this->enemy->currentHP - 6;
            this->playerTurn = false;
            this->startAnimation();
    }

    this->attackSelected = false;

    this->updateHpBars();
}

void BattleScene::enemyAttack()
{
    this->attackSource = sourceEnemy;
    this->attackType = this->enemyNextAttack;

    switch (this->enemyNextAttack)
    {
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
