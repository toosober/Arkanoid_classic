

#include "Config.h" 
#include "Menu.h"
#include "Levels.h"




int main()
{
    RenderWindow window(VideoMode(1100, 600), "Arkanoid");
    window.setVerticalSyncEnabled(0);

    Image image;
    image.loadFromFile(IMGPATH);

    Music music;                                            //создаем объект музыки
    music.openFromFile("MusicAndSounds/Stupid_Dancer.wav"); //загружаем файл
    music.play();                                           //
    
    Menu::GetInstance();
    Levels lvs(image);

    while(window.isOpen())
        lvs.StartGame(window);
        
    
    return 0;
}


