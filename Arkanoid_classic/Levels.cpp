
#include "Levels.h"


unsigned Ball::_ballCounter = 0;

Levels::Levels(Image& img) : _image(img)
{
    _platform = new ConcretePlatform(_image);
    _platform->GetInstance()->setPosition(PLATFORM_START_POSITION);

    _ball.push_back(new Ball(_image));
    _bl = _ball.begin();
    (*_bl)->setPosition(BALL_START_POSITION);

    _level = 1;
    _changeLevel = true;
    _flagBallMove = false;

    
   
    

}

Levels::~Levels()
{
    delete _platform;
    
    while (!_block.empty())
    {
        _blk = _block.begin();
        delete* _blk;
        _blk = _block.erase(_blk);
    }

    while (!_bonus.empty())
    {
        _bns = _bonus.begin();
        delete* _bns;
        _bns = _bonus.erase(_bns);
    }

    while (!_ball.empty())
    {
        _bl = _ball.begin();
        delete* _bl;
        _bl = _ball.erase(_bl);
    }
}



int Levels::StartGame(RenderWindow& window)
{
    Menu::GetInstance().CreateStartMenu(window);                        // Создаем стартовый экран
    Menu::GetInstance().CreateLevelSplashCreen(window, _board, _level); // Запускаем экран с заставкой уровня
    GameInit();                                                         // Приводим все элементы в стартовой полжожение
    Menu::GetInstance().PlayerInit();                                   // Начало игры, устанавливаем жизни игрока, и количество очков в начальные значения.
   

    //Инициализация случайного числа при помощи Вихря Мерсенна, нужен для того, чтобы при запуске шарика в начале игры
    //он полетел по случайной траектории
    std::random_device rd;
    std::mt19937 mersenne(rd());

    double angleUnitCircleX = 0;         // Переменные в которых будет храниться направление движения шарика (вектор на единичной окружности)
    double angleUnitCircleY = 0;         

    // Инициализируем переменную которая будет отдавать время и перезагружать его
    Clock clockForBullets;
    Clock clock;

    while (window.isOpen())
    {   
        // Блок обновления временной единицы 
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;

        float timeForBullet = clockForBullets.getElapsedTime().asMilliseconds();  // Заводим таймер для выпуска пуль

        //---------------------------------------------Обработка событий нажатия кнопок
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
                    // Здесь отдадим команду начала игры через булеву переменную _flagBallMove;
                    if (!_flagBallMove)
                    {
                        // Формируем начальное направление движения шарика при помощи единичной окружности
                        angleUnitCircleX = (mersenne() % 150);
                        angleUnitCircleX = (angleUnitCircleX - 75) / 100;
                        angleUnitCircleY = sqrt(1.0 - pow(angleUnitCircleX, 2));
                        angleUnitCircleY = -1 * abs(angleUnitCircleY);

                        // Не заходим в этот блок до следующей инициализации
                        _flagBallMove = true;

                        
                    }

                    for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
                    {   
                        if ((*_bl)->getPosition().y == _platform->GetInstance()->GetRect().top - BLUE_BALL_HEIGHT + 1)
                        {
                            (*_bl)->SetFlagCatch(false);
                            (*_bl)->SetFlagBallCatchPosition(false);
                        }
                    }                    
                }
                if (event.key.code == Keyboard::X)
                {
                    for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
                    {
                        (*_bl)->SetSpeedFast();
                    }
                    
                }


                if (event.key.code == Keyboard::Z)
                {
                     for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
                    {
                        (*_bl)->SetSpeedSlow();
                    }
                }

                if (event.key.code == Keyboard::F)
               {    
                    _platform->ChangePlatform(3);                    
               }
            }
        }


        //-------------------------------------------Создание дополнительных элементов

        // Если выбран бонус создания пуль, создаем пули
        if (_platform->GetInstance()->GetBullets() > 0)
        {
            if (timeForBullet > 1000)
            {
                _platform->GetInstance()->Fire();
                clockForBullets.restart();

                Bullets* tempBullet1 = new Bullets(_image);
                Bullets* tempBullet2 = new Bullets(_image);

                tempBullet1->setPosition(_platform->GetInstance()->GetRect().left, _platform->GetInstance()->GetRect().top +
                    _platform->GetInstance()->GetRect().height / 2 - BULLET_HEIGHT / 2);

                tempBullet2->setPosition(_platform->GetInstance()->GetRect().left + _platform->GetInstance()->GetRect().width - BULLET_WIDTH,
                    _platform->GetInstance()->GetRect().top + _platform->GetInstance()->GetRect().height / 2 - BULLET_HEIGHT / 2);


                _bullets.push_back(tempBullet1);
                _bullets.push_back(tempBullet2);

            }
        }


        //-------------------------------------------------Движение элементов

        // Движение платформы
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            // Двигаемся влево, пока координата х не станет меньше 25,
            // Это граница передвижения, если пересекли то устанавливаем позицию в последнее возможное положение
            _platform->GetInstance()->Move(-0.5, time);
            if (_platform->GetInstance()->GetRect().left < BORDER_LEFT)
            {   
                _platform->GetInstance()->setPosition(Vector2f(BORDER_LEFT, PLATFORM_START_POSITION.y));
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            // Двигаемся влево, пока координата х не станет меньше 25,
            // Это граница передвижения, если пересекли то устанавливаем позицию в последнее возможное положение
            _platform->GetInstance()->Move(0.5, time);
            if (_platform->GetInstance()->GetRect().left + _platform->GetInstance()->GetRect().width > BORDER_RIGHT)
            {
                _platform->GetInstance()->setPosition(Vector2f(BORDER_RIGHT - _platform->GetInstance()->GetRect().width, PLATFORM_START_POSITION.y));
            }
        }

        
        // Если игра началась запускаем движение шарика
        if (_flagBallMove)
        {
            for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
            (*_bl)->Move(angleUnitCircleX, angleUnitCircleY, time);
        }
        // Если игра не началась шарик привязан к платформе
        else
        {      
            // Первое условие: "х" шарика всегда по середине платформы
            _bl = _ball.begin();
            (*_bl)->setPosition((_platform->GetInstance()->GetRect().left +
                (_platform->GetInstance()->GetRect().width / 2) - ((*_bl)->GetRect().width / 2)),
                // Второе условие: "y" шарика всегда выше платформы на высоту шарика
                _platform->GetInstance()->GetRect().top - (*_bl)->GetRect().height);
        }

        // Двигаем бонусы
        for (_bns = _bonus.begin(); _bns != _bonus.end(); _bns++)
        {
            (*_bns)->Move(time);
        }

        // Двигаем пули
        for (_blts = _bullets.begin(); _blts != _bullets.end(); _blts++)
        {
            (*_blts)->Move(time);
        }

        
        // После всех перемещений проверяем столкновения
        CollisionDetecter();

        // Если жизни закончились выводим экран окончания игры, все переменные приводим к начальному значению
        if (Menu::GetInstance().GetCountlives() <= 0)
        {
            Menu::GetInstance().SetScoreRecord();
            Menu::GetInstance().CreateStopGame(window, _block, _board, _platform);
            Menu::GetInstance().PlayerInit();
            GameInit();

            _level = 1;
            _changeLevel = true;

            return 0;
        }

        if (_changeLevel) //если булева пременная = true необходимо собрать новый уровень
        {
            
            _level = InitLevel(_level);
            _changeLevel = false;

        }

        if (_block.empty())
        {
            _changeLevel = true;
            _level++;
            GameInit();
            Menu::GetInstance().CreateLevelSplashCreen(window, _board, _level);
        }

       


        window.clear();

        _board.CreateMap(window);
        _board.CreateMenu(window);
        
        Menu::GetInstance().CreateMenu(window, _level);

        for (_blk = _block.begin(); _blk != _block.end(); _blk++)
            window.draw(**_blk);

        for (_bns = _bonus.begin(); _bns != _bonus.end(); _bns++)
            window.draw(**_bns);

        for (_bl = _ball.begin(); _bl != _ball.end(); _bl++)
            window.draw(**_bl);

        for (_blts = _bullets.begin(); _blts != _bullets.end(); _blts++)
        {
            window.draw(**_blts);
        }
             
        window.draw(*_platform->GetInstance());
       
        window.display();


    }

    
    return 0;
}
//---------------------------------------------------------------Обработка коллизий
void Levels::CollisionDetecter()
{

   BallCollision(); // Проверяем столкновение шариков с границами карты

   PlatformCollision(); // Проверяем столкновения элементов игры с платформой

   BulletsCollision();  // Проверяем столкновения элементов игры с пулями

}

