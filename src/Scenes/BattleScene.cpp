//
// Created by Munchkin on 24.05.2022.
//

#include "BattleScene.h"

BattleScene::BattleScene(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy)
{
    this->controlsLocked = false;

    this->player = player;
    this->enemy = enemy;

    this->player->turn(up);
    this->enemy->turn(down);

    this->background = LoadTexture("assets/graphics/ui/combat/background.png");

    Vector2 camTarget = {0, 0};
    this->camera.target = camTarget;
    this->camera.offset = camTarget;
    this->camera.zoom = 2;

    this->player->position.x = GetScreenWidth() * 0.125;
    this->player->position.y = GetScreenHeight() * 0.225;

    this->enemy->position.x = GetScreenWidth() * 0.2917;
    this->enemy->position.y = GetScreenHeight() * 0.0724;

    this->player->currentFrame = 0;
    this->enemy->currentFrame = 0;

    this->framesCounter = 0;
}

void BattleScene::Update()
{
animateIdle();

}

void BattleScene::Draw()
{
    BeginMode2D(this->camera);

    // Everything to be drawn goes here! (Between BeginMode2D() and EndMode2D() )

    DrawTexture(background, 0, 0, WHITE);

    this->player->Draw();
    this->enemy->Draw();

    EndMode2D();
}

void BattleScene::initializeBattle()
{

}

void BattleScene::animateIdle() {
    this->framesCounter++;

    this->player->playIdle = true;

    if (this->framesCounter >= (60 / this->player->frameSpeed)) {
        this->framesCounter = 0;
        this->player->currentFrame++;
        this->enemy->currentFrame++;

        if (player->currentFrame > 3) {
            this->player->currentFrame = 0;
            this->enemy->currentFrame = 0;
        }

        this->player->frameRec.x = (float) this->player->currentFrame * (float) this->player->spritesheet.width / 4;
        this->enemy->frameRec.x = (float) this->enemy->currentFrame * (float) this->enemy->spritesheet.width / 4;
    }
}