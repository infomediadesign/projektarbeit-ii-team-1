//
// Created by sefer on 07.09.2022.
//
#include "TutorialLevelScene.h"
TutorialLevelScene::TutorialLevelScene(std::shared_ptr<Player> player) {
    this->player = player;
    // Background img
    tutorialLevelBackgroundImg = LoadTexture("./assets/maps/TutorialLevel/TutorialLevelBackground.png");
    // Hitboxen


    // NPC img
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