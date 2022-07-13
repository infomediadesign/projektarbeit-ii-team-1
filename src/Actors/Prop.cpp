//
// Created by Maximilian R�ck on 05.06.2022.
//

#include "Prop.h"

#include <iostream>


void Prop::Update()
{
    std::cout << "[DEBUG] Updating prop" << std::endl;
}

void Prop::Draw()
{

}

std::string Prop::getName()
{
    return this->name;
}

void Prop::setName(std::string name_)
{
    this->name = name_;
}
