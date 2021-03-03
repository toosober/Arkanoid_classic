
#include "Menu.h"
#include "Ball.h"


Menu::Menu()
{
    if (_font.loadFromFile(FONTPATH) == NULL)
        std::cout << "Font Error" << std::endl;

    _textStartGame.setFont(_font);
    _textStartGame.setCharacterSize(55);
    _textStartGame.setColor(Color::Red);
    _textStartGame.setStyle(Text::Bold);
    
    _textStopGame.setFont(_font);
    _textStopGame.setCharacterSize(55);
    _textStopGame.setColor(Color::Red);
    _textStopGame.setStyle(Text::Bold);
        
    _textScore.setFont(_font);
    _textScore.setCharacterSize(35);
    _textScore.setColor(Color::Yellow);    
    _textScore.setStyle(Text::Bold);
    _textScore.setPosition(850, 40);


    _textLevel.setFont(_font);
    _textLevel.setCharacterSize(35);
    _textLevel.setColor(Color::Yellow);    
    _textLevel.setStyle(Text::Bold);
    _textLevel.setPosition(850, 200);


    _textLives.setFont(_font);
    _textLives.setCharacterSize(35);
    _textLives.setColor(Color::Yellow);    
    _textLives.setStyle(Text::Bold);
    _textLives.setPosition(850, 120);


    _textCongratulations.setFont(_font);
    _textCongratulations.setCharacterSize(35);
    _textCongratulations.setColor(Color::Yellow);
    _textCongratulations.setStyle(Text::Bold);
    

}

