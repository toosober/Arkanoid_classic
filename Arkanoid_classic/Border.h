#pragma once

#include "GameObject.h"

class Border
{
private:
	Image image;
	Texture texture;
	//тайлы границ (углы и стены)
	Sprite _verticalWall;
	Sprite _horizontalWall;
	Sprite _leftTopCorner;
	Sprite _leftBottomCorner;
	Sprite _rightTopCorner;
	Sprite _rightBottomCorner;

	
	


public:
	//конструторы
	Border();
	Border(const Border&) = delete;

	~Border() {}

	//переопределенные операторы
	Border operator=(const GameObject& gmbj) const = delete;
	Border operator+(const GameObject& gmbj) const = delete;

	//Методы получения картинок стенок карты
	Sprite GetLeftTopCorner(int posX, int posY);
	Sprite GetLeftBottomCorner(int posX, int posY);
	Sprite GetRightTopCorner(int posX, int posY);
	Sprite GetRightBottomCorner(int posX, int posY);
	Sprite GetVerticalWall(int posX, int posY);
	Sprite GetHorizontalWall(int posX, int posY);

	void CreateMap(RenderWindow& window);
	void CreateMenu(RenderWindow& window);


};

