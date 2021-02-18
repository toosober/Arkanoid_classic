
#include "Config.h" //Файл конфига
#include "Levels.h" //Основаная логика уровней
#include "Menu.h"   //Файл с вступительным меню и 


int main()
{
    RenderWindow window(VideoMode(1100, 600), "Arkanoid");
    window.setVerticalSyncEnabled(0);

    

    Menu::GetInstance().CreateStartMenu(window);

    Levels lvs;

    while(window.isOpen())
        lvs.StartGame(window);

    return 0;
}


