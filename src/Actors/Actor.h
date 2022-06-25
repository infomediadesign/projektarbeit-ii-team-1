//
// Created by Maximilian R�ck on 05.06.2022.
//

#pragma once

#include "Prop.h"
#include "raylib.h"
#include <vector>
#include "enums.h"

class Actor : public Prop {

public: // Attributes

	direction facing = down;

	int hp;
	int money;
	int speed = 5; //Do we need this?

private:
	Texture2D textures; // All textures, formatted in a spritesheet
	//std::vector<Texture2D> textures; // Another possible way to implement this

	// Methods
public:

	Actor();

	Actor(int posX, int posY, Texture2D texture);
	
	void move();

	// onInteraction();

	void turn(direction turningDirection);

};
