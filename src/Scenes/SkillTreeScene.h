//
// Created by Munchkin on 24.05.2022.
//

#pragma once
#include "MenuScenes.h"
#include "raylib.h"
#include "config.h"
#include <memory>
#include "vector"
#include "../Actors/Player.h"


class SkillTreeScene : public MenuScenes {
private:
    // ===== UI PNGS =====
    Texture2D arrowImg, skillUnlockecImg, skillLockedImg, skillLeftArmImg,
            skillRightArmImg, skillLeftLegImg, skillRightLegImg, skillLeftEyeImg,
            skillRightEyeImg;

    //SFX
    Sound uiBlip; //navigate
    Sound uiBlip2; //confirm

    std::vector<Texture2D> skillImgs = {skillLeftArmImg, skillRightArmImg, skillLeftLegImg, skillRightLegImg, skillLeftEyeImg,skillRightEyeImg};
    std::vector<std::string> skillTxts = {"Left arm", "Right arm", "Left leg", "Right leg", "Left Eye", "Right Eye"};
    std::vector<std::string> skillInfoTxts ={"Defence: 2", "Defence: 4", "Defence: 8", "Defence: 12", "Defence: 16", "Defence: 22"};
public:
    std::shared_ptr<Player> player;
    std::vector<Vector2> skillPos ={Vector2 {80,Game::ScreenHeight/2-50}, Vector2 {410,Game::ScreenHeight/2-50},Vector2 {720,Game::ScreenHeight/2-50},
                                    Vector2{1040,Game::ScreenHeight/2-50}, Vector2 {1360,Game::ScreenHeight/2-50},Vector2 {1670,Game::ScreenHeight/2-50}};
    Font font1;


    SkillTreeScene(std::shared_ptr<Player> player);
    void CustomUpdate() override;
    void CustomDraw() override;

    void DrawSkillTree ();
protected:;
};

