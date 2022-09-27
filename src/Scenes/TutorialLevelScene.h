//
// Created by sefer on 07.09.2022.
//
#ifndef RAYLIBSTARTER_TUTORIALLEVELSCENE_H
#define RAYLIBSTARTER_TUTORIALLEVELSCENE_H

#pragma once
#include "config.h"
#include "LevelScene.h"
#include "../Actors/Player.h"
#include "../Actors/Dealer.h"
#include "../Actors/Actor.h"
#include "../Actors/Enemies/Bouncer2.h"
#include "../Actors/enums.h"


class TutorialLevelScene : public LevelScene {

private:;
public:
    Texture2D tutorialLevelBackgroundImg;

    Rectangle recExitLevel ={0.0,0.0,10,10};
    Vector2 playerStartPos;
    std::shared_ptr<Actor> npcTutorial;

    Vector2 mousePos;


    std::vector<std::string> startDialogue = {"Man, I wish I could get something out of this.",
                                              "If the chief finds out I'm infiltrating the\n Endless Dragon Gang HQ, he'll kill me.",
                                              "Unless those gangsters do it first when they\nfind out I'm an undercover cop.",
                                              "But I can't help it.\nThose bastards have something to do with...","Charlie and Monika's accident and I'm going\nto find out.",
                                              "No matter what it costs."};
    std::vector<std::string> startDialogueBouncer = {"Hey, what's up?", "Are you the one looking for a kick?\nI just got some new stuff in. ",
                                                     "You're the first to try it out. How's it looks?",
                                                     "Oh, you want to know how you move, right?",
                                                     "Always these junkies, they forget everything. ",
                                                     "You have two healthy legs that you can move\nwith WASD or the arrow keys. ",
                                                     "If you want to talk to people, you walk up to\nthem and press E. ",
                                                     "That's how you use your mouth, you moron. ",
                                                     "If you get into a fight, then you should know\nthat they are turn based. ",
                                                     "So, you get to hit first and then you get\nslapped. ",
                                                     "Whoever is still standing at the end wins. ",
                                                     "It's almost like that old video game Pekemon\nor something, I don't remember. ",
                                                     "You can bump into the guy on the street\nover there,...",
                                                     "he'll probably fight you, then you'll\nunderstand what I mean. "};
    std::vector<int> dialogSwitches = {};


    TutorialLevelScene(Level currentLevel, std::string currentLevelRoom,std::shared_ptr<Player> player);
    void CheckCollision();

    void CustomUpdate() override;
    void CustomDraw() override;
protected:;
};


#endif //RAYLIBSTARTER_TUTORIALLEVELSCENE_H