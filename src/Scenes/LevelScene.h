#ifndef RAYLIBSTARTER_LEVELSCENE_H
#define RAYLIBSTARTER_LEVELSCENE_H

#include "Scenes.h"
#include "../Actors/Enemies/Enemy.h"


#include <nlohmann/json.hpp>
#include <fstream>
#include "vector"


class LevelScene : public Scenes {
    private:
    ;
    public:
    std::vector<Enemy> listOfNPCs();

    LevelScene();

    void DrawMap();
    void CustomUpdate() override;
    void CustomDraw() override;
    protected:
    ;

};


#endif //RAYLIBSTARTER_LEVELSCENE_H
