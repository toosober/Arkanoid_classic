

#include "Config.h" 
#include "Menu.h"
#include "Levels.h"



int main()
{
    RenderWindow window(VideoMode(1100, 600), "Arkanoid");
    window.setVerticalSyncEnabled(1);
   

    //Menu::GetInstance().CreateStartMenu(window);

    Levels lvs;

    while(window.isOpen())
        lvs.StartGame(window);

    return 0;
}


