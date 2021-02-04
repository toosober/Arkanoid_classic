#pragma once
#include "GameObject.h"
class Border
{
private:
	sf::Sprite _verticalWall;
	sf::Sprite _horizontalWall;
	sf::Sprite _leftTopCorner;
	sf::Sprite _leftBottomCorner;
	sf::Sprite _rightTopCorner;
	sf::Sprite _rightBottomCorner;
	sf::Sprite _map;

	GameObject* gmbj;

public:
	//конструторы
	Border(GameObject* gmbj);

	~Border() {}

	//переопределенные операторы
	Border operator=(const GameObject& gmbj) const {}
	Border operator+(const GameObject& gmbj) const {}

	//ћетоды
	sf::Sprite GetLeftTopCorner(int posX, int posY);
	sf::Sprite GetLeftBottomCorner(int posX, int posY);
	sf::Sprite GetRightTopCorner(int posX, int posY);
	sf::Sprite GetRightBottomCorner(int posX, int posY);
	sf::Sprite GetVerticalWall(int posX, int posY);
	sf::Sprite GetHorizontalWall(int posX, int posY);

	void GetImage();
};

