//
// Created by Munchkin on 24.05.2022.
//

#include "SkillTreeScene.h"


SkillTreeScene::SkillTreeScene(std::shared_ptr<Player> player)
{
    this->player = player;
    font1 = LoadFont("../../assets/graphics/ui/Habbo.ttf");
}

void SkillTreeScene::CustomUpdate()
{
    // TEST
    if(IsKeyPressed(KEY_ESCAPE))
    {
        switchTo = TESTSCENE;
        switchScene = true;
    }
    // TEST
}

void SkillTreeScene::CustomDraw()
{
    this->DrawSkillTree();
}

void SkillTreeScene::DrawSkillTree()
{
    // Draw basics, Background, Text
    ClearBackground(GRAY);

    // Header text
    const std::string skilltreeHeaderTxt = "SkillTree";
    const Vector2 inventoryTxtSize =  MeasureTextEx(font1, skilltreeHeaderTxt.c_str(), 2, 60);
    DrawTextEx( font1, skilltreeHeaderTxt.c_str(), {Game::ScreenWidth/2 - (inventoryTxtSize.x/4),110}, 60, 2, BLACK);

    // Close Inventory text
    const std::string escapeInventoryTxt = "Escape to close Skilltree";
    //const Vector2 escapeTxtSize =  MeasureTextEx(font1, escapeInventoryTxt.c_str(), 2, 30);
    DrawTextEx( font1, escapeInventoryTxt.c_str(), {20,20}, 30, 1, BLACK);

    //Skill Images and text
    /*DrawText("Left arm", 100,Game::ScreenHeight/2-100, 25, BLACK);
    DrawText("Right arm", 420,Game::ScreenHeight/2-100, 25, BLACK);
    DrawText("Left leg", 740,Game::ScreenHeight/2-100, 25, BLACK);
    DrawText("Right leg", 1060,Game::ScreenHeight/2-100, 25, BLACK);
    DrawText("Left Eye", 1380,Game::ScreenHeight/2-100, 25, BLACK);
    DrawText("Right Eye", 1700,Game::ScreenHeight/2-100, 25, BLACK);*/

    // Frame and arrow pictures
    Texture2D arrowImg = LoadTexture("../../assets/graphics/UI/Skilltree/Arrpw.png");
    Texture2D skillUnlockecImg = LoadTexture("../../assets/graphics/UI/Skilltree/SkillUnlocked.png");
    Texture2D skillLockedImg = LoadTexture("../../assets/graphics/UI/Skilltree/SkillLocked.png");

    // Skill pictures
    Texture2D skillLeftArmImg = LoadTexture("../../assets/graphics/UI/Skilltree/SkillLeftArm.png");
    Texture2D skillRightArmImg = LoadTexture("../../assets/graphics/UI/Skilltree/SkillRightArm.png");
    Texture2D skillLeftLegImg = LoadTexture("../../assets/graphics/UI/Skilltree/SkillLeftLeg.png");
    Texture2D skillRightLegImg = LoadTexture("../../assets/graphics/UI/Skilltree/SkillRightLeg.png");
    Texture2D skillLeftEyeImg = LoadTexture("../../assets/graphics/UI/Skilltree/SkillLeftEye.png");
    Texture2D skillRightEyeImg = LoadTexture("../../assets/graphics/UI/Skilltree/SkillRightEye.png");

    std::vector<Texture2D> skillImgs = {skillLeftArmImg, skillRightArmImg, skillLeftLegImg, skillRightLegImg, skillLeftEyeImg,skillRightEyeImg};
    std::vector<std::string> skillTxts = {"Left arm", "Right arm", "Left leg", "Right leg", "Left Eye", "Right Eye"};

    //DrawTextureEx(skillLeftArmImg, {75,Game::ScreenHeight/2}, 0, 0.5, WHITE);
    //DrawTextureEx(skillRightArmImg, {395,Game::ScreenHeight/2}, 0, 0.5, WHITE);
    //DrawTextureEx(skillLeftLegImg, {740,Game::ScreenHeight/2}, 0, 0.5, WHITE);
    //DrawTextureEx(skillRightLegImg, {1060,Game::ScreenHeight/2}, 0, 0.5, WHITE);
    //DrawTextureEx(skillLeftEyeImg, {1380,Game::ScreenHeight/2}, 0, 0.5, WHITE);
    //DrawTextureEx(skillRightEyeImg, {1700,Game::ScreenHeight/2}, 0, 0.5, WHITE);

    //DrawTextureEx(arrowImg, {150, Game::ScreenHeight/2}, 0, 0.5,WHITE);

    int skillDrawCount = 1;

    for (int i = 0; i < 6; ++i) {

        // ... unlocked skills
        if (player->augmentationCount >0 && skillDrawCount <= player->augmentationCount)
        {
            DrawTextEx(font1,skillTxts[i].c_str(), skillPos[i], 27, 0.2, BLACK);
            DrawTextureEx(skillImgs[i], {skillPos[i].x+20,skillPos[i].y+20}, 0, 0.5, WHITE);
            DrawTextureEx(skillUnlockecImg, {skillPos[i].x,skillPos[i].y}, 0, 2.5, WHITE);
            skillDrawCount ++;
        }

        // ... locked skills
        if (player->augmentationCount == 0 || (player->augmentationCount >0 && skillDrawCount > player->augmentationCount))
        {
            DrawTextEx(font1,skillTxts[i].c_str(), {skillPos[i].x+ (skillLockedImg.width*float(2.25)-float(MeasureText(skillTxts[i].c_str(), 27))),skillPos[i].y-50}, 27, 0.2, BLACK);
            DrawTextureEx(skillImgs[i], {skillPos[i].x+10,skillPos[i].y+10}, 0, 0.5, WHITE);
            DrawTextureEx(skillLockedImg, {skillPos[i].x,skillPos[i].y}, 0, 2.5, WHITE);
            skillDrawCount ++;
        }

    }
    //DrawTextureEx(skillLockedImg, {skillPos[0].x,skillPos[0].y}, 0, 3, WHITE);
}