void Levels::BallCollision()
{
    for (_bl = _ball.begin(); _bl != _ball.end();)
    {
        // Проверяем пересечение шарика с левой стенкой карты
        if ((*_bl)->GetRect().left < BORDER_LEFT)
        {
            (*_bl)->setPosition(BORDER_LEFT, (*_bl)->getPosition().y);  // Если вдруг перелетели правую стенку, то уснатавливаемся в самое крайнее возможное положение
            (*_bl)->SetAngleUnitCircle(Vector2f(-(*_bl)->GetAngleUnitCircle().x, (*_bl)->GetAngleUnitCircle().y)); // Меняем направление на противоположное по х
        }

        // Проверяем пересечение с правой стенкой
        if ((*_bl)->GetRect().left + (*_bl)->GetRect().width > BORDER_RIGHT)
        {
            // Если вдруг перелетели правую стенку, то уснатавливаемся в самое крайнее возможное положение
            (*_bl)->setPosition(BORDER_RIGHT - (*_bl)->GetRect().width, (*_bl)->getPosition().y);
            (*_bl)->SetAngleUnitCircle(Vector2f(-(*_bl)->GetAngleUnitCircle().x, (*_bl)->GetAngleUnitCircle().y)); // Меняем направление на противоположное по х
        }

        // Проверяем пересечение с потолком
        if ((*_bl)->getPosition().y < BORDER_TOP)
        {
            (*_bl)->setPosition((*_bl)->getPosition().x, BORDER_TOP); // Если вдруг перелетели потолок, то устанавливаемся в саоме крайнее возможное положение
            (*_bl)->SetAngleUnitCircle(Vector2f((*_bl)->GetAngleUnitCircle().x, -(*_bl)->GetAngleUnitCircle().y)); // Меняем направление на противоположное по х
        }


        //----------------------------------------------------------------Проверяем столкновение шарика с платформой, (обрабатываем в классе Platform)
        if (_platform->GetInstance()->GetRect().intersects((*_bl)->GetRect()))
        {
            Menu::GetInstance().ResetCombo();

            if ((*_bl)->GetFlagCatch() && Ball::GetBallCount() == 1)
            {
                if (!(*_bl)->GetFlagBallCatchPosition())
                {
                    (*_bl)->SetCatchPositionX((*_bl)->getPosition().x - _platform->GetInstance()->GetRect().left);
                    (*_bl)->SetFlagBallCatchPosition(true);
                    (*_bl)->DecreaseCatchCounter();
                }

                (*_bl)->setPosition(_platform->GetInstance()->GetRect().left + (*_bl)->GetCatchPositionX(), _platform->GetInstance()->GetRect().top - BLUE_BALL_HEIGHT+1);
            }
            else
            {
                (*_bl)->SetAngleUnitCircle(_platform->GetInstance()->CollisionWithBall(**_bl));

                if ((*_bl)->GetCatchCounter() > 0)
                {
                    (*_bl)->SetFlagCatch(true);
                }
            }

            
        }

        //----------------------------------------------------------------Проверяем столкновение шарика с блоками, (обрабатываем в блкоах)

        for (_blk = _block.begin(); _blk != _block.end();)
        {
            if ((*_blk)->GetRect().intersects((*_bl)->GetRect()))
            {
                Menu::GetInstance().SetCountScore(10 * Menu::GetInstance().GetCombo());
                Menu::GetInstance().IncreaseCombo();
                (*_bl)->SetAngleUnitCircle((*_blk)->BallCollision(**_bl));
                if ((*_blk)->GetFlagBonus())
                {
                    _bonus.push_back(new Bonus(_image, (*_blk)->GetBlockType(), Vector2f((*_blk)->GetRect().left + (*_blk)->GetRect().width / 2 - BONUS_WIDTH / 2,
                        (*_blk)->getPosition().y)));
                }
                delete* _blk;
                _blk = _block.erase(_blk);
            }
            else
            {
                _blk++;
            }
        }


        // Если шарик упал 
        if ((*_bl)->getPosition().y > BORDER_BOTTOM)
        {
            BallFall();
        }
        else
        {
            _bl++;
        }
    }
}