// «апуск стартового меню
void Menu::CreateStartMenu(RenderWindow& window)
{
    Image image;
    image.loadFromFile(IMGPATH);
    Texture texture;
    texture.loadFromImage(image);

    Sprite blueBonus;
    blueBonus.setTexture(texture);
    blueBonus.setTextureRect(IntRect(456, 449, 27, 30));
    blueBonus.setPosition(100, 200);

    Sprite PrintPlatformLarge;
    PrintPlatformLarge.setTexture(texture);
    PrintPlatformLarge.setTextureRect(IntRect(148, 302, 128, 31));
    PrintPlatformLarge.setPosition(190, 200);

    Sprite  PrintPlatformSmall;
    PrintPlatformSmall.setTexture(texture);
    PrintPlatformSmall.setTextureRect(IntRect(0, 302, 58, 31));
    PrintPlatformSmall.setPosition(378, 200);

    Sprite PrintBall;
    PrintBall.setTexture(texture);
    PrintBall.setTextureRect(IntRect(64, 128, 16, 16));
    PrintBall.setPosition(190, 353);

    Sprite greenBonus;
    greenBonus.setTexture(texture);
    greenBonus.setTextureRect(IntRect(488, 449, 27, 30));
    greenBonus.setPosition(100, 250);

    Sprite pinkBonus;
    pinkBonus.setTexture(texture);
    pinkBonus.setTextureRect(IntRect(520, 449, 27, 30));
    pinkBonus.setPosition(100, 300);

    Sprite purpleBonus;
    purpleBonus.setTexture(texture);
    purpleBonus.setTextureRect(IntRect(553, 449, 27, 30)); 
    purpleBonus.setPosition(100, 350);

    Sprite redBonus;
    redBonus.setTexture(texture);
    redBonus.setTextureRect(IntRect(456, 482, 27, 30));
    redBonus.setPosition(100, 400);

    Sprite yellowBonus;
    yellowBonus.setTexture(texture);
    yellowBonus.setTextureRect(IntRect(488, 481, 27, 30));
    yellowBonus.setPosition(100, 450);

    Text textEqual("=", _font, 25);
    textEqual.setColor(Color::Red);
    textEqual.setStyle(Text::Bold);

    Text textOr("or", _font, 25);
    textOr.setColor(Color::Red);
    textOr.setStyle(Text::Bold);
    textOr.setPosition(338, 200);

    Text textLaserOnBoard("Laser on board", _font, 25);
    textLaserOnBoard.setColor(Color::Red);
    textLaserOnBoard.setStyle(Text::Bold);
    textLaserOnBoard.setPosition(190, 396);

    Text textPlatformCatchBall("Platform catch ball", _font, 25);
    textPlatformCatchBall.setColor(Color::Red);
    textPlatformCatchBall.setStyle(Text::Bold);
    textPlatformCatchBall.setPosition(190, 246);

    Text textSlowOrFastBall("Slow or Fast ball speed", _font, 25);
    textSlowOrFastBall.setColor(Color::Red);
    textSlowOrFastBall.setStyle(Text::Bold);
    textSlowOrFastBall.setPosition(190, 296);

    Text textExtraLife("Extra Life", _font, 25);
    textExtraLife.setColor(Color::Red);
    textExtraLife.setStyle(Text::Bold);
    textExtraLife.setPosition(190, 446);

    Text textMultiply("X 3", _font, 25);
    textMultiply.setColor(Color::Red);
    textMultiply.setStyle(Text::Bold);
    textMultiply.setPosition(216, 344);
    
    MediumPlatform platform(image);
    Ball ball(image);
    Border board;

    //устанавливаем начальные позиции дл€ элементов
    platform.setPosition(-25, 550);
    ball.setPosition(800, 534);
    _textStartGame.setString("PRESS ENTER TO START");
    _textStartGame.setPosition(120, 0);

    

    auto& score = Menu::GetInstance().GetCountScore();
    auto& lives = Menu::GetInstance().GetCountlives();    

    Clock clock;

    bool isMenu = true;
    while (isMenu)
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;
        sf::Event event;
        while (window.pollEvent(event))
        {
            //выключаем игру если нажата клавиша Esc или крестик в правом верхнем углу
            if (event.type == sf::Event::Closed ||
                Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
                isMenu = false;
            }

            //реализуем событие однократного нажати€ клавиши Enter
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Enter)
                {
                    isMenu = false;
                }
            }
        }

        if (platform.getPosition().x < 320)
            platform.move(time * 0.5, 0);
        else
            platform.setPosition(320, 550);

        if (ball.getPosition().x > platform.getPosition().x + 37)
            ball.move(time * -0.5, 0);
        else
            ball.setPosition(platform.getPosition().x + 37, platform.getPosition().y - 16);

        if (_textStartGame.getPosition().y <= 80)
            _textStartGame.move(0, time * 0.2);


        window.clear();

        board.CreateMap(window);
        board.CreateMenu(window);

        _textScore.setString("Score");

        _textLives.setString("Lives");

        _textLevel.setString("Round");

        for (int i = 0; i < 6; i++)
        {
            textEqual.setPosition(150, 196 + i * 50);
            window.draw(textEqual);
        }


        window.draw(textMultiply);
        window.draw(PrintBall);
        window.draw(textSlowOrFastBall);
        window.draw(textPlatformCatchBall);
        window.draw(textLaserOnBoard);
        window.draw(textOr);
        window.draw(PrintPlatformSmall);
        window.draw(PrintPlatformLarge);
        window.draw(textExtraLife);
        window.draw(greenBonus);
        window.draw(blueBonus);
        window.draw(pinkBonus);
        window.draw(purpleBonus);
        window.draw(redBonus);
        window.draw(yellowBonus);

        window.draw(platform);
        window.draw(ball);
        window.draw(_textScore);
        window.draw(_textLives);
        window.draw(_textLevel);
        window.draw(_textStartGame);

        window.display();
    }
}

// ћеню в правой части игрового экрана
void Menu::CreateMenu(RenderWindow& window, unsigned level)
{
    std::ostringstream playerScore;
    std::ostringstream playerLives;
    std::ostringstream gameLevel;

    playerScore << _score;
    playerLives << _lives;
    gameLevel << level;

    _textScore.setString("Score: " + playerScore.str());
    _textLives.setString("Lives: " + playerLives.str());
    _textLevel.setString("Level: " + gameLevel.str());

    window.draw(_textScore);
    window.draw(_textLives);
    window.draw(_textLevel);
}


