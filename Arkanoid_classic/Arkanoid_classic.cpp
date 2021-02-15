
#include "GameObject.h"
#include "Border.h"
#include "Levels.h"
#include "Menu.h"


int main()
{
    RenderWindow window(VideoMode(1100, 600), "Arkanoid");
    window.setVerticalSyncEnabled(0);

    //путь к спрайтам и создание картинки
    //перевод картинки в текстуру
    string path("Images/Sprites_Arkanoid.png");
    Image image;
    if (!image.loadFromFile(path))
    {
        std::cout << "Image not found" << std::endl;
        EXIT_FAILURE;
    }

    //Блок отвечающий за карту
    Border board(image); //Класс хранящий нужные спрайты границ и свойства доступа к ним

    Platform platform(image, 148, 302, 128, 31);
    platform.setPosition(320, 550);

    //Инициализируем объект класса шарики и присваиваем ему начальную позицию на платформе
    Balls ball(image, 64, 128, 16, 16);
    ball.setPosition(376, 534);
    ball.SetSpeed(Vector2f(0.1, -0.1));

    Menu::GetInstance();

    Menu::GetInstance().CreateStartMenu(window, platform, ball, board);

    Levels lvs(image);
    lvs.StartGame(window, platform, ball, board);




    return 0;
}


