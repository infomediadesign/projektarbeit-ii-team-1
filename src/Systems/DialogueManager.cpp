//
// Created by Maximilian R�ck on 06.06.2022.
//

#define PANEL_HEIGHT (GetScreenHeight() * 0.67777777777777)
#define DIA_PADDING (GetScreenWidth() * 0.16)
#define DIA_HEIGHT GetScreenHeight() * 0.7935;

#include "DialogueManager.h"
#include <iostream>
#include <memory>

DialogueManager::DialogueManager()
{
this->panelTexture = LoadTexture("assets/graphics/ui/dialogueWindow.png");
this->font = LoadFont("assets/graphics/Habbo.ttf");
}

void DialogueManager::Update()
{
	this->playDialogue();
}

void DialogueManager::startDialogue(std::string name, std::vector<std::string> dialogue, Texture2D spritesheet)
{
	std::cout << "[DEBUG] Dialogue started.";
	this->lineCounter = 0;
	this->charCounter = 0;

    this->name = name;
	this->rawDialogue = dialogue;
	this->lineToDraw.clear();

	this->dialoguePlaying = true;

    this->loadedSpritesheet = spritesheet;
    this->portraitRec.x = 0;
    this->portraitRec.y = 0;
    this->portraitRec.width = this->loadedSpritesheet.width / 4;
    this->portraitRec.height = this->portraitRec.width;
}

void DialogueManager::playDialogue()
{
	if (this->dialoguePlaying == true)
	{
        std::string lineToLoad = this->rawDialogue[this->lineCounter];

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
	this->dialoguePlaying = false;
}

void DialogueManager::drawDialogue()
{
	// BeginDrawing() and EndDrawing() are located in main()

	if (this->dialoguePlaying == true)
	{
		// Draw panel
        DrawTexture(this->panelTexture, 0, PANEL_HEIGHT, WHITE);

        // Draw portrait
        Vector2 portraitPos;
        portraitPos.x = GetScreenWidth() * 0.0305;
        portraitPos.y = DIA_HEIGHT;
        DrawTextureRec(this->loadedSpritesheet, this->portraitRec, portraitPos , WHITE);

        // Draw name
        Vector2 namePos;
        namePos.x = GetScreenWidth() * 0.015;
        namePos.y = GetScreenHeight() * 0.702;
        DrawTextEx(this->font, this->name.c_str(), namePos, 30, 5, BLACK);

		// Draw dialogue
		//DrawText(this->lineToDraw.c_str(), DIA_PADDING, PANEL_HEIGHT + 200, 60, GREEN);
        Vector2 diaPos;
        diaPos.x = DIA_PADDING;
        diaPos.y = DIA_HEIGHT
        DrawTextEx(this->font, this->lineToDraw.c_str(), diaPos, 70, 5, BLACK);
	}
}