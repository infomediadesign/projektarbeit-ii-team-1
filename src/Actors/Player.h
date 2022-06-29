//
// Created by Maximilian R�ck on 05.06.2022.
//

#pragma once

#include "Prop.h"
#include "Actor.h"

class Player : public Actor {

	// Attributes
public:

	// Character attributes. Better implemented using vectors?
	int strength;
	int defense;

	bool interacting = false; // Do we need this? Maybe for locking controls

	Rectangle interactionBox;


	// Methods
public:
	Player();

    Player(int posX, int posY, Texture2D spritesheet_);

    void Update();

	void move();

	void interact(std::vector<Actor> actors_);
};

