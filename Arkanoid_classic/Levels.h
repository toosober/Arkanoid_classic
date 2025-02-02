

#ifndef _LEVELS_H
#define _LEVELS_H

#include "Config.h"
#include "Border.h"
#include "Ball.h"
#include "Platform.h"
#include "Block.h"
#include "Bonus.h"
#include "Bullets.h"





class Levels
{

private:

    Image& _image;

    Border _board;
    ConcretePlatform* _platform;
    

    unsigned _level;                // ������� ����� ������    
    
    std::list<Block*> _block;
    std::list<Block*>::iterator _blk;

    std::list<Bonus*> _bonus;
    std::list<Bonus*>::iterator _bns;
    

    std::list<Ball*> _ball;
    std::list<Ball*>::iterator _bl;
    bool _flagBallMove;				 // ���� ������� ������

    
    
    std::list<Bullets*> _bullets;
    std::list<Bullets*>::iterator _blts;





    // ��������
    void CollisionDetecter();
    void BallCollision(); // ������������ ������������ ������ � ���������� ����
    void PlatformCollision(); // ������������ ������������ ��������� � ���������� ���� (����� ������������ � �������) 
    void BulletsCollision(); // ��� ��������� ������������ ���� � ���������� ����
    void BallFall();          // ����� ���� � spawn ����
    


    // �������� �������
    void GameInit();
    int InitLevel(int lvl);
    int CreateLevel1();
    int CreateLevel2();
    int CreateLevel3();
    int CreateLevel4();
    int CreateLevel5();
    int CreateLevel6();
    int CreateLevel7();
    int StartLevel(RenderWindow& window);

    
    

    







public:
    Levels(Image& img);
    ~Levels();

    int StartGame(RenderWindow& window);

};

#endif