void Levels::PlatformCollision()
{

//-------------------------------------------------------------------Проверяем столкновение бонуса с платформой (обрабатываем в платформе)
//---------------------------------------------------------------------------------------Если бонус достиг нижней границы карты, то удаляем его

    for (_bns = _bonus.begin(); _bns != _bonus.end();)
    {
        if ((*_bns)->GetRect().intersects(_platform->GetInstance()->GetRect()))
        {
            (*_bns)->CollisionWithPlatform(_platform, _ball);
            delete* _bns;
            _bns = _bonus.erase(_bns);
        }
        else if ((*_bns)->getPosition().y > BORDER_BOTTOM)
        {
            delete* _bns;
            _bns = _bonus.erase(_bns);

        }
        else
        {
            _bns++;
        }

    }
}

void Levels::BulletsCollision()
{
    for (_blts = _bullets.begin(); _blts != _bullets.end();)
    {
        if ((*_blts)->getPosition().y < BORDER_TOP)
        {
            delete* _blts;
            _blts = _bullets.erase(_blts);
            continue;
        }

    
        for (_blk = _block.begin(); _blk != _block.end();)
        {
            if ((*_blts)->GetRect().intersects((*_blk)->GetRect()))
            {
                if ((*_blk)->GetFlagBonus())
                {
                    _bonus.push_back(new Bonus(_image, (*_blk)->GetBlockType(), Vector2f((*_blk)->GetRect().left + (*_blk)->GetRect().width / 2 - BONUS_WIDTH / 2,
                        (*_blk)->getPosition().y)));
                }

                delete* _blk;
                _blk = _block.erase(_blk);

                delete* _blts;
                _blts = _bullets.erase(_blts);
                break;
            }
            else
            {
                _blk++;
            }
        } 

        if (!_bullets.empty() && _blts != _bullets.end())
        {
            _blts++;
        }
            
    }
}

