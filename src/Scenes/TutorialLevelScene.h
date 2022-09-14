//
// Created by sefer on 07.09.2022.
//
#ifndef RAYLIBSTARTER_TUTORIALLEVELSCENE_H
#define RAYLIBSTARTER_TUTORIALLEVELSCENE_H

#pragma once
#include "config.h"
#include "LevelScene.h"
#include "../Actors/Player.h"
#include "../Actors/Enemies/Bouncer2.h"
#include "../Actors/enums.h"




class TutorialLevelScene : public LevelScene {

private:;
public:
    Texture2D tutorialLevelBackgroundImg;

    Rectangle recExitLevel ={0.0,0.0,10,10};
    Vector2 playerStartPos;
    std::shared_ptr<Bouncer2> bouncer2;

    std::vector<std::string> startDialogue = {"this is a test", "this is a test line","blaaaaa"};
    std::vector<std::string> startDialogueBouncer = {"tnerv mich nict", "geh nach hause"};
    std::vector<int> dialogSwitches = {1};


    TutorialLevelScene(std::shared_ptr<Player> player);

    void CustomUpdate() override;
    void CustomDraw() override;
protected:;
};


#endif //RAYLIBSTARTER_TUTORIALLEVELSCENE_H