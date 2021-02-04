
#include  <random> //Для задания случайного направления полета шарика при первом его запуске с платформы
#include "GameObject.h"
#include "Border.h"

using namespace sf;

int main()
{
    //Инициализация игровой формы
    sf::RenderWindow window(sf::VideoMode(1100, 600), "Arkanoid", sf::Style::Close);
    window.setFramerateLimit(60);

    //создаем объект игровых объектов, там хранится ссылка на спрайты
    //и перевод картинки в текстуру
    GameObject gmbj("Images/Sprites_Arkanoid.png");

    //Блок отвечающий за карту
    Border board(&gmbj); //Класс хранящий нужные спрайты границ и свойства доступа к ним

    //Переменные отвечающие за количество тайликов
    //На данный момент тайлы вырезаны кустарным способом и поэтому отличаются по своему размеру
    //Поэтому карту нельзя создать автоматически приходится немного подгадывать с размером тайлов
    int horizontalSize = 26;
    int verticalSize = 22;
    int horizontalSizeMenu = horizontalSize + 9;
    int verticalSizeMenu = verticalSize - 2;

    //Инициализируем объект класса платформа
    Platform platform(&gmbj, 148, 302, 128, 31);
    platform.setPosition(320, 550);

    //Инициализируем объякт класса шарики и присваиваем ему начальную позицию на платформе
    Balls ball(&gmbj, 64, 128, 16, 16);
    ball.setPosition(376, 534);
    bool ballIsMove = false; //Переменная которая становится true когда игра начинается и шарик вылетает с платформы
    //Инициализация случайного числа при помощи Вихря Мерсенна, нужен для того, чтобы при запуске шарика в начале игры
    //он полетел по случайной траектории
    std::random_device rd;
    std::mt19937 mersenne(rd());
    int rand;



    //Инициализируем переменную которая будет отдавать время и перезагружать его
    Clock clock;


    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMilliseconds();
        clock.restart();
        time = time / 800;
        sf::Event event;
        while (window.pollEvent(event))
        {
            //выключаем игру если нажата клавиша Esc или крестик в правом верхнем углу
            if (event.type == sf::Event::Closed ||
                Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();

            //реализуем событие однократного нажатия клавиши пробел
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Space)
                {
                    //здесь отдадим команду начала игры через булеву переменную ballIsMove;
                    if (!ballIsMove)
                    {
                        rand = 25 + mersenne() % 620;
                        ball.SetStartPosition(ball.getPosition().x, ball.getPosition().y); //Разумеется нужно будет исправить на вектор и здесь и в классе или подумать над тем как брать эти данные напряму с getPosition
                        ballIsMove = true;
                    }
                }

            }
        }


        //Движение платформы
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            //Двигаемся влево, пока координата х не станет меньше 25,
            //Это граница передвижения, если пересекли то устанавливаем позицию в последнее возможное положение
            platform.move(-500 * time, 0);
            if (platform.getPosition().x < 25)
            {
                platform.setPosition(25, 550);
            }

        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            //Двигаемся влево, пока координата х не станет меньше 25,
            //Это граница передвижения, если пересекли то устанавливаем позицию в последнее возможное положение
            platform.move(500 * time, 0);
            if (platform.getPosition().x > 645)
            {
                platform.setPosition(645, 550);
            }
        }

        //Здесь логика движения шарика
        if (ballIsMove)
        {
            ball.Move(rand, 22, time);
        }
        else
        {   //Если игра не началась, мы привязаны к платформе
            ball.setPosition(platform.getPosition().x + 56, 534);
        }




        window.clear();


        //Отрисовываем игровое поле из тайликов
        //В тайлах не выдержан размер, поэтому коэффициенты в некоторых местах
        //подогнанны вручную...
        for (int i = 0; i < horizontalSize; i++)
        {
            for (int j = 0; j < verticalSize; j++)
            {
                if (i == 0 && j == 0)
                    window.draw(board.GetLeftTopCorner(0, 0));
                else if (i < horizontalSize - 1 && j == 0)
                    window.draw(board.GetHorizontalWall(31 * i, 0));
                else if (i == horizontalSize - 1 && j == 0)
                    window.draw(board.GetRightTopCorner((31 * i) - 4, 0));
                else if (j > 0 && i == 0)
                    window.draw(board.GetVerticalWall(0, 29 * j));
                else if (j > 0 && i == horizontalSize - 1)
                    window.draw(board.GetVerticalWall(31 * i, 29 * j));
            }
        }

        //Отрисовываем меню из тайликов
        //В тайлах не выдержан размер, поэтому коэффициенты в некоторых местах
        //подогнанны вручную...
        for (int i = (horizontalSize); i < (horizontalSizeMenu); i++)
        {
            for (int j = 0; j < verticalSizeMenu; j++)
            {
                if (i == horizontalSize && j == 0)
                    window.draw(board.GetLeftTopCorner((i * 31), 0));
                else if (i < horizontalSizeMenu - 1 && j == 0)
                    window.draw(board.GetHorizontalWall(31 * i, 0));
                else if (i == horizontalSizeMenu - 1 && j == 0)
                    window.draw(board.GetRightTopCorner((31 * i) - 4, 0));
                else if (j > 0 && i == horizontalSize && j < verticalSizeMenu - 1)
                    window.draw(board.GetVerticalWall(i * 31, 29 * j));
                else if (j > 0 && i == horizontalSizeMenu - 1 && j < verticalSizeMenu - 1)
                    window.draw(board.GetVerticalWall(i * 31, 29 * j));
                else if (j == verticalSizeMenu - 1 && i == horizontalSize)
                    window.draw(board.GetLeftBottomCorner((i * 31), (j * 29)));
                else if (j == verticalSizeMenu - 1 && i == horizontalSizeMenu - 1)
                    window.draw(board.GetRightBottomCorner((i * 31) - 4, (j * 29)));
                else if (j == verticalSizeMenu - 1 && i > horizontalSize && i < horizontalSizeMenu - 1)
                    window.draw(board.GetHorizontalWall(31 * i, (j * 29 + 7)));
            }
        }



        window.draw(platform);
        window.draw(ball);


        window.display();
    }

    return 0;
}


/*
Из нерешенного:
- Пока не понимаю как реализовать отражения от стенок и потолка, т.е. мы двигаемся по вектору нормали от
начальной точки в конечную, в конечной - мы должны отразиться от стены и полелеть дальше. Как долететь - понятно, как отразиться - пока нет
- Как определять столкновение с блоками, которые будут встречаться на пути? Как вообще обрабатывать отражения, которые будут встречаться при движении по нормали
от точки А в точку Б?
- Как сделать шарик во время начала игры дочерним к платфоре, т.е. пока не нажата клавиша пробел, чтобы шарик был заблокирован на платформе и двигался с ней вправо и влево
*/