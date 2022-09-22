//
// Created by Maximilian R�ck on 05.06.2022.
//

#include "Enemy.h"

#define COLLISION_OFFSET 0.4


void Enemy::Update()
{
    this->framesCounter++;
    animate();
}

void Enemy::Draw()
{
    DrawTextureRec(this->spritesheet, this->frameRec, this->position, WHITE);

    // Debug boxes
    //DrawRectangleLines(this->collisionBox.x, this->collisionBox.y, this->collisionBox.width, this->collisionBox.height,
      //                 RED);
    //DrawCircleLines(this->position.x + this->frameRec.width / 2, this->position.y + this->frameRec.height / 2, this->aggroRadius, RED);
}
