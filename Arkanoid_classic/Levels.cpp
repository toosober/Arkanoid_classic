
#include "Levels.h"



int Levels::StartGame(RenderWindow& window)
{
    Menu::GetInstance().PlayerInit(); // Начало игры, устанавливаем жизни игрока, номер уровня и количество очков.
    
    Border board;
    
    CreatorPlatform* creatorPlatform = new CreatorMediumPlatform(); // Через фабрику создаем игровую платформу
    creatorPlatform->SomeSetPosition(PLATFORM_START_POSITION);      // Устанавливаем стартовую позицию
    
    // Создаем шарик
    Ball ball(0.1);
    ball.setPosition(BALL_START_POSITION);
    
   
    //Инициализация случайного числа при помощи Вихря Мерсенна, нужен для того, чтобы при запуске шарика в начале игры
    //он полетел по случайной траектории
    std::random_device rd;
    std::mt19937 mersenne(rd());

    Vector2f angleUnitCircle; // Переменная в которой будет храниться направление движения шарика (вектор на единичной окружности)

    // Инициализируем переменную которая будет отдавать время и перезагружать его
    Clock clock;

    while (window.isOpen())
    {   
        // Блок обновления временной единицы 
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;

        // Обработка событий нажатий кнопок
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Выключаем игру если нажата клавиша Esc или крестик в правом верхнем углу
            if (event.type == sf::Event::Closed ||
                Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();

            // Реализуем событие однократного нажатия клавиши пробел
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Space)
                {
                    //здесь отдадим команду начала игры через булеву переменную ballIsMove;
                    if (!ball.GetFlagMove())
                    {
                        //Формируем начальное направление движения шарика при помощи единичной окружности
                        angleUnitCircle.x = ((mersenne() % 150) - 75) / 100;                        
                        angleUnitCircle.y = sqrt(1.0 - pow(angleUnitCircle.x, 2));

                        //не заходим в этот блок до следующей инициализации
                        ball.SetFlagMove(true);
                    }
                }
                if (event.key.code == Keyboard::X)
                {
                    ball.SetSpeedFast();
                }


                if (event.key.code == Keyboard::Z)
                {
                    ball.SetSpeedSlow();
                }
            }
        }

        //Движение платформы
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            //Двигаемся влево, пока координата х не станет меньше 25,
            //Это граница передвижения, если пересекли то устанавливаем позицию в последнее возможное положение
            creatorPlatform->SomeMove(-0.5, time);
            if (creatorPlatform->SomeGetRect().left < BORDER_LEFT)
            {   
                creatorPlatform->SomeSetPosition(Vector2f(BORDER_LEFT, PLATFORM_START_POSITION.y));
            }

        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            //Двигаемся влево, пока координата х не станет меньше 25,
            //Это граница передвижения, если пересекли то устанавливаем позицию в последнее возможное положение
            creatorPlatform->SomeMove(-0.5, time);
            if (creatorPlatform->SomeGetRect().left+ creatorPlatform->SomeGetRect().left > BORDER_RIGHT)
            {
                creatorPlatform->SomeSetPosition(Vector2f(BORDER_RIGHT-creatorPlatform->SomeGetRect().width, PLATFORM_START_POSITION.y));
            }
        }

        //Если игра началась запускаем движение шарика
        if (ball.GetFlagMove())
        {
            ball.Move(angleUnitCircle, time, creatorPlatform);
        }
        else
        {   //Если игра не началась, шарик привязан к середине платформы 
            ball.setPosition((creatorPlatform->SomeGetRect().left + (creatorPlatform->SomeGetRect().width/2)-(ball.GetRect().width/2)),
                creatorPlatform->SomeGetRect().top - ball.GetRect().height);
        }

        if (Menu::GetInstance().GetCountlives() <= 0)
        {
            Menu::GetInstance().SetScoreRecord();
            Menu::GetInstance().CreateStopGame(window, block, board);

            delete creatorPlatform;           
            return 0;
        }

        if (change_level) //если булева пременная = true необходимо собрать новый уровень
        {
            level = InitLevel(level);
            Menu::GetInstance().Setlevel(level);
            change_level = false;
        }

        window.clear();

        board.CreateMap(window);
        board.CreateMenu(window);

        Menu::GetInstance().CreateMenu(window);

        for (blk = block.begin(); blk != block.end(); blk++)
            window.draw(**blk);

        for (bns = bonus.begin(); bns != bonus.end(); bns++)
            window.draw(**bns);

        creatorPlatform->SomeDraw(window);

        
        window.draw(ball);

        window.display();


    }

    delete creatorPlatform;
    return 0;
}


