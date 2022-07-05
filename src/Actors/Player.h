//
// Created by Maximilian R�ck on 05.06.2022.
//

#pragma once

#include "Prop.h"
#include "Actor.h"
#include <vector>
#include <memory>

class Player : public Actor {

	// Attributes
public:

	Vector2 prevPosition;

	// Character attributes. Better implemented using vectors?
	int strength;
	int defense;

	bool interacting = false; // Do we need this? Maybe for locking controls

	bool moveLockUp = false;
	bool moveLockDown = false;
	bool moveLockLeft = false;
	bool moveLockRight = false;

	Rectangle interactionBox;


	// Methods
public:
	Player();

    Player(int posX, int posY, Texture2D spritesheet_);

    void Update();

	void move();

	void interact(std::vector<std::shared_ptr<Prop>> actors_);

	void checkActorCollision(std::vector<std::shared_ptr<Prop>> actors);

};