//----------------------------------------------------------------Создание уровней

int Levels::InitLevel(int lvl)
{
    switch (lvl)
    {
    case 1:
        return CreateLevel4();
        break;
    case 2:
        return CreateLevel2();
        break;
    case 3:
        return CreateLevel3();
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
            _block.push_back(new Block(_image, YELLOW, true));  // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         //смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, YELLOW));
            _blk = _block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         //смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
    }

    //Второй ряд
    positionY = 1;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 4 || i == 8)
        {
            _block.push_back(new Block(_image, GREEN, true));  // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, GREEN));
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
    }

    //третий ряд
    positionY = 2;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 3 || i == 9)
        {
            _block.push_back(new Block(_image, PINK, true));  //создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, PINK));
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
    }

    // Четвертый ряд
    positionY = 3;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 2 || i == 10)
        {
            _block.push_back(new Block(_image, PURPLE, true));                    //создаем бонусные блоки
            _blk = _block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         //смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, PURPLE));
            _blk = _block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         //смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
    }

    // Пятый ряд
    positionY = 4;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 1 || i == 11)
        {
            _block.push_back(new Block(_image, RED, true));  //создаем бонусные блоки
            _blk = _block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         //смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, RED));
            _blk = _block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         //смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
    }
    //шестой ряд
    positionY = 5;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 0 || i == 12)
        {
            _block.push_back(new Block(_image, BLUE, true));  //создаем бонусные блоки
            _blk = _block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         //смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, BLUE));
            _blk = _block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         //смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
        }
    }

    //седьмой ряд
    positionY = 6;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        _block.push_back(new Block(_image, ORANGE));
        _blk = _block.end();                                            //итератор устанавливаем на адрес стоящий за последним элементом листа
        _blk--;                                                         //смещаемся на последний элемент.
        (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); //устанавливаем позицию блока
       
    }
   
    return 1;
}

