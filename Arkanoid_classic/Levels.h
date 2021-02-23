

#ifndef _LEVELS_H
#define _LEVELS_H

#include "Config.h"
#include "Border.h"
#include "Ball.h"
#include "Platform.h"
#include "Block.h"
#include "Bonus.h"





class Levels
{

private:

    Border board;
    ConcretePlatform* platform;
    Ball ball;

    unsigned level;                 // Текущий номер уровня
    bool change_level;              // Когда true собираем новый уровень
    
    std::list<Block*> block;
    std::list<Block*>::iterator blk;

    //std::list<Bonus*> bonus;
    //std::list<Bonus*>::iterator bns;

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
    /*Levels() { level = 1; change_level = true; }
    ~Levels() {}*/

    int StartGame(RenderWindow& window);
    /*void SetChangeLevel(bool change) { change_level = change; }
    void CreateBonus(FloatRect blockPosition, BlockType blockType);*/

    void CollisionDetecter();

};

#endif