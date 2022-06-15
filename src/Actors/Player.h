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
	int constitution;
	int intelligence;
	int defense;

	bool interacting = false; // Do we need this? Maybe for locking controls

	// Methods
public:

    Player(int posX, int posY, Texture2D texture);

    void Update();

	void move();

	void interact(std::vector<Actor> actors_);
};
