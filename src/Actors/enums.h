//
// Created by Maximilian R�ck on 05.06.2022.
//

// This file shouldn't be in the Actors-Folder
// However, I've failed to find a way to include this file if it isn't

#pragma once

enum Direction
{
    up,
    down,
    left,
    right
};

enum GameState{Started, Paused, Stopped};
enum Level{Tutorial, Level01, Rooftop, VIP};