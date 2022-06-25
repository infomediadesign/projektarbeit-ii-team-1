//
// Created by Maximilian R�ck on 05.06.2022.
//

#include "Player.h"
#include <iostream>
#include <raylib.h>


Player::Player()
{
    std::cout << "[DEBUG] This function should not be called (Player-Standardconstructor)" << std::endl;
}

Player::Player(int posX, int posY, Texture2D texture)
{
    this->position.x = posX;
    this->position.y = posY;

    this->activeTexture = texture;

    this->collisionBox.x = posX;
    this->collisionBox.y = posY;
    this->collisionBox.height = activeTexture.height;
    this->collisionBox.width = activeTexture.width;


}


void Player::Update() {
    this->move();




    //this->interact();
}


void Player::move()
{
	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
	{
		if (this->facing != up)
            this->turn(up);
		this->position.y = position.y - this->speed;

        //Adjusting interaction box
        this->interactionBox.width = this->activeTexture.width;
        this->interactionBox.height = this->activeTexture.height;
        this->interactionBox.x = this->position.x;
        this->interactionBox.y = this->position.y - this->activeTexture.height;
	}
	if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
	{
        if (this->facing != down)
            this->turn(down);
		this->position.y = position.y + this->speed;

        //Adjusting interaction box
        this->interactionBox.width = this->activeTexture.width;
        this->interactionBox.height = this->activeTexture.height;
        this->interactionBox.x = this->position.x;
        this->interactionBox.y = this->position.y + this->activeTexture.height;
	}
	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
	{
        if (this->facing != left)
		    this->turn(left);
		this->position.x = position.x - this->speed;

        //Adjusting interaction box
        this->interactionBox.width = this->activeTexture.width;
        this->interactionBox.height = this->activeTexture.height;
        this->interactionBox.x = this->position.x - activeTexture.width;
        this->interactionBox.y = this->position.y;
	}
	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
	{
        if (this->facing != right)
		    this->turn(right);
		this->position.x = position.x + this->speed;

        //Adjusting interaction box
        this->interactionBox.width = this->activeTexture.width;
        this->interactionBox.height = this->activeTexture.height;
        this->interactionBox.x = this->position.x + activeTexture.width;
        this->interactionBox.y = this->position.y;
	}
	this->collisionBox.x = this->position.x;
    this->collisionBox.y = this->position.y;

}

void Player::interact(std::vector<Actor> actors_) {

    if (IsKeyPressed(KEY_E))
    {
        for (int i = 0; i < actors_.size(); i++)
        {

            if (CheckCollisionRecs(actors_[i].collisionBox, this->interactionBox))
            {
                std::cout << "[DEBUG] Interaction successful!" << std::endl;
                std::cout << "[DEBUG] Interacted with " << actors_[i].getName() << std::endl;
            }
        }
    }
}
