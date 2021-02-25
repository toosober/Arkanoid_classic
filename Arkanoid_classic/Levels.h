

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

    Border _board;
    ConcretePlatform* _platform;
    

    unsigned _level;                 // Текущий номер уровня
    bool _changeLevel;              // Когда true собираем новый уровень
    
    std::list<Block*> _block;
    std::list<Block*>::iterator _blk;

    std::list<Bonus*> _bonus;
    std::list<Bonus*>::iterator _bns;

    std::list<Ball*> _ball;
    std::list<Ball*>::iterator _bl;
    bool _flagBallMove;				 // Флаг запуска шарика

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
    Levels();
    //~Levels() {  }

    int StartGame(RenderWindow& window);
    /*void SetChangeLevel(bool change) { change_level = change; }
    void CreateBonus(FloatRect blockPosition, BlockType blockType);*/

    void CollisionDetecter();

};

#endif