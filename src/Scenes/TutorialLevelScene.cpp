//
// Created by sefer on 07.09.2022.
//
#include "TutorialLevelScene.h"
TutorialLevelScene::TutorialLevelScene(Level currentLevel, std::string currentLevelRoom,std::shared_ptr<Player> player) {
    this->player = player;
    this->currentLevelRooms = currentLevelRoom;
    this->currentLevel = currentLevel;
    this->switchNextRoom = false;
    this->switchNextLevel = false;

    // Background img
    tutorialLevelBackgroundImg = LoadTexture("./assets/maps/TutorialLevel/TutorialLevelBackground.png");

    // Start dialogue
    player->dialogueManager.startDialogue(player->getName(),startDialogue, player->spritesheetIdle);
    // NPC img
    npcTutorial = std::make_shared<Actor>(250, 580,Texture2D{LoadTexture("assets/graphics/character/npcIdle/npc2/npc2.png")},startDialogueBouncer);
    npcTutorial->setName("Dealer");
    npcTutorial->setDiaSwitches(dialogSwitches);

    actors.push_back(npcTutorial);
    // Dialog


    mousePos = GetMousePosition();
}

void TutorialLevelScene::CustomUpdate() {
    player->Update();
    this->CheckCollision();

    if (IsKeyPressed(KEY_I)) {
        this->switchTo = INVENTORY;
        this->switchScene = true;
        TraceLog(LOG_INFO,"TUTORIAL I");
    }
    if (IsKeyPressed(KEY_C)) {
        this->switchTo = SKILLTREE;
        this->switchScene = true;
        TraceLog(LOG_INFO,"TUTORIAL C");
    }
    if (IsKeyPressed(KEY_P)) {
        this->switchTo = PAUSEMENU;
        this->switchScene = true;
        TraceLog(LOG_INFO,"TUTORIAL P");
    }

    // ===== Check if a fight has to be started =====
    if (player->startCombat == true && player->dialogueManager.dialoguePlaying == false) {
        TraceLog(LOG_INFO, "Starting combat...");
        player->startCombat = false;
        // Start combat with player and player->enemyToFight
        // Has to remember the player's position in the level before battle!

        this->switchTo = BATTLE;
        this->switchScene = true;
    }

    // ===== Check enemy aggro radius collision =====
    bool stopSearch = false;
    for (int i = 0; i < enemies.size() && stopSearch == false &&
                    player->dialogueManager.dialoguePlaying == false; i++) {
        if (CheckCollisionCircleRec({enemies[i]->position.x + enemies[i]->frameRec.width / 2,
                                     enemies[i]->position.y + enemies[i]->frameRec.height / 2},
                                    enemies[i]->aggroRadius, player->collisionBox) &&
            enemies[i]->defeated == false &&
            this->switchScene == false) {
            player->interactionForced(enemies[i]);
            stopSearch = true;
        }
    }

    player->interact(actors);
    player->interact(enemies);
    player->interact(barkeepers);
    player->interact(dealers);
    player->interact(items);


    for (int i = 0; i < actors.size(); i++) {
        actors[i]->Update();
    }
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->Update();
    }
    for (int i = 0; i < barkeepers.size(); i++) {
        barkeepers[i]->Update();
    }
    for (int i = 0; i < dealers.size(); i++) {
        dealers[i]->Update();
    }




    mousePos = GetMousePosition();
}

void TutorialLevelScene::CustomDraw() {
    // Draw level background img
    Vector2 backgroundImgPos {0,0};
    DrawTexture(tutorialLevelBackgroundImg,backgroundImgPos.x, backgroundImgPos.y,WHITE);

    DrawRectangleLines(tutorialExitBoxes.at("tutorial").rec.x ,
                       tutorialExitBoxes.at("tutorial").rec.y,
                       tutorialExitBoxes.at("tutorial").rec.width,
                       tutorialExitBoxes.at("tutorial").rec.height, RED);

    // Draw npc img
    npcTutorial->Draw();
    player->Draw();
    player->dialogueManager.drawDialogue();
    DrawText(("x:" + std::to_string(mousePos.x) +" y:" + std::to_string(mousePos.y)).c_str(), GetMousePosition().x,GetMousePosition().y,10, RED);
}

void TutorialLevelScene::CheckCollision()
{
    if(CheckCollisionRecs(player->collisionBox, tutorialExitBoxes.at(this->currentLevelRooms).rec)) {
        TraceLog(LOG_INFO, "TUTORIAL Player kollidiert mit Box");
        switchLevelScene = true;
        switchNextLevel = true;
        switchNextRoom = true;
        nextLevel = tutorialExitBoxes.at(this->currentLevelRooms).nextLevelName;
        nextRoom = tutorialExitBoxes.at(this->currentLevelRooms).nextRoomName;
        newPlayerPos = tutorialExitBoxes.at("tutorial").newStartPos;

    }
}

/*}else if(currentExitCount.at(currentLevelRooms) > 1){
            room + std::to_string(i);
            if (i == 1){
                DrawRectangleLines(currentExitBoxes.at(room).rec.x+ 200 ,
                                   currentExitBoxes.at(room).rec.y,
                                   currentExitBoxes.at(room).rec.width,
                                   currentExitBoxes.at(room).rec.height, RED);
                std::cout<< currentLevelRooms <<std::endl;

            }else{

                DrawRectangleLines(currentExitBoxes.at(room).rec.x+ 200 ,
                                   currentExitBoxes.at(room).rec.y,
                                   currentExitBoxes.at(room).rec.width,
                                   currentExitBoxes.at(room).rec.height, RED);
                //std::string room = currentLevelRooms + std::to_string(i);
                std::cout<< room <<std::endl;
            }*/