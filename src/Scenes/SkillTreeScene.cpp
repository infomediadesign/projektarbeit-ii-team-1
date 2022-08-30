//
// Created by Munchkin on 24.05.2022.
//

#include "SkillTreeScene.h"
#include "memory"


SkillTreeScene::SkillTreeScene()
{

}

void SkillTreeScene::CustomUpdate()
{

}

void SkillTreeScene::CustomDraw()
{
    this->DrawSkillTree();
}

void SkillTreeScene::DrawSkillTree()
{
    // Draw basics, Background, Text
    ClearBackground(GRAY);
    // Header Text
    DrawText("Skilltree", Game::ScreenWidth/2-100,110, 30, BLACK);
    // Skill Text
    DrawText("Left arm", Game::ScreenWidth/2-200,Game::ScreenWidth/2-50, 25, BLACK);
    DrawText("Right arm", Game::ScreenWidth/2-100,Game::ScreenWidth/2-50, 25, BLACK);
    DrawText("Left leg", Game::ScreenWidth/2-50,Game::ScreenWidth/2-50, 25, BLACK);
    DrawText("Right leg", Game::ScreenWidth/2+50,Game::ScreenWidth/2-50, 25, BLACK);
    DrawText("Left Eye", Game::ScreenWidth/2+100,Game::ScreenWidth/2-50, 25, BLACK);
    DrawText("Right Eye", Game::ScreenWidth/2+200,Game::ScreenWidth/2-50, 25, BLACK);

    Texture2D skillUnlockedImg = LoadTexture("../../assets/graphics/UI/Skilltree/SkillUnlocked.png");
    std::make_shared<Texture2D>(skillUnlockedImg);

    // Skill pictures
    Texture2D skillLeftArmImg = LoadTexture("../../assets/graphics/UI/Skilltree/SkillLeftArm.png");
    Texture2D skillRightArmImg = LoadTexture("../../assets/graphics/UI/Skilltree/SkillRightArm.png");
    Texture2D skillLeftLegImg = LoadTexture("../../assets/graphics/UI/Skilltree/SkillLeftLeg.png");
    Texture2D skillRightLegImg = LoadTexture("../../assets/graphics/UI/Skilltree/SkillRightLeg.png");
    Texture2D skillLeftEyeImg = LoadTexture("../../assets/graphics/UI/Skilltree/SkillLeftEye.png");
    Texture2D skillRightEyeImg = LoadTexture("../../assets/graphics/UI/Skilltree/SkillRightEye.png");

    /*std::shared_ptr<Texture2D> skillLeftArm = std::make_shared<Texture2D>(skillUnlockedImg);
    std::shared_ptr<Texture2D> skillRightArm = std::make_shared<Texture2D>(skillUnlockedImg);
    std::shared_ptr<Texture2D> skillLeftLeg = std::make_shared<Texture2D>(skillUnlockedImg);
    std::shared_ptr<Texture2D> skillRightLeg = std::make_shared<Texture2D>(skillUnlockedImg);
    std::shared_ptr<Texture2D> skillLeftEye = std::make_shared<Texture2D>(skillUnlockedImg);
    std::shared_ptr<Texture2D> skillRightEye = std::make_shared<Texture2D>(skillUnlockedImg);*/


    //DrawTexture(skillUnlockedImg,100,100, WHITE);

    /*
    for (int i = 1; i <= ; ++i) {
        if ( >0)
        {

        }else{

        }
            DrawTexture(skillUnlockedImg,100,100, WHITE);

    }
*/
}
