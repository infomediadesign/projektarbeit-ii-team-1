//
// Created by Munchkin on 24.05.2022.
//

#ifndef RAYLIBSTARTER_SKILLTREESCENE_H
#define RAYLIBSTARTER_SKILLTREESCENE_H

#include "MenuScenes.h"
#include "raylib.h"
#include "config.h"
#include "memory"
#include "vector"


class SkillTreeScene : public MenuScenes {

public:
    std::vector<Vector2> skillPos ={Vector2 {10,11}, Vector2 {12,13},
                                    Vector2{14,15}, Vector2 {16,17}};


    SkillTreeScene();
    void CustomUpdate() override;
    void CustomDraw() override;

    void DrawSkillTree ();
};


#endif //RAYLIBSTARTER_SKILLTREESCENE_H
