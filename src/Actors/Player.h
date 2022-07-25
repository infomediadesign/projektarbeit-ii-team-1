//
// Created by Maximilian R�ck on 05.06.2022.
//

#pragma once

#include "Prop.h"
#include "Actor.h"
#include "../Systems/DialogueManager.h"
#include <vector>
#include <memory>

class Player : public Actor {

	// Attributes
public:

	// Regarding idle animation
	Texture2D spritesheetIdle;
    bool playIdle;

	//Rectangle frameRecWalk = { 0.0f, 0.0f, (float)spritesheetWalk.width / 4, (float)spritesheetWalk.height / 4 };


	Vector2 prevPosition;

	// Character attributes. Better implemented using vectors?
	int strength;
	int defense;

	bool moveLockAbsolute = false;

	bool moveLockUp = false;
	bool moveLockDown = false;
	bool moveLockLeft = false;
	bool moveLockRight = false;

	Rectangle interactionBox;
    bool interactionDisabled = false;

    DialogueManager dialogueManager;

	// Methods
public:
	Player();

	Player(int posX, int posY, Texture2D spritesheet_, Texture2D spritesheetIdle_);

	void Update();

    void Draw();

	void move();

	void interact(std::vector<std::shared_ptr<Prop>> actors_);
    void interact(std::vector<std::shared_ptr<Actor>> actors_);

	void checkActorCollision(std::vector<std::shared_ptr<Prop>> actors);
    void checkActorCollision(std::vector<std::shared_ptr<Actor>> actors);
};

