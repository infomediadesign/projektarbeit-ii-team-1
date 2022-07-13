//
// Created by Maximilian R�ck on 05.06.2022.
//

#include "Actor.h"
#include <iostream>

Actor::Actor()
{
	std::cout << "[DEBUG] This function should not be called (Actor-Standardconstructor)" << std::endl;
}


Actor::Actor(int posX, int posY, Texture2D spritesheet_, std::vector<std::string> dialogue_)
{
	this->position.x = posX;
	this->position.y = posY;

	this->spritesheet = spritesheet_;
	this->frameRec.width = this->spritesheet.width / 4;
	this->frameRec.height = this->spritesheet.height / 4;

	this->collisionBox.x = posX;
	this->collisionBox.y = posY;
	this->collisionBox.height = frameRec.height;
	this->collisionBox.width = frameRec.width;

    this->dialogue = dialogue_;
}

void Actor::Update()
{
    std::cout << "[DEBUG] Updating actor" << std::endl;
    this->framesCounter++;
    animate();
}

void Actor::Draw()
{
    std::cout << "[DEBUG] Drawing actor" << std::endl;
    DrawTextureRec(this->spritesheet, this->frameRec, this->position, WHITE);

    // Debug boxes
    DrawRectangleLines(this->collisionBox.x, this->collisionBox.y, this->collisionBox.width, this->collisionBox.height,
                       RED);
}

void Actor::move()
{
	std::cout << "[DEBUG] Called actor.move()" << std::endl;
}

void Actor::animate()
{
	// Reminder: framesCounter++ belongs in the Update()-Method of the classes
	// (Prevents animation from speeding up when multiple move-keys are pressed)
	if (this->framesCounter >= (60 / this->frameSpeed))
	{
		this->framesCounter = 0;
		this->currentFrame++;

		if (this->currentFrame > 3) this->currentFrame = 0;

		this->frameRec.x = (float)this->currentFrame * (float)this->spritesheet.width / 4;
	}
}

void Actor::turn(Direction turningDirection)
{
	switch (turningDirection)
	{
	case up:
		this->facing = up;
		// Change height of spritesheet-frame
		this->frameRec.y = spritesheet.height / 4;
		break;
	case down:
		this->facing = down;
		// Change height of spritesheet-frame
		this->frameRec.y = 0;
		break;
	case left:
		this->facing = left;
		// Change height of spritesheet-frame
		this->frameRec.y = spritesheet.height - spritesheet.height / 4;
		break;
	case right:
		this->facing = right;
		// Change height of spritesheet-frame
		this->frameRec.y = spritesheet.height / 2;
		break;
	default:
		std::cout << "[DEBUG] Error while turning actor" << std::endl;
	}

}
