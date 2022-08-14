//
// Created by 22max on 28.07.2022.
//

#pragma once

#include "raylib.h"

struct CombatSheet
{
    Texture2D sheet; // The actual spritesheet
    int spriteCount; // Indicates how may sprites are on a spritesheet
    int delay;       // For attack-animations: Indicates how long the game will wait after starting an attack animation to play the reaction animation
};