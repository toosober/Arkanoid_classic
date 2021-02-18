#pragma once


#include "Border.h"


class Levels
{

    unsigned level;
    bool change_level;
    Image image;
    std::list<Block*> blocks;
    std::list<Block*>::iterator blks;

   /* std::list<Bonus*> bonuses;
    std::list<Bonus*>::iterator bns;*/

    void GameInit();
    int InitLevel(int lvl);
    int CreateLevel1();
    int CreateLevel2();
    int CreateLevel3();
    int CreateLevel4();
    int CreateLevel5();
    int CreateLevel6();
    int CreateLevel7();





public:
    Levels() { level = 1; change_level = true; }
    ~Levels() {}

    int StartGame(RenderWindow& window);
    void SetChangeLevel(bool change) { change_level = change; }

};

