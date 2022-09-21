//
// Created by sefer on 20.09.2022.
//

#include "Note.h"

Note::Note(unsigned int id, Vector2 position) {
    this->levelPosition = position;
    this->type = itemNote;
    this->name = "Note";
    this->price = 0; // Cannot be bought
    this->upgraded = false;
    this->showInLevel = true;
    this->id = id;
    this->collisionBox.width = this->texture.width;
    this->collisionBox.height = this->texture.height;
    this->collisionBox.x = this->levelPosition.x;
    this->collisionBox.y = this->levelPosition.y;

    std::string tesxturePath= "assets/graphics/items/collectible/Note" + std::to_string(id)+".png";
    this->texture = LoadTexture(tesxturePath.c_str());
}

void Note::Draw() {

    DrawTextureRec(this->texture, this->collisionBox, this->levelPosition, WHITE);
}
