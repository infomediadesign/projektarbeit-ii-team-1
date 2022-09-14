//
// Created by sefer on 07.09.2022.
//
#include "TutorialLevelScene.h"
TutorialLevelScene::TutorialLevelScene(std::shared_ptr<Player> player) {
    this->player = player;
    // Background img
    tutorialLevelBackgroundImg = LoadTexture("./assets/maps/TutorialLevel/TutorialLevelBackground.png");

    // Start dialogue
    player->dialogueManager.startDialogue(player->getName(),startDialogue, player->spritesheetIdle);

    // NPC img
    bouncer2 = std::make_shared<Bouncer2>(0,0, Tutorial, startDialogueBouncer);
    bouncer2->setDiaSwitches(dialogSwitches);
    // Dialog
}

void TutorialLevelScene::CustomUpdate() {
    player->Update();

    if (IsKeyPressed(KEY_I)) {
        this->switchTo = INVENTORY;
        this->switchScene = true;
    }
    if (IsKeyPressed(KEY_C)) {
        this->switchTo = SKILLTREE;
        this->switchScene = true;
    }
    if (IsKeyPressed(KEY_P)) {
        this->switchTo = PAUSEMENU;
        this->switchScene = true;
    }
}

void TutorialLevelScene::CustomDraw() {
    // Draw level background img
    TraceLog(LOG_INFO, "DRAW TUTORIALLEVEL BACKGROUND *************");
    Vector2 backgroundImgPos {0,0};
    DrawTexture(tutorialLevelBackgroundImg,backgroundImgPos.x, backgroundImgPos.y,WHITE);

    // Draw npc img
    player->Draw();

}