int Levels::CreateLevel2()
{   
    int positionX = 0;
    int positionY = 0;

    // Первый ряд
    _block.push_back(new Block(_image, ORANGE));
    _blk = _block.end();                                             // Итератор устанавливаем на адрес стоящий за последним элементом листа
    _blk--;                                                          // Смещаемся на последний элемент.
    (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23);  // Устанавливаем позицию блока
    

    // Второй ряд
    positionY = 1;
    for (int i = 0; i < 3; i++)
    {
        positionX = i;
        if (i == 2)
        {
            _block.push_back(new Block(_image, PURPLE, true));              // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Cмещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, PURPLE));                    // Создаем обычные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
    }

    // Третий ряд
    positionY = 2;
    for (int i = 0; i < 5; i++)
    {
        positionX = i;
        if (i == 4)
        {
            _block.push_back(new Block(_image, PINK, true));                // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Cмещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, PINK));                      // Создаем обычные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
    }

    // Четвертый ряд
    positionY = 3;
    for (int i = 0; i < 7; i++)
    {
        positionX = i;
        if (i == 6)
        {
            _block.push_back(new Block(_image, YELLOW, true));              // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Cмещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, YELLOW));                    // Создаем обычные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
    }

    // Пятый ряд
    positionY = 4;
    for (int i = 0; i < 9; i++)
    {
        positionX = i;
        if (i == 8)
        { 
            _block.push_back(new Block(_image, RED, true));                 // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Cмещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, RED));                       // Создаем обычные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
    }

    // Шестой ряд
    positionY = 5;
    for (int i = 0; i < 11; i++)
    {
        positionX = i;
        if (i == 10)
        {
            _block.push_back(new Block(_image, BLUE, true));                // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Cмещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, BLUE));                      // Создаем обычные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
    }

    // Седьмой ряд
    positionY = 6;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 12)
        {
            _block.push_back(new Block(_image, GREEN, true));               // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Cмещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, GREEN));                     // Создаем обычные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
    }

    return 2;
}

int Levels::CreateLevel3()
{
    int positionX = 0;
    int positionY = 0;

    // Первый ряд
    positionY = 0;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 6)
        {
            _block.push_back(new Block(_image, PURPLE, true));              // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Cмещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, PURPLE));                    // Создаем обычные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
    }

    // Второй ряд
    positionY = 1;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 4 || i == 8)
        {
            _block.push_back(new Block(_image, GREEN, true));               // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Cмещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, GREEN));                     // Создаем обычные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
    }

    // Третий ряд
    positionY = 2;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 0 || i == 12)
        {
            _block.push_back(new Block(_image, YELLOW, true));                // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Cмещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, YELLOW));                      // Создаем обычные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
    }

    // Четвертый ряд
    positionY = 3;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 2 || i == 10)
        {
            _block.push_back(new Block(_image, BLUE, true));              // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Cмещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, BLUE));                    // Создаем обычные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
    }

    // Пятый ряд
    positionY = 4;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        {
            _block.push_back(new Block(_image, ORANGE));                       // Создаем обычные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
    }

    // Шестой ряд
    positionY = 5;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 4 || i == 8)
        {
            _block.push_back(new Block(_image, RED, true));                // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Cмещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, RED));                      // Создаем обычные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
    }

    // Седьмой ряд
    positionY = 6;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 6)
        {
            _block.push_back(new Block(_image, PINK, true));               // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Cмещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, PINK));                     // Создаем обычные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
    }

    return 3;
}

