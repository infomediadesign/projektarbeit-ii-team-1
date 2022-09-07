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

Player::Player(int posX, int posY, bool genderMale)
{
    this->position.x = posX;
    this->position.y = posY;

    this->prevPosition = this->position;
    this->savedPos = this->position;
    this->savedPosTimer = 0;

    this->augmentationCount = 0;

    this->name = "Dt. Carver";

    this->genderMale = genderMale;
    if (this->genderMale == true)
    {
        this->spritesheetIdle = LoadTexture("assets/graphics/character/dudeInOrange/idle/withoutAugmentation.png");
        this->spritesheet = LoadTexture("assets/graphics/character/dudeInOrange/walkcycle/withoutAugmentation.png");

        this->spritesheetAttackPunch.sheet = LoadTexture("assets/graphics/combatAnimations/attack/dudeInOrange/withoutAugmentation/punch.png");
        this->spritesheetAttackPunch.spriteCount = 7;
        this->spritesheetAttackPunch.delay = 2;
        this->spritesheetAttackPunchGun.sheet = LoadTexture("assets/graphics/combatAnimations/attack/dudeInOrange/withoutAugmentation/punchGun.png");
        this->spritesheetAttackPunchGun.spriteCount = 8;
        this->spritesheetAttackPunchGun.delay = 2;
        this->spritesheetAttackBottlecap.sheet = LoadTexture("assets/graphics/combatAnimations/attack/dudeInOrange/withoutAugmentation/bottlecap.png");
        this->spritesheetAttackBottlecap.spriteCount = 9;
        this->spritesheetAttackBottlecap.delay = 5;
        this->spritesheetAttackLaser.sheet = LoadTexture("assets/graphics/combatAnimations/attack/dudeInOrange/withoutAugmentation/laser.png");
        this->spritesheetAttackLaser.spriteCount = 9;
        this->spritesheetAttackLaser.delay = 4;
        this->spritesheetAttackBomb.sheet = LoadTexture("assets/graphics/combatAnimations/attack/dudeInOrange/withoutAugmentation/bomb.png");
        this->spritesheetAttackBomb.spriteCount = 8;
        this->spritesheetAttackBomb.delay = 5;
        this->spritesheetAttackFrisbee.sheet = LoadTexture("assets/graphics/combatAnimations/attack/dudeInOrange/withoutAugmentation/frisbee.png");
        this->spritesheetAttackFrisbee.spriteCount = 6;
        this->spritesheetAttackFrisbee.delay = 3;
        this->spritesheetReactPunch.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/dudeInOrange/withoutAugmentation/punch.png");
        this->spritesheetReactPunch.spriteCount = 4;
        this->spritesheetReactTazer.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/dudeInOrange/withoutAugmentation/tazer.png");
        this->spritesheetReactTazer.spriteCount = 2;
    }
    else
    {
        this->spritesheetIdle = LoadTexture("assets/graphics/character/ladyInYellow/idle/withoutAugmentation.png");
        this->spritesheet = LoadTexture("assets/graphics/character/ladyInYellow/walkcycle/withoutAugmentation.png");

        this->spritesheetAttackPunch.sheet = LoadTexture("assets/graphics/combatAnimations/attack/ladyInYellow/withoutAugmentation/punch.png");
        this->spritesheetAttackPunch.spriteCount = 7; // Placeholder!!
        this->spritesheetAttackPunchGun.sheet = LoadTexture("assets/graphics/combatAnimations/attack/ladyInYellow/withoutAugmentation/punchGun.png");
        this->spritesheetAttackPunchGun.spriteCount = 8;
        this->spritesheetAttackBottlecap.sheet = LoadTexture("assets/graphics/combatAnimations/attack/ladyInYellow/withoutAugmentation/bottlecap.png");
        this->spritesheetAttackBottlecap.spriteCount = 9;
        this->spritesheetAttackLaser.sheet = LoadTexture("assets/graphics/combatAnimations/attack/ladyInYellow/withoutAugmentation/laser.png");
        this->spritesheetAttackLaser.spriteCount = 9;
        this->spritesheetAttackBomb.sheet = LoadTexture("assets/graphics/combatAnimations/attack/ladyInYellow/withoutAugmentation/bomb.png");
        this->spritesheetAttackBomb.spriteCount = 8;
        this->spritesheetAttackFrisbee.sheet = LoadTexture("assets/graphics/combatAnimations/attack/ladyInYellow/withoutAugmentation/frisbee.png");
        this->spritesheetAttackFrisbee.spriteCount = 6;
        this->spritesheetReactPunch.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/ladyInYellow/withoutAugmentation/punch.png");
        this->spritesheetReactPunch.spriteCount = 4;
        this->spritesheetReactTazer.sheet = LoadTexture("assets/graphics/combatAnimations/reaction/ladyInYellow/withoutAugmentation/tazer.png");
        this->spritesheetReactTazer.spriteCount = 2;
    }

    this->frameRec.width = this->spritesheet.width / 4;
    this->frameRec.height = this->spritesheet.height / 4;

    this->collisionOffset = 0.4;
    this->collisionBox.x = posX + frameRec.width * (this->collisionOffset / 2);
    this->collisionBox.y = posY;
    this->collisionBox.height = frameRec.height;
    this->collisionBox.width = frameRec.width - frameRec.width * this->collisionOffset;

    this->maxHP = 50;
    this->currentHP = this->maxHP;
    this->defense = 0;
    this->money = 0;

    this->startCombat = false;
    this->openShopBarkeeper = false;
    this->openShopDealer = false;
}


