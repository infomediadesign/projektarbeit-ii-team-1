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

    TutorialLevelScene(std::shared_ptr<Player> player);

    void CustomUpdate() override;
    void CustomDraw() override;
protected:;
};


#endif //RAYLIBSTARTER_TUTORIALLEVELSCENE_H