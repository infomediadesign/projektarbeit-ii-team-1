//
// Created by Munchkin on 24.05.2022.
//

#include "BattleScene.h"

BattleScene::BattleScene(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy)
{
    this->controlsLocked = false;
    this->animationPlaying = false;

    this->playPlayerIdle = true;
    this->playEnemyIdle = true;

    this->player = player;
    this->enemy = enemy;

    this->player->turn(up);
    this->enemy->turn(down);

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
    this->frameSpeed = 10;

    this->frameRecPlayer.x = 0;
    this->frameRecPlayer.y = 0;
    this->frameRecEnemy.x = 0;
    this->frameRecEnemy.y = 0;
}

void BattleScene::Update()
{
    this->framesCounter++;
    playAnimation();
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
        enemyPosition.x = GetScreenWidth() * 0.2917;
        enemyPosition.y = GetScreenHeight() * 0.072;
        DrawTextureRec(this->enemyAnimation.sheet, this->frameRecEnemy, enemyPosition, WHITE);
    }

    
    EndMode2D();
}

void BattleScene::initializeBattle()
{

}

void BattleScene::animateIdle() {


    if (this->playPlayerIdle == true)
    {
        this->player->playIdle = true;

        if (this->framesCounter >= (60 / this->player->frameSpeed))
        {
            this->framesCounter = 0;
            this->player->currentFrame++;

            if (this->player->currentFrame > 3)
            {
                this->player->currentFrame = 0;
            }

            this->player->frameRec.x = (float) this->player->currentFrame * (float) this->player->spritesheet.width / 4;
        }

        if (this->playEnemyIdle == true)
        {
            if (this->framesCounter >= (60 / this->enemy->frameSpeed))
            {
                this->framesCounter = 0;
                this->enemy->currentFrame++;

                if (this->player->currentFrame > 3)
                {
                    this->enemy->currentFrame = 0;
                }

                this->enemy->frameRec.x = (float) this->enemy->currentFrame * (float) this->enemy->spritesheet.width / 4;
            }
        }

    }
}

void BattleScene::playAnimation()
{
    if (animationPlaying == false && IsKeyPressed(KEY_E))
    {
        this->animationPlaying = true;
        this->playPlayerIdle = false;
        this->playEnemyIdle = false;
        this->framesCounter = 0;
        this->currentFrameEnemy = 0;
        this->currentFramePlayer = 0;
    }
    else if (animationPlaying == true)
    {
        // This part decides which animation is going to play (it is hardcoded to animate a punch for test purposes)

        this->playerAnimation = this->player->spritesheetAttackBottlecap;
        this->enemyAnimation = this->enemy->spritesheetReactBottlecap;

        this->frameRecPlayer.width = this->playerAnimation.sheet.width / this->playerAnimation.spriteCount;
        this->frameRecPlayer.height = this->playerAnimation.sheet.height;


        this->frameRecEnemy.width = this->enemyAnimation.sheet.width / this->enemyAnimation.spriteCount;
        this->frameRecEnemy.height = this->enemyAnimation.sheet.height;

        //this->framesCounter++;

        if (this->framesCounter >= (60 / this->frameSpeed))
        {
            this->framesCounter = 0;
            this->currentFramePlayer++;
            this->currentFrameEnemy++;

            if (this->currentFramePlayer > this->playerAnimation.spriteCount)
            {
                this->playPlayerIdle = true;
            }
            if (this->currentFrameEnemy > this->enemyAnimation.spriteCount)
            {
                this->playEnemyIdle = true;
            }
            if (this->currentFramePlayer > this->playerAnimation.spriteCount && this->currentFrameEnemy > this->enemyAnimation.spriteCount)
            {
                this->player->currentFrame = 0;
                this->currentFramePlayer = 0;
                this->enemy->currentFrame = 0;
                this->currentFrameEnemy = 0;
                this->animationPlaying = false;
            }

            this->frameRecPlayer.x = (float) this->currentFramePlayer * (float) this->playerAnimation.sheet.width / this->playerAnimation.spriteCount;
            this->frameRecEnemy.x = (float) this->currentFrameEnemy * (float) this->enemyAnimation.sheet.width / this->enemyAnimation.spriteCount;
        }
    }
}
