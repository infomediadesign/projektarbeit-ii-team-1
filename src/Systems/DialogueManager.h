//
// Created by Maximilian R�ck on 06.06.2022.
//

#pragma once

#include "raylib.h"
#include <string>
#include <vector>

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

	// Methods
public:
    DialogueManager();

	void Update();

	void startDialogue(std::string name, std::vector<std::string> dialogue, Texture2D spritesheet);

	void playDialogue(); // Belongs in an Update() method

	void stopDialogue();

	void drawDialogue(); // Belongs in a Draw() method


private:


};