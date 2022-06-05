//
// Created by Maximilian Röck on 05.06.2022.
//

#include "Player.h"

void Player::move()
{

	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
	{
		this->turn(up);
		this->posY = posY - this->speed;
	}
	if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
	{
		this->turn(down);
		this->posY = posY + this->speed;
	}
	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
	{
		this->turn(left);
		this->posX = posX - this->speed;
	}
	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
	{
		this->turn(down);
		this->posX = posX + this->speed;
	}
	
}
