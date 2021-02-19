#pragma once


#include "Config.h"
#include "Block.h"
#include "Ball.h"
#include "Bonus.h"



class Levels
{

    unsigned level;
    bool change_level;
    Image image;
    std::list<Block*> block;
    std::list<Block*>::iterator blk;

    std::list<Bonus*> bonus;
    std::list<Bonus*>::iterator bns;

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
    void CreateBonus(FloatRect blockPosition, BlockType blockType);

};

