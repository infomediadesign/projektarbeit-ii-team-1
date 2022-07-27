//
// Created by 22max on 27.07.2022.
//

#pragma once

#include "../Scenes/Scenes.h"

#include <memory>

class SceneManager {

    // Attributes
public:
    std::shared_ptr<Scenes> activeScene;
    // Methods
public:
    SceneManager();

    void Update();
    void Draw();
};
