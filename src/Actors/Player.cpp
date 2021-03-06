//
// Created by Maximilian R�ck on 05.06.2022.
//

#include "Player.h"
#include <iostream>
#include <raylib.h>
#include <vector>


Player::Player()
{
    std::cout << "[DEBUG] This function should not be called (Player-Standardconstructor)" << std::endl;
}

Player::Player(int posX, int posY, Texture2D spritesheet_, Texture2D spritesheetIdle_)
{
    this->position.x = posX;
    this->position.y = posY;

    this->prevPosition = this->position;

    this->spritesheetIdle = spritesheetIdle_;
    this->spritesheet = spritesheet_;
    this->frameRec.width = this->spritesheet.width / 4;
    this->frameRec.height = this->spritesheet.height / 4;
    /*
    this->spritesheetWalk = spritesheetWalk;
    this->frameRec.width = this->spritesheetWalk.width / 4;
    this->frameRec.height = this->spritesheetWalk.height / 4;
    */
    this->collisionBox.x = posX;
    this->collisionBox.y = posY;
    this->collisionBox.height = frameRec.height;
    this->collisionBox.width = frameRec.width;
}


void Player::Update() {
    this->framesCounter++;
    this->move();

    if(this->dialogueManager.dialoguePlaying == false)
    {
        this->moveLockAbsolute = false;
        this->interactionDisabled = false;
    }

    this->dialogueManager.Update();
    //this->interact();
}

void Player::Draw()
{
    if (this->playIdle == false)
    {
        DrawTextureRec(this->spritesheet, this->frameRec, this->position, WHITE);
    }
    else
        DrawTextureRec(this->spritesheetIdle, this->frameRec, this->position, WHITE);
    // Debug-Boxes
    DrawRectangleLines(this->collisionBox.x, this->collisionBox.y, this->collisionBox.width, this->collisionBox.height,
                       GREEN);
    DrawRectangleLines(this->interactionBox.x, this->interactionBox.y, this->interactionBox.width, this->interactionBox.height,
                       BLUE);

    this->dialogueManager.drawDialogue();
}

void Player::move()
{
    this->playIdle = true;
    if (this->moveLockAbsolute == false)
    {
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        {
            this->playIdle = false;
            if (this->facing != up)
                this->turn(up);
            if (this->moveLockUp == false)
            {
                this->prevPosition = this->position;
                this->position.y = position.y - this->speed;
            }
            //Adjusting interaction box
            this->interactionBox.width = this->frameRec.width;
            this->interactionBox.height = this->frameRec.height;
            this->interactionBox.x = this->position.x;
            this->interactionBox.y = this->position.y - this->frameRec.height;
        }
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        {
            this->playIdle = false;
            if (this->facing != down)
                this->turn(down);

            if (this->moveLockDown == false)
            {
                this->prevPosition = this->position;
                this->position.y = position.y + this->speed;
            }
            //Adjusting interaction box
            this->interactionBox.width = this->frameRec.width;
            this->interactionBox.height = this->frameRec.height;
            this->interactionBox.x = this->position.x;
            this->interactionBox.y = this->position.y + this->frameRec.height;
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        {
            this->playIdle = false;
            if (this->facing != left)
                this->turn(left);
            if (this->moveLockLeft == false)
            {
                this->prevPosition = this->position;
                this->position.x = position.x - this->speed;
            }
            //Adjusting interaction box
            this->interactionBox.width = this->frameRec.width;
            this->interactionBox.height = this->frameRec.height;
            this->interactionBox.x = this->position.x - frameRec.width;
            this->interactionBox.y = this->position.y;
        }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        {
            this->playIdle = false;
            if (this->facing != right)
                this->turn(right);
            if (this->moveLockRight == false)
            {
                this->prevPosition = this->position;
                this->position.x = position.x + this->speed;
            }
            //Adjusting interaction box    
            this->interactionBox.width = this->frameRec.width;
            this->interactionBox.height = this->frameRec.height;
            this->interactionBox.x = this->position.x + frameRec.width;
            this->interactionBox.y = this->position.y;
        }
        this->collisionBox.x = this->position.x;
        this->collisionBox.y = this->position.y;
    }
    this->animate();
}
// Interaction for props
void Player::interact(std::vector<std::shared_ptr<Prop>> actors_) {

    if (IsKeyPressed(KEY_E) && interactionDisabled == false)
    {
        for (int i = 0; i < actors_.size(); i++)
        {

            if (CheckCollisionRecs(actors_[i]->collisionBox, this->interactionBox))
            {
                std::cout << "[DEBUG] Interaction successful!" << std::endl;
                std::cout << "[DEBUG] Starting dialogue with " << actors_[i]->getName() << std::endl;
                this->moveLockAbsolute = true;
                this->interactionDisabled = true;
                this->dialogueManager.startDialogue(this->getName(), actors_[i]->getDialogue(), this->spritesheet);
            }
        }
    }
}
// Interaction for actors
void Player::interact(std::vector<std::shared_ptr<Actor>> actors_) {

    if (IsKeyPressed(KEY_E) && interactionDisabled == false)
    {
        for (int i = 0; i < actors_.size(); i++)
        {

            if (CheckCollisionRecs(actors_[i]->collisionBox, this->interactionBox))
            {
                std::cout << "[DEBUG] Interaction successful!" << std::endl;
                std::cout << "[DEBUG] Starting dialogue with " << actors_[i]->getName() << std::endl;
                switch (this->facing)
                {
                    case down: actors_[i]->turn(up);
                    break;
                    case up: actors_[i]->turn(down);
                    break;
                    case left: actors_[i]->turn(right);
                    break;
                    case right: actors_[i]->turn(left);
                    std::cout << "[DEBUG] Error while checking player facing during interaction" << std::endl;
                }


                this->moveLockAbsolute = true;
                this->interactionDisabled = true;
                this->dialogueManager.startDialogue(actors_[i]->getName(), actors_[i]->getDialogue(), actors_[i]->spritesheet);
            }
        }
    }
}

void Player::checkActorCollision(std::vector<std::shared_ptr<Prop>> actors)
{
    for (const auto& actor : actors)
    {
        if (CheckCollisionRecs(this->collisionBox, actor->collisionBox))
        {

            Rectangle leftEdge;
            leftEdge.x = actor->collisionBox.x;
            leftEdge.width = 1;
            leftEdge.y = actor->collisionBox.y + 1;
            leftEdge.height = actor->collisionBox.height - 2;

            Rectangle rightEdge;
            rightEdge.x = actor->collisionBox.x + actor->collisionBox.width - 1;
            rightEdge.width = 1;
            rightEdge.y = actor->collisionBox.y + 1;
            rightEdge.height = actor->collisionBox.height - 2;

            Rectangle topEdge;
            topEdge.x = actor->collisionBox.x + 1;
            topEdge.width = actor->collisionBox.width - 2;
            topEdge.y = actor->collisionBox.y;
            topEdge.height = 1;

            Rectangle bottomEdge;
            bottomEdge.x = actor->collisionBox.x + 1;
            bottomEdge.width = actor->collisionBox.width - 2;
            bottomEdge.y = actor->collisionBox.y + actor->collisionBox.height - 1;
            bottomEdge.height = 1;

            this->position = this->prevPosition;

            // Left edge collision
            if (CheckCollisionRecs(this->collisionBox, leftEdge))
            {
                this->moveLockUp = false;
                this->moveLockRight = true;
            }
            // Right edge collision
            if (CheckCollisionRecs(this->collisionBox, rightEdge))
            {
                this->moveLockRight = false;
                this->moveLockLeft = true;
            }
            // Top edge collision
            if (CheckCollisionRecs(this->collisionBox, topEdge))
            {
                this->moveLockLeft = false;
                this->moveLockDown = true;
            }
            // Bottom edge collision
            if (CheckCollisionRecs(this->collisionBox, bottomEdge))
            {
                this->moveLockDown = false;
                this->moveLockUp = true;
            }
        }
        else
        {
            this->moveLockDown = false;
            this->moveLockUp = false;
            this->moveLockLeft = false;
            this->moveLockRight = false;
        }
    }
}

void Player::checkActorCollision(std::vector<std::shared_ptr<Actor>> actors)
{
    for (const auto& actor : actors)
    {
        if (CheckCollisionRecs(this->collisionBox, actor->collisionBox))
        {

            Rectangle leftEdge;
            leftEdge.x = actor->collisionBox.x;
            leftEdge.width = 1;
            leftEdge.y = actor->collisionBox.y + 1;
            leftEdge.height = actor->collisionBox.height - 2;

            Rectangle rightEdge;
            rightEdge.x = actor->collisionBox.x + actor->collisionBox.width - 1;
            rightEdge.width = 1;
            rightEdge.y = actor->collisionBox.y + 1;
            rightEdge.height = actor->collisionBox.height - 2;

            Rectangle topEdge;
            topEdge.x = actor->collisionBox.x + 1;
            topEdge.width = actor->collisionBox.width - 2;
            topEdge.y = actor->collisionBox.y;
            topEdge.height = 1;

            Rectangle bottomEdge;
            bottomEdge.x = actor->collisionBox.x + 1;
            bottomEdge.width = actor->collisionBox.width - 2;
            bottomEdge.y = actor->collisionBox.y + actor->collisionBox.height - 1;
            bottomEdge.height = 1;

            this->position = this->prevPosition;

            // Left edge collision
            if (CheckCollisionRecs(this->collisionBox, leftEdge))
            {
                this->moveLockUp = false;
                this->moveLockRight = true;
            }
            // Right edge collision
            if (CheckCollisionRecs(this->collisionBox, rightEdge))
            {
                this->moveLockRight = false;
                this->moveLockLeft = true;
            }
            // Top edge collision
            if (CheckCollisionRecs(this->collisionBox, topEdge))
            {
                this->moveLockLeft = false;
                this->moveLockDown = true;
            }
            // Bottom edge collision
            if (CheckCollisionRecs(this->collisionBox, bottomEdge))
            {
                this->moveLockDown = false;
                this->moveLockUp = true;
            }
        }
        else
        {
            this->moveLockDown = false;
            this->moveLockUp = false;
            this->moveLockLeft = false;
            this->moveLockRight = false;
        }
    }
}

