//
// Created by Maximilian R�ck on 05.06.2022.
//

#pragma once

#include "Prop.h"
#include "Actor.h"
#include "../Systems/DialogueManager.h"
#include "Enemies/CombatStructs.h"
#include "Enemies/Enemy.h"
#include "../Items/Item.h"
#include <vector>
#include <memory>
#include "../Scenes/InventoryScene.h"
#include "../Scenes/SkillTreeScene.h"


class Player : public Actor {

	// Attributes
public:
    //InventoryScene inventory;
    SkillTreeScene skillree;


    bool genderMale;

	// Regarding idle animation
	Texture2D spritesheetIdle;
    bool playIdle;

    // Combat animations
    CombatSheet spritesheetAttackPunch;
    CombatSheet spritesheetAttackPunchGun;
    CombatSheet spritesheetAttackBottlecap;
    CombatSheet spritesheetAttackLaser;
    CombatSheet spritesheetAttackBomb;
    CombatSheet spritesheetAttackFrisbee;
    CombatSheet spritesheetReactPunch;
    CombatSheet spritesheetReactTazer;

	Vector2 prevPosition;

	// Character attributes. Better implemented using vectors?
    float maxHP;
    float currentHP;
	int defense;

    // Placeholder?
    std::vector<std::shared_ptr<Item>> inventory;

    bool inventoryOpened = false;
    bool skilltreeOpend = false;

	bool moveLockAbsolute = false;

	bool moveLockUp = false;
	bool moveLockDown = false;
	bool moveLockLeft = false;
	bool moveLockRight = false;

	Rectangle interactionBox;
    bool interactionDisabled = false;

    DialogueManager dialogueManager;

    // Combat
    std::shared_ptr<Enemy> enemyToFight;
    bool startCombat;

	// Methods
public:
	Player();

	Player(int posX, int posY, bool genderMale);

	void Update();

    void Draw();

	void move();

	void interact(std::vector<std::shared_ptr<Prop>> actors_);
    void interact(std::vector<std::shared_ptr<Actor>> actors_);
    void interact(std::vector<std::shared_ptr<Enemy>> actors_);
    void interactionForced(std::shared_ptr<Enemy> enemy);

	void checkActorCollision(std::vector<std::shared_ptr<Prop>> actors);
    void checkActorCollision(std::vector<std::shared_ptr<Actor>> actors);
};

