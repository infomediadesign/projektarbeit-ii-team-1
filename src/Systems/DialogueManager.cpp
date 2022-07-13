//
// Created by Maximilian Röck on 06.06.2022.
//

#include "DialogueManager.h"
#include <iostream>
#include <memory>

void DialogueManager::Update()
{
	this->playDialogue();
}

void DialogueManager::startDialogue(std::vector<std::string> dialogue)
{
	std::cout << "[DEBUG] Dialogue started.";
	this->lineCounter = 0;
	this->charCounter = 0;

	this->rawDialogue = dialogue;
	this->lineToDraw.clear();

	this->dialoguePlaying = true;

	// Open panel

}

void DialogueManager::playDialogue()
{
	std::string lineToLoad = this->rawDialogue[this->lineCounter];


	if (this->dialoguePlaying == true)
	{
		// Closes dialogue when E is pressed while the final line is being displayed
		if (IsKeyPressed(KEY_E) && lineCounter == this->rawDialogue.size() - 1)		// Possible source for game crashing bugs
		{																			// (subscript out of range)
			this->stopDialogue();
		}
		// Scrolls through dialogue when E is pressed and it's not the final line (failsafe for preventing crashes)
		else if (IsKeyPressed(KEY_E) && lineCounter < this->rawDialogue.size() - 1)	// Possible source for game crashing bugs
		{																			// (subscript out of range)
			this->lineCounter++;
			this->charCounter = 0;
			this->lineToDraw.clear();
		}
		// Loads the next character of the currently active line if the line is not already fully loaded
		else if (charCounter < rawDialogue[lineCounter].size())						// Possible source for game crashing bugs
		{																			// (subscript out of range)

			this->lineToDraw.push_back(lineToLoad[this->charCounter]);
			charCounter++;
		}
	}

	// Quick implementation reminder: If ever implemented, automatic line breaks will work like this:
	// this->lineToDraw.push_back('\');
	// this->lineToDraw.push_back('n');
	// Or if this works (which I doubt):
	// this->lineToDraw.push_back("\n");

}

void DialogueManager::stopDialogue()
{
	// Close panel


	this->dialoguePlaying = false;

}

void DialogueManager::drawDialogue()
{
	// BeginDrawing() and EndDrawing() are located in main()

	if (this->dialoguePlaying == true)
	{
		// Draw panel

		// Draw text
		DrawText(this->lineToDraw.c_str(), GetScreenWidth() / 2, GetScreenHeight() / 2, 30, LIGHTGRAY);
	}
}