void Player::Update()
{
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
        this->prevPosition = this->position;

        // If movement keys are pressed
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) ||
            IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        {
            this->savedPosTimer++;
            if (this->savedPosTimer == 60)
            {
                this->savedPos = this->prevPosition;
            }
        }

        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        {
            this->playIdle = false;
            if (this->facing != up)
                this->turn(up);
            if (this->moveLockUp == false)
            {
                //this->prevPosition = this->position;
                this->position.y = position.y - this->speed;
            }
            //Adjusting interaction box
            this->interactionBox.width = this->frameRec.width / 4;
            this->interactionBox.height = this->frameRec.height / 2;
            this->interactionBox.x = (this->position.x + this->frameRec.width / 2) - this->interactionBox.width / 2;
            this->interactionBox.y = this->position.y - this->frameRec.height / 2;
        }
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        {
            this->playIdle = false;
            if (this->facing != down)
                this->turn(down);

            if (this->moveLockDown == false)
            {
                //this->prevPosition = this->position;
                this->position.y = position.y + this->speed;
            }
            //Adjusting interaction box
            this->interactionBox.width = this->frameRec.width / 4;
            this->interactionBox.height = this->frameRec.height / 2;
            this->interactionBox.x = (this->position.x + this->frameRec.width / 2) - this->interactionBox.width / 2;
            this->interactionBox.y = this->position.y + this->frameRec.height;
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        {
            this->playIdle = false;
            if (this->facing != left)
                this->turn(left);
            if (this->moveLockLeft == false)
            {
                //this->prevPosition = this->position;
                this->position.x = position.x - this->speed;
            }
            //Adjusting interaction box
            this->interactionBox.width = this->frameRec.width / 2;
            this->interactionBox.height = this->frameRec.height / 4;
            this->interactionBox.x = this->position.x - frameRec.width / 2 + (frameRec.width * (this->collisionOffset / 2));
            this->interactionBox.y = this->position.y + this->frameRec.height / 2 - this->interactionBox.height / 2;
        }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        {
            this->playIdle = false;
            if (this->facing != right)
                this->turn(right);
            if (this->moveLockRight == false)
            {
                //this->prevPosition = this->position;
                this->position.x = position.x + this->speed;
            }
            //Adjusting interaction box    
            this->interactionBox.width = this->frameRec.width / 2;
            this->interactionBox.height = this->frameRec.height / 4;
            this->interactionBox.x = this->position.x + frameRec.width - (frameRec.width * (this->collisionOffset / 2));
            this->interactionBox.y = this->position.y + this->frameRec.height / 2 - this->interactionBox.height / 2;
        }
        this->collisionBox.x = this->position.x + this->frameRec.width * 0.2;
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
                TraceLog(LOG_INFO, "Interaction successful!");
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
                TraceLog(LOG_INFO, "Interaction successful!");
                switch (this->facing)
                {
                    case down: actors_[i]->turn(up);
                    break;
                    case up: actors_[i]->turn(down);
                    break;
                    case left: actors_[i]->turn(right);
                    break;
                    case right: actors_[i]->turn(left);
                }


                this->moveLockAbsolute = true;
                this->interactionDisabled = true;
                this->dialogueManager.startDialogue(actors_[i]->getName(), actors_[i]->getDialogue(), actors_[i]->spritesheet);
            }
        }
    }
}
// Interaction for barkeepers
void Player::interact(std::vector<std::shared_ptr<Barkeeper>> actors_) {

    if (IsKeyPressed(KEY_E) && interactionDisabled == false)
    {
        for (int i = 0; i < actors_.size(); i++)
        {

            if (CheckCollisionRecs(actors_[i]->collisionBox, this->interactionBox))
            {
                TraceLog(LOG_INFO, "Interaction successful!");


                float workingHeightBarkeeper = actors_[i]->position.y + actors_[i]->frameRec.height / 2;

                float workingHeightPlayer = this->position.y + this->frameRec.height / 2;

                if (workingHeightPlayer < workingHeightBarkeeper)
                    actors_[i]->turn(up);
                else
                    actors_[i]->turn(down);


                this->moveLockAbsolute = true;
                this->interactionDisabled = true;
                if (actors_[i]->firstInteraction == true)
                {
                    this->dialogueManager.startDialogue(actors_[i]->getName(), actors_[i]->getDialogue(),
                                                        actors_[i]->spritesheet);
                    actors_[i]->firstInteraction = false;
                }
                this->barkeeperPtr = actors_[i];
                this->openShopBarkeeper = true;
            }
        }
    }
}

void Player::interact(std::vector<std::shared_ptr<Dealer>> actors_)
{
    if (IsKeyPressed(KEY_E) && interactionDisabled == false)
    {
        for (int i = 0; i < actors_.size(); i++)
        {

            if (CheckCollisionRecs(actors_[i]->collisionBox, this->interactionBox))
            {
                TraceLog(LOG_INFO, "Interaction successful!");

                this->moveLockAbsolute = true;
                this->interactionDisabled = true;
                if (actors_[i]->firstInteraction == true)
                {
                    this->dialogueManager.startDialogue(actors_[i]->getName(), actors_[i]->getDialogue(),
                                                        actors_[i]->spritesheet);
                    actors_[i]->firstInteraction = false;
                }
                this->openShopDealer = true;
            }
        }
    }
}

// Interaction for enemies
void Player::interact(std::vector<std::shared_ptr<Enemy>> actors_) {

    if (IsKeyPressed(KEY_E) && interactionDisabled == false)
    {
        for (int i = 0; i < actors_.size(); i++)
        {
            if (CheckCollisionRecs(actors_[i]->collisionBox, this->interactionBox))
            {
                this->interactionForced(actors_[i]);
            }
        }
    }
}


void Player::interact(std::vector<std::shared_ptr<Item>> items) {
    if (IsKeyPressed(KEY_E) && interactionDisabled == false) {
        for (int i = 0; i < items.size(); i++) {
            if (items[i]->showInLevel == true) {
                if (CheckCollisionPointRec(items[i]->levelPosition,
                                           this->interactionBox)) { // has to be adjusted when items have hitboxes
                    TraceLog(LOG_INFO, "Interaction successful!");

                    items[i]->showInLevel = false;
                    this->inventory.push_back(items[i]);
                    this->moveLockAbsolute = true;
                    this->interactionDisabled = true;

                    std::string line = "Oh look, a ";
                    line.append(items[i]->name);
                    line.append("!");

                    std::vector<std::string> dialogue = {
                            line,
                            "This should come in handy..."
                    };

                    this->dialogueManager.startDialogue(this->getName(), dialogue,
                                                        this->spritesheet);
                }
            }
        }
    }
}

void Player::interactionForced(std::shared_ptr<Enemy> enemy)
{
    TraceLog(LOG_INFO, "Interaction successful!");

    Vector2 workingPosPlayer;
    workingPosPlayer.x = this->position.x + this->frameRec.width / 2;
    workingPosPlayer.y = this->position.y + this->frameRec.height / 2;

    Vector2 workingPosEnemy;
    workingPosEnemy.x = enemy->position.x + enemy->frameRec.width / 2;
    workingPosEnemy.y = enemy->position.y + enemy->frameRec.height / 2;


    Vector2 distance;
    distance.x = workingPosPlayer.x - workingPosEnemy.x; // Positive: Enemy is on the left, Negative: enemy is on the right
    distance.y = workingPosPlayer.y - workingPosEnemy.y; // Positive: Enemy is above, Negative: enemy is below

    int workingX;
    int workingY;

    // Make positive
    if (distance.x < 0)
        workingX = distance.x * -1;
    else
        workingX = distance.x;
    if (distance.y < 0)
        workingY = distance.y * -1;
    else
        workingY = distance.y;

    if (workingX >= workingY)
    {
        if (distance.x > 0)
        {
            this->turn(left);
            enemy->turn(right);
        }
        else
        {
            this->turn(right);
            enemy->turn(left);
        }
    }
    else if (distance.y > 0)
    {
        this->turn(up);
        enemy->turn(down);
    }
    else
    {
        this->turn(down);
        enemy->turn(up);
    }

    this->moveLockAbsolute = true;
    this->interactionDisabled = true;
    this->dialogueManager.startDialogue(enemy->getName(), enemy->getDialogue(), enemy->spritesheet);
    if (enemy->defeated == false) {
        this->enemyToFight = enemy;
        this->startCombat = true;
    }
}


void Player::checkActorCollision(std::vector<std::shared_ptr<Prop>> actors)
{
    for (const auto& actor : actors)
    {
        if (CheckCollisionRecs(this->collisionBox, actor->collisionBox))
        {
            this->position = this->prevPosition;
            /* Obsolete but could be useful later on
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
            } */
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
            this->position = this->prevPosition;
            /*  Obsolete but could be useful later on?
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
             */
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

