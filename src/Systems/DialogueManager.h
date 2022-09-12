//
// Created by Maximilian R�ck on 06.06.2022.
//

#pragma once

#include "raylib.h"
#include <string>
#include <vector>
#include <memory>
#include "../Actors/Actor.h"

class DialogueManager {

	// Attributes
public:
    bool dialoguePlaying = false;

private:
    // Text related
    Font font;

    // Texture related
    Texture2D panelTexture;
    Texture2D loadedSpritesheet;
    Rectangle portraitRec;

    // System related
	std::vector<std::string> rawDialogue;
    std::string lineToDraw;
    std::string name;
    int lineCounter = 0;
    int charCounter = 0;

    // Crutches for the upgraded dialogue system
    bool monologue;
    std::string name2;
    Texture2D loadedSpritesheet2;
    std::vector<int> diaSwitches;

    // Sfx related
    Sound soundChatter;

	// Methods
public:
    DialogueManager();

	void Update();

    // For single actor / Monologue
	void startDialogue(std::string name, std::vector<std::string> dialogue, Texture2D spritesheet);
    // For two actors
    void startDialogue(std::string name1, Texture2D spritesheet1, std::string name2, Texture2D spritesheet2, std::vector<std::string> dialogue, std::vector<int> diaSwitches);

	void playDialogue(); // Belongs in an Update() method

	void stopDialogue();

	void drawDialogue(); // Belongs in a Draw() method

    // Crutch for the upgraded dialogue system
    void switchActors();
};