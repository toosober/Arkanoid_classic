#include "Menu.h"
#include "Border.h"


Menu::Menu()
{
    if (font.loadFromFile("Fonts/Neucha/Neucha-Regular.ttf") == NULL)
        std::cout << "Font Error" << std::endl;

    text_startgame.setFont(font);
    text_startgame.setCharacterSize(55);
    text_startgame.setColor(Color::Red);
    text_startgame.setStyle(Text::Bold);


    text_score.setFont(font);
    text_score.setCharacterSize(35);
    text_score.setColor(Color::Yellow);
    text_score.setStyle(Text::Bold);


    text_level.setFont(font);
    text_level.setCharacterSize(35);
    text_level.setColor(Color::Yellow);
    text_level.setStyle(Text::Bold);

    text_lives.setFont(font);
    text_lives.setCharacterSize(35);
    text_lives.setColor(Color::Yellow);
    text_lives.setStyle(Text::Bold);

    text_game_over.setFont(font);
    text_game_over.setCharacterSize(35);
    text_game_over.setColor(Color::Yellow);
    text_game_over.setStyle(Text::Bold);

}

// Запуск стартового меню
void Menu::CreateStartMenu(RenderWindow& window, Platform& platform, Balls& ball, Border& board)
{
    //устанавливаем начальные позиции для элементов
    platform.setPosition(-25, 550);
    ball.setPosition(800, 534);
    text_startgame.setString("PRESS ENTER TO START");
    text_startgame.setPosition(120, 0);

    text_score.setPosition(850, 40);
    text_lives.setPosition(850, 120);
    text_level.setPosition(850, 200);

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

        if (ball.getPosition().x > platform.getPosition().x + 56)
            ball.move(time * -0.5, 0);
        else
            ball.setPosition(platform.getPosition().x + 56, platform.getPosition().y - 16);

        if (text_startgame.getPosition().y <= 80)
            text_startgame.move(0, time * 0.2);


        window.clear();

        board.CreateMap(window);
        board.CreateMenu(window);

        text_score.setString("Score");

        text_lives.setString("Lives");

        text_level.setString("Round");

        window.draw(platform);
        window.draw(ball);
        window.draw(text_score);
        window.draw(text_lives);
        window.draw(text_level);
        window.draw(text_startgame);

        window.display();
    }
}