void Levels::CreateBonus(FloatRect blockPosition, BlockType blockType)
{

}

int Levels::InitLevel(int lvl)
{
    switch (lvl)
    {
    case 1:
        return CreateLevel1();
        break;
    case 2:
        return CreateLevel2();
        break;
    default:
        break;
    }



}

int Levels::CreateLevel1()
{
    int positionX = 0; //отвечает за столбец
    int positionY = 0; //отвечает за ряд

    //Первый ряд
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 5 || i == 7)
        {
            block.push_back(new Block(YELLOW, true));  //создаем бонусные блоки
            blk = block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            blk--;                                                         //смещаемся на последний элемент.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
        else
        {
            block.push_back(new Block(YELLOW));
            blk = block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            blk--;                                                         //смещаемся на последний элемент.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
    }

    //Второй ряд
    positionY = 1;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 4 || i == 8)
        {
            block.push_back(new Block(GREEN, true));  //создаем бонусные блоки
            blk = block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            blk--;                                                         //смещаемся на последний элемент.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
        else
        {
            block.push_back(new Block(GREEN));
            blk = block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            blk--;                                                         //смещаемся на последний элемент.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
    }

    //третий ряд
    positionY = 2;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 3 || i == 9)
        {
            block.push_back(new Block(PINK, true));  //создаем бонусные блоки
            blk = block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            blk--;                                                         //смещаемся на последний элемент.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
        else
        {
            block.push_back(new Block(PINK));
            blk = block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            blk--;                                                         //смещаемся на последний элемент.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
    }

    //четвертый ряд
    positionY = 3;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 2 || i == 10)
        {
            block.push_back(new Block(PURPLE, true));                    //создаем бонусные блоки
            blk = block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            blk--;                                                         //смещаемся на последний элемент.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
        else
        {
            block.push_back(new Block(PURPLE));
            blk = block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            blk--;                                                         //смещаемся на последний элемент.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
    }

    //пятый ряд
    positionY = 4;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 1 || i == 11)
        {
            block.push_back(new Block(RED, true));  //создаем бонусные блоки
            blk = block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            blk--;                                                         //смещаемся на последний элемент.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
        else
        {
            block.push_back(new Block(RED));
            blk = block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            blk--;                                                         //смещаемся на последний элемент.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
    }
    //шестой ряд
    positionY = 5;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 0 || i == 12)
        {
            block.push_back(new Block(BLUE, true));  //создаем бонусные блоки
            blk = block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            blk--;                                                         //смещаемся на последний элемент.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
        else
        {
            block.push_back(new Block(BLUE));
            blk = block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            blk--;                                                         //смещаемся на последний элемент.
            (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
    }

    //седьмой ряд
    positionY = 6;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        block.push_back(new Block(ORANGE));
        blk = block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
        blk--;                                                         //смещаемся на последний элемент.
        (*blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
       
    }
   
    return 2;
}

int Levels::CreateLevel2()
{
    int color = 1;
    int positionX;
    int positionY;
    for (int i = 0; i < 7; i++)
    {
        positionX = i;
        for (int j = 0; j < color; j++)
        {
            block.push_back(new Block(GREEN));
            positionY = j;
            blk = block.end(); //итератор устанавливаем на адрес стоящий за последним элементом листа
            blk--; //смещаемся на последний элемент.
            (*blk)->setPosition(40 + j * 55, 60 + i * 23);
        }
        color += 2;
    }

    return 3;
}






