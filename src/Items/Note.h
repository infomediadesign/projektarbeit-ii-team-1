//
// Created by sefer on 20.09.2022.
//

#ifndef RAYLIBSTARTER_NOTE_H
#define RAYLIBSTARTER_NOTE_H

#pragma once
#include "Item.h"

class Note : Item{
private:;
public:
    unsigned int id;

    Note(unsigned int id, Vector2 position);
    void Draw();
protected:;
};


#endif //RAYLIBSTARTER_NOTE_H
