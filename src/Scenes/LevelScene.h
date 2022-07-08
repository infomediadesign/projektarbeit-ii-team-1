#ifndef RAYLIBSTARTER_LEVELSCENE_H
#define RAYLIBSTARTER_LEVELSCENE_H

#include "Scenes.h"

#include <nlohmann/json.hpp>
#include <fstream>


class LevelScene : Scenes {
    private:
    ;
    public:


    void LevelScene();

    void DrawMap();
    void Update();
    void Draw();
    protected:
    ;

};


#endif //RAYLIBSTARTER_LEVELSCENE_H
