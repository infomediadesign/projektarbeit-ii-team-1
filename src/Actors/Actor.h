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

	Direction facing = down;

	int hp;
	int money;
	int speed = 5;

	// Everything regarding textures

	Texture2D spritesheet; // All textures, formatted in a spritesheet

	Rectangle frameRec = { 0.0f, 0.0f, (float)spritesheet.width / 4, (float)spritesheet.height / 4 };;
	int framesCounter = 0;
	int frameSpeed = 6;
	int currentFrame = 0;

	// Methods
public:

	Actor();

	Actor(int posX, int posY, Texture2D spritesheet_, std::vector<std::string> dialogue_);

    void Update();

    void Draw();

	void move();

	void animate();

	// onInteraction();

	void turn(Direction turningDirection);

};