// ќкно запускаемое при поражении
void Menu::CreateStopGame(RenderWindow& window, std::list<Block*>& blocks, Border& board, ConcretePlatform* platform)
{
    std::ostringstream record;
    record << _scoreRecord;
    _textStopGame.setString("Game Over\n\nYour Record is: " + record.str() + "\n\n" +
        "Press Enter to try again");
    _textStopGame.setPosition(100, -50);

    
    std::list<Block*>::iterator blks;

    
    Clock clock;

    bool isMenu = true;
    while (isMenu)
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;
        sf::Event event;
        while (window.pollEvent(event))
        {
            //выключаем игру если нажата клавиша Esc или крестик в правом верхнем углу
            if (event.type == sf::Event::Closed ||
                Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
                isMenu = false;
            }

            //реализуем событие однократного нажати€ клавиши Enter
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Enter)
                {
                    isMenu = false;
                }
            }
        }

        if (platform->GetInstance()->getPosition().x < 1300)
            platform->GetInstance()->move(time * 1.5, 0);
        else
            platform->GetInstance()->setPosition(1300, 550);


        for (blks = blocks.begin(); blks != blocks.end();)
        {   
            if ((*blks)->getPosition().x > -50)
            {
                (*blks)->move(time * -1.5, 0);
                blks++;
            }                
            else
            {
                delete (*blks);
                blks = blocks.erase(blks);
            }
            
        }       

       
        if (_textStopGame.getPosition().y < 100)
            _textStopGame.move(0, time * 0.5);
        else
            _textStopGame.setPosition(_textStopGame.getPosition().x, 100);
       
        
        
        _textScore.setString("Score");
        _textLives.setString("Lives");
        _textLevel.setString("Round");

        window.clear();

        board.CreateMap(window);
        board.CreateMenu(window);

        for (blks = blocks.begin(); blks != blocks.end(); blks++)
            window.draw(**blks);

        window.draw(*platform->GetInstance());        
        window.draw(_textScore);
        window.draw(_textLives);
        window.draw(_textLevel);
        window.draw(_textStopGame);

        window.display();
    }
}

void Menu::CreateEndGame(RenderWindow& window, std::list<Block*>& blocks, Border& board, ConcretePlatform* platform)
{
    std::ostringstream record;
    record << _scoreRecord;
    std::ostringstream score;
    score << _score;

    _textCongratulations.setString("Congratulations\n\nYou Score is: " + score.str() + "\n\nYour Record is: " + record.str() + "\n\n" +
        "Press Enter to try again");
    _textCongratulations.setPosition(100, -50);


    std::list<Block*>::iterator blks;


    Clock clock;

    bool isMenu = true;
    while (isMenu)
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;
        sf::Event event;
        while (window.pollEvent(event))
        {
            //выключаем игру если нажата клавиша Esc или крестик в правом верхнем углу
            if (event.type == sf::Event::Closed ||
                Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
                isMenu = false;
            }

            //реализуем событие однократного нажати€ клавиши Enter
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Enter)
                {
                    isMenu = false;
                }
            }
        }

        if (platform->GetInstance()->getPosition().x < 1300)
            platform->GetInstance()->move(time * 1.5, 0);
        else
            platform->GetInstance()->setPosition(1300, 550);


        for (blks = blocks.begin(); blks != blocks.end();)
        {
            if ((*blks)->getPosition().x > -50)
            {
                (*blks)->move(time * -1.5, 0);
                blks++;
            }
            else
            {
                delete (*blks);
                blks = blocks.erase(blks);
            }

        }


        if (_textStopGame.getPosition().y < 100)
            _textStopGame.move(0, time * 0.5);
        else
            _textStopGame.setPosition(_textStopGame.getPosition().x, 100);



        _textScore.setString("Score");
        _textLives.setString("Lives");
        _textLevel.setString("Round");

        window.clear();

        board.CreateMap(window);
        board.CreateMenu(window);

        for (blks = blocks.begin(); blks != blocks.end(); blks++)
            window.draw(**blks);

        window.draw(*platform->GetInstance());
        window.draw(_textScore);
        window.draw(_textLives);
        window.draw(_textLevel);
        window.draw(_textStopGame);

        window.display();
    }
}

void Menu::CreateLevelSplashCreen(RenderWindow& window, Border& board, unsigned level)
{
    bool isOpen = true;

    Text textSPlashScreenLevel("Level ", _font, 60);
    textSPlashScreenLevel.setColor(Color::Yellow);
    textSPlashScreenLevel.setStyle(Text::Bold);
    textSPlashScreenLevel.setPosition(300, 250);

    std::ostringstream gameLevel;
    gameLevel << level;

    Clock clock;

    Clock clockIsOpen;

    while (isOpen)
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;

        float timeIsOpen = clockIsOpen.getElapsedTime().asMilliseconds();
        
        if (timeIsOpen > 3000)
        {
            isOpen = false;
            window.clear();
        }

        textSPlashScreenLevel.setString("Level " + gameLevel.str());

        window.clear();

        board.CreateMap(window);
        board.CreateMenu(window);

        window.draw(textSPlashScreenLevel);

        window.display();
            
    }

}