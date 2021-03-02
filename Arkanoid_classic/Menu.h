#pragma once

#include "Block.h"
#include "Border.h"
#include "Platform.h"


#pragma warning(disable : 4996); //ругаетс€ на устаревшую строку text.setColor(Color::Yellow)

class Menu //наивный одиночка
{
private:
	Menu();

	unsigned _scoreRecord = 0;
	unsigned _score = 0;
	int _lives = 0;
	

	unsigned _combo = 1;


	//–азличные текста
	Font _font;

	Text _textStartGame;
	Text _textScore;
	Text _textLevel;
	Text _textLives;
	Text _textGameOver;
	Text _textStopGame;


public:
	Menu(Menu& otner) = delete;
	void operator=(const Menu&) = delete;

	static Menu& GetInstance() //статическа€ функци€ инициализатор
	{
		static Menu menu_;
		return menu_;
	}

	void SetCountScore(int x) { _score += x; }
	const unsigned& GetCountScore() const { return _score; }

	void SetCountlives(int x) { _lives += x; }
	const int& GetCountlives() const { return _lives; }

	void SetScoreRecord() { if(_score > _scoreRecord) _scoreRecord = _score; }
	const unsigned GetScoreRecord() { return _scoreRecord; }

	void ResetCombo() { _combo = 1; }
	void IncreaseCombo() { _combo += 1; }
	const unsigned GetCombo() { return _combo; }




	

	void CreateStartMenu(RenderWindow& window);
	void CreateMenu(RenderWindow& window, unsigned level);
	void CreateStopGame(RenderWindow& window, std::list<Block*>& blocks, Border& board, ConcretePlatform* platform);
	void PlayerInit() { _score = 0; _lives = 3;}

	void CreateLevelSplashCreen(RenderWindow& window, Border& board, unsigned level);

	
};