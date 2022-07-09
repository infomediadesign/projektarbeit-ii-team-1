//
// Created by Maximilian Röck on 06.06.2022.
//

#pragma once

#include "raylib.h"
#include <string>
#include <vector>

class DialogueManager {

	// Attributes
private:

	bool dialoguePlaying = false;

	std::vector<std::string> rawDialogue;

	int lineCounter = 0;
	int charCounter = 0;

	std::string lineToDraw;

	Rectangle panel; // Dialogue panel
	bool panelOpen = false;


	// Methods
public:
	void Update();

	void startDialogue(std::vector<std::string> dialogue);

	void playDialogue(); // Belongs in an Update() method

	void stopDialogue();

	void drawDialogue(); // Belongs in a Draw() method


private:


};