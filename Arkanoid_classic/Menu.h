#pragma once

#include "Border.h"
#include <sstream>

#pragma warning(disable : 4996); //ругаетс€ на устаревшую строку text.setColor(Color::Yellow)

class Menu //наивный одиночка
{
private:
	Menu();

	unsigned score = 0;
	int lives = 0;
	unsigned level = 1;


	//–азличные текста
	Font font;

	Text text_startgame;
	Text text_score;
	Text text_level;
	Text text_lives;
	Text text_game_over;


public:
	Menu(Menu& otner) = delete;
	void operator=(const Menu&) = delete;

	static Menu& GetInstance() //статическа€ функци€ инициализатор
	{
		static Menu menu_;
		return menu_;
	}

	void SetCountScore(int x) { score += x; }
	const unsigned& GetCountScore() const { return score; }

	void SetCountlives(int x) { lives += x; }
	const int& GetCountlives() const { return lives; }

	void Setlevel(int x) { level += x; }
	const unsigned& Getlevel() const { return level; }

	void CreateStartMenu(Image& image, RenderWindow& window, Platform& platform, Balls& ball, Border& board);
	void CreateMenu();
};