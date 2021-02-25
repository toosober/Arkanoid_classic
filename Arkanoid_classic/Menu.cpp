
#include "Menu.h"
#include "Ball.h"
#include "Platform.h"




Menu::Menu()
{
    if (font.loadFromFile(FONTPATH) == NULL)
        std::cout << "Font Error" << std::endl;

    text_startgame.setFont(font);
    text_startgame.setCharacterSize(55);
    text_startgame.setColor(Color::Red);
    text_startgame.setStyle(Text::Bold);

    text_stopgame.setFont(font);
    text_stopgame.setCharacterSize(55);
    text_stopgame.setColor(Color::Red);
    text_stopgame.setStyle(Text::Bold);
    
    text_score.setFont(font);
    text_score.setCharacterSize(35);
    text_score.setColor(Color::Yellow);
    text_score.setStyle(Text::Bold);
    text_score.setPosition(850, 40);

    text_level.setFont(font);
    text_level.setCharacterSize(35);
    text_level.setColor(Color::Yellow);
    text_level.setStyle(Text::Bold);

    text_lives.setFont(font);
    text_lives.setCharacterSize(35);
    text_lives.setColor(Color::Yellow);
    text_lives.setStyle(Text::Bold);
    text_lives.setPosition(850, 120);

    text_game_over.setFont(font);
    text_game_over.setCharacterSize(35);
    text_game_over.setColor(Color::Yellow);
    text_game_over.setStyle(Text::Bold);    
    text_level.setPosition(850, 200);

}

// Запуск стартового меню
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

    Text text_equal("=", font, 25);
    text_equal.setColor(Color::Red);

    Text text_or("or", font, 25);
    text_or.setColor(Color::Red);
    text_or.setPosition(338, 200);

    Text text_laserOnBoard("Laser on board", font, 25);
    text_laserOnBoard.setColor(Color::Red);
    text_laserOnBoard.setPosition(190, 396);

    Text text_platformCatchBall("Platform catch ball", font, 25);
    text_platformCatchBall.setColor(Color::Red);
    text_platformCatchBall.setPosition(190, 246);

    Text text_slowOrFastBall("Slow or Fast ball speed", font, 25);
    text_slowOrFastBall.setColor(Color::Red);
    text_slowOrFastBall.setPosition(190, 296);

    Text text_extraLife("Extra Life", font, 25);
    text_extraLife.setColor(Color::Red);
    text_extraLife.setPosition(190, 446);

    Text text_multiply("X 3", font, 25);
    text_multiply.setColor(Color::Red);
    text_multiply.setPosition(216, 344);
    
    MediumPlatform platform;
    Ball ball;
    Border board;

    //устанавливаем начальные позиции для элементов
    platform.setPosition(-25, 550);
    ball.setPosition(800, 534);
    text_startgame.setString("PRESS ENTER TO START");
    text_startgame.setPosition(120, 0);

    

    auto& score = Menu::GetInstance().GetCountScore();
    auto& lives = Menu::GetInstance().GetCountlives();
    auto& level = Menu::GetInstance().Getlevel();

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

            //реализуем событие однократного нажатия клавиши Enter
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

        if (text_startgame.getPosition().y <= 80)
            text_startgame.move(0, time * 0.2);


        window.clear();

        board.CreateMap(window);
        board.CreateMenu(window);

        text_score.setString("Score");

        text_lives.setString("Lives");

        text_level.setString("Round");

        for (int i = 0; i < 6; i++)
        {
            text_equal.setPosition(150, 196 + i * 50);
            window.draw(text_equal);
        }


        window.draw(text_multiply);
        window.draw(PrintBall);
        window.draw(text_slowOrFastBall);
        window.draw(text_platformCatchBall);
        window.draw(text_laserOnBoard);
        window.draw(text_or);
        window.draw(PrintPlatformSmall);
        window.draw(PrintPlatformLarge);
        window.draw(text_extraLife);
        window.draw(greenBonus);
        window.draw(blueBonus);
        window.draw(pinkBonus);
        window.draw(purpleBonus);
        window.draw(redBonus);
        window.draw(yellowBonus);

        window.draw(platform);
        window.draw(ball);
        window.draw(text_score);
        window.draw(text_lives);
        window.draw(text_level);
        window.draw(text_startgame);

        window.display();
    }
}

void Menu::CreateMenu(RenderWindow& window)
{
    std::ostringstream playerScore;
    std::ostringstream playerLives;
    std::ostringstream gameLevel;

    playerScore << score;
    playerLives << lives;
    gameLevel << level;

    text_score.setString("Score: " + playerScore.str());
    text_lives.setString("Lives: " + playerLives.str());
    text_level.setString("Level: " + gameLevel.str());

    window.draw(text_score);
    window.draw(text_lives);
    window.draw(text_level);
}

void Menu::CreateStopGame(RenderWindow& window, std::list<Block*>& blocks, Border& board)
{
    std::ostringstream Record;
    Record << scoreRecord;
    text_stopgame.setString("Game Over\n\nYour Record is: " + Record.str() + "\n\n" +
        "Press Enter to try again");
    text_stopgame.setPosition(100, -50);

    
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

            //реализуем событие однократного нажатия клавиши Enter
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Enter)
                {
                    isMenu = false;
                }
            }
        }

       ///* if (platform.getPosition().x < 1300)
       //     platform.move(time * 1.5, 0);*/
       // else
       //     platform.setPosition(1300, 550);

        for (blks = blocks.begin(); blks != blocks.end(); blks++)
        {
            if ((*blks)->getPosition().x > -50)
                (*blks)->move(time * -1.5, 0);
            else
                (*blks)->setPosition(-50, 25);
        }

        if (text_stopgame.getPosition().y < 100)
            text_stopgame.move(0, time * 0.5);
        else
            text_stopgame.setPosition(text_stopgame.getPosition().x, 100);
        
        text_score.setString("Score");
        text_lives.setString("Lives");
        text_level.setString("Round");

        window.clear();

        board.CreateMap(window);
        board.CreateMenu(window);

        for (blks = blocks.begin(); blks != blocks.end(); blks++)
            window.draw(**blks);

        //window.draw(platform);        
        window.draw(text_score);
        window.draw(text_lives);
        window.draw(text_level);
        window.draw(text_stopgame);

        window.display();
    }
}