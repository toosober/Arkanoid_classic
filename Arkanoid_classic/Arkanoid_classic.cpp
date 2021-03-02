

#include "Config.h" 
#include "Menu.h"
#include "Levels.h"



int main()
{
    RenderWindow window(VideoMode(1100, 600), "Arkanoid");
    window.setVerticalSyncEnabled(0);

    Image image;
    image.loadFromFile(IMGPATH);
    
    Menu::GetInstance();
    Levels lvs(image);

    while(window.isOpen())
        lvs.StartGame(window);
        
    
    return 0;
}


