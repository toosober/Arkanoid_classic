#pragma once


#include "Border.h"


class Levels
{

    unsigned level;
    bool change_level;
    Image image;
    std::list<Block*> blocks;
    std::list<Block*>::iterator blks;

    int InitLevel(int lvl);
    int CreateLevel1();
    int CreateLevel2();
    int CreateLevel3();
    int CreateLevel4();
    int CreateLevel5();
    int CreateLevel6();
    int CreateLevel7();





public:
    Levels(Image& img) { image = img; level = 1; change_level = true; }
    ~Levels() {}

    int StartGame(RenderWindow& window, Platform& platform, Balls& ball, Border& board);
    void SetChangeLevel(bool change) { change_level = change; }









};

