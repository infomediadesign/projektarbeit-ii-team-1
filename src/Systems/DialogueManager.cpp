//
// Created by Maximilian R�ck on 06.06.2022.
//

#define PANEL_HEIGHT (GetScreenHeight() * 0.67777777777777)
#define DIA_PADDING (GetScreenWidth() * 0.16)
#define DIA_HEIGHT GetScreenHeight() * 0.7935;

#include "DialogueManager.h"
#include <memory>

// For tests
#include <iostream>

extern float volSfx;

DialogueManager::DialogueManager()
{
this->panelTexture = LoadTexture("assets/graphics/ui/dialogueWindow.png");
this->font = LoadFont("assets/graphics/ui/Habbo.ttf");

this->soundChatter = LoadSound("assets/audio/sfx/chatter.wav");
SetSoundVolume(this->soundChatter, volSfx);
}

void DialogueManager::Update()
{
	this->playDialogue();
}

void DialogueManager::startDialogue(std::string name, std::vector<std::string> dialogue, Texture2D spritesheet)
{
    TraceLog(LOG_INFO, "Dialogue started (Mono)...");
	this->lineCounter = 0;
	this->charCounter = 0;

    this->monologue = true;
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

void
DialogueManager::startDialogue(std::string name1, Texture2D spritesheet1, std::string name2, Texture2D spritesheet2,
                               std::vector<std::string> dialogue, std::vector<int> diaSwitches) {

    TraceLog(LOG_INFO, "Dialogue started (Dia)...");
    this->lineCounter = 0;
    this->charCounter = 0;

    this->monologue = false;
    this->diaSwitches = diaSwitches;
    this->name = name1;
    this->name2 = name2;
    this->rawDialogue = dialogue;
    this->lineToDraw.clear();

    this->dialoguePlaying = true;

    this->loadedSpritesheet = spritesheet1;
    this->loadedSpritesheet2 = spritesheet2;
    this->portraitRec.x = 0;
    this->portraitRec.y = 0;
    this->portraitRec.width = this->loadedSpritesheet.width / 4;
    this->portraitRec.height = this->portraitRec.width;

    for (int i = 0; i < this->diaSwitches.size(); i++)
    {
        if (this->lineCounter == diaSwitches[i])
        {
            this->switchActors();
        }
    }

}

void DialogueManager::playDialogue()
{
	if (this->dialoguePlaying == true)
    {
        // Stop sound when a line is completed
        if (charCounter >= rawDialogue[lineCounter].size())
        {
            StopSound(this->soundChatter);
        }

        std::string lineToLoad = this->rawDialogue[this->lineCounter];

        // Closes dialogue when E is pressed while the final line is being displayed
        if (IsKeyPressed(KEY_E) && lineCounter == this->rawDialogue.size() - 1)        // Possible source for game crashing bugs
        {                                                                            // (subscript out of range)
            StopSound(this->soundChatter);
            this->stopDialogue();
        }
            // Scrolls through dialogue when E is pressed and it's not the final line (failsafe for preventing crashes)
        else if (IsKeyPressed(KEY_E) && lineCounter < this->rawDialogue.size() - 1)    // Possible source for game crashing bugs
        {                                                                            // (subscript out of range)
            StopSound(this->soundChatter);
            this->lineCounter++;
            this->charCounter = 0;
            this->lineToDraw.clear();

            // For upgraded dialogue system
            if (this->monologue == false)
            {
                for (int i = 0; i < this->diaSwitches.size(); i++)
                {
                    if (this->lineCounter == diaSwitches[i])
                    {
                        this->switchActors();
                    }
                }
            }
        }
            // Loads the next character of the currently active line if the line is not already fully loaded
        else if (charCounter < rawDialogue[lineCounter].size())                        // Possible source for game crashing bugs
        {                                                                            // (subscript out of range)
            // Play sound if no sound is playing
            if (IsSoundPlaying(this->soundChatter) == false)
            {
                PlaySound(this->soundChatter);
            }


            this->lineToDraw.push_back(lineToLoad[this->charCounter]);
            charCounter++;
        }
    }
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


        namePos.x = (GetScreenWidth() * 0.07) - MeasureTextEx(this->font, this->name.c_str(), 30, 3).x/2;;
        namePos.y = GetScreenHeight() * 0.702;
        DrawTextEx(this->font, this->name.c_str(), namePos, 30, 3, BLACK);

		// Draw dialogue
		//DrawText(this->lineToDraw.c_str(), DIA_PADDING, PANEL_HEIGHT + 200, 60, GREEN);
        Vector2 diaPos;
        diaPos.x = DIA_PADDING;
        diaPos.y = DIA_HEIGHT
        DrawTextEx(this->font, this->lineToDraw.c_str(), diaPos, 70, 5, BLACK);
	}
}

void DialogueManager::switchActors()
{
    std::string workingName = this->name;
    Texture2D workingSheet = this->loadedSpritesheet;

    this->name = this->name2;
    this->loadedSpritesheet = this->loadedSpritesheet2;
    this->name2 = workingName;
    this->loadedSpritesheet2 = workingSheet;
}

