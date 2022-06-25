//
// Created by Maximilian R�ck on 05.06.2022.
//

#include "Actor.h"
#include <iostream>

Actor::Actor()
{
	std::cout << "[DEBUG] This function should not be called (Actor-Standardconstructor)" << std::endl;
}


Actor::Actor(int posX, int posY, Texture2D texture)
{
	this->position.x = posX;
	this->position.y = posY;

	this->activeTexture = texture;

	this->collisionBox.x = posX;
	this->collisionBox.y = posY;
	this->collisionBox.height = activeTexture.height;
	this->collisionBox.width = activeTexture.width;
}

void Actor::move()
{
	std::cout << "[DEBUG] Called actor.move()" << std::endl;
}

void Actor::turn(direction turningDirection)
{
	switch (turningDirection)
	{
	case up:
		this->facing = up;
		// Change active texture
		break;
	case down:
		this->facing = down;
		// Change active texture
		break;
	case left:
		this->facing = left;
		// Change active texture
		break;
	case right:
		this->facing = right;
		// Change active texture
		break;
	default: 
		std::cout << "[DEBUG] Error while turning actor" << std::endl;
	}

}
