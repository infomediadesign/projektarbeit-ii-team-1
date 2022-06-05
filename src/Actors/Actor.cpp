//
// Created by Maximilian Röck on 05.06.2022.
//

#include "Actor.h"
#include <iostream>

void Actor::move()
{
	std::cout << "[DEBUG] Called actor move()" << std::endl;
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