int Levels::CreateLevel4()
{
    int positionX = 0;
    int positionY = 0;

    // Первый ряд
    positionY = 0;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 6)
        {
            _block.push_back(new Block(_image, BLUE, true));                // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Cмещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }        
    }

    // Второй ряд
    positionY = 1;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i > 4 && i < 7)
        {
            _block.push_back(new Block(_image, RED));               // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Cмещаемся на последний элемент.
            (*_blk)->setPosition(67 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }        
    }

    // Третий ряд
    positionY = 2;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 6)
        {
            _block.push_back(new Block(_image, PINK, true));                // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Cмещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
        else if (i == 5 || i == 7)
        {
            _block.push_back(new Block(_image, PINK));                      // Создаем обычные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
    }

    // Четвертый ряд
    positionY = 3;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i > 3 && i < 8)
        {
            _block.push_back(new Block(_image, PURPLE));              // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Cмещаемся на последний элемент.
            (*_blk)->setPosition(67 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }        
    }

    // Пятый ряд
    positionY = 4;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 6 )
        {
            _block.push_back(new Block(_image, YELLOW, true));                // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Cмещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
        else if ((i > 3 && i < 6) || (i  > 6 && i < 9 ))
        {
            _block.push_back(new Block(_image, RED));                      // Создаем обычные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
    }

    // Шестой ряд
    positionY = 5;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        
        _block.push_back(new Block(_image, ORANGE));                // Создаем бонусные блоки
        _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
        _blk--;                                                         // Cмещаемся на последний элемент.
        (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
    }

    // Седьмой ряд
    positionY = 6;
    for (int i = 0; i < 13; i++)
    {
        positionX = i;
        if (i == 0 || i == 12)
        {
            _block.push_back(new Block(_image, GREEN, true));               // Создаем бонусные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Cмещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
        else
        {
            _block.push_back(new Block(_image, GREEN));                     // Создаем обычные блоки
            _blk = _block.end();                                            // Итератор устанавливаем на адрес стоящий за последним элементом листа
            _blk--;                                                         // Смещаемся на последний элемент.
            (*_blk)->setPosition(40 + positionX * 55, 40 + positionY * 23); // Устанавливаем позицию блока
        }
    }

    return 4;
}

// Инициализация стартовых значений игры

void Levels::GameInit()
{
    _platform->ChangePlatform(mediumPlatform);
    _platform->GetInstance()->ReSetBulltes();
    _platform->GetInstance()->setPosition(PLATFORM_START_POSITION);

    _flagBallMove = false;

    while (!_ball.empty())
    {
        _bl = _ball.begin();
        delete* _bl;
        _bl = _ball.erase(_bl);        
    }

    while (!_block.empty())
    {
        _blk = _block.begin();
        delete* _blk;
        _blk = _block.erase(_blk);
    }

    while (!_bonus.empty())
    {
        _bns = _bonus.begin();
        delete* _bns;
        _bns = _bonus.erase(_bns);
    }
    
    _ball.push_back(new Ball(_image));
    _bl = _ball.begin();
    (*_bl)->setPosition(BALL_START_POSITION);
}

void Levels::BallFall()
{
    if (Ball::GetBallCount() <= 1)
    {
        _flagBallMove = false;
        (*_bl)->SetFlagInit(true);
        _bl++;
        Menu::GetInstance().SetCountlives(-1);

        
    }
    else
    {
        delete* _bl;
        _bl = _ball.erase(_bl);
    }
}








