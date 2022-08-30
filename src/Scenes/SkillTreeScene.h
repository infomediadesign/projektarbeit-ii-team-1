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

public:
    std::shared_ptr<Player> player;
    std::vector<Vector2> skillPos ={Vector2 {10,11}, Vector2 {12,13},
                                    Vector2{14,15}, Vector2 {16,17}};
    Font font1;


    SkillTreeScene(std::shared_ptr<Player> player);
    void CustomUpdate() override;
    void CustomDraw() override;

    void DrawSkillTree ();
};

