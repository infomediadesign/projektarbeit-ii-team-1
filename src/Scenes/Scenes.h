//
// Created by Munchkin on 24.05.2022.
//

#pragma once
#include "../Actors/enums.h"

class Scenes {

    // Attributes
public:
    bool switchScene;
    GameScreen switchTo;
    bool drawLevelBackground = false;

    // Methods
public:
    virtual void Update();
    virtual void Draw();

protected:
    virtual void CustomUpdate() = 0;
    virtual void CustomDraw() = 0;

};
