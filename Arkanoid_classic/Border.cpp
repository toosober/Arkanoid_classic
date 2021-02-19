#include "Config.h"
#include "Border.h"
#include <iostream>

Border::Border()
{
	image.loadFromFile(IMGPATH);
	texture.loadFromImage(image);

	_leftTopCorner.setTexture(texture);
	_leftTopCorner.setTextureRect(sf::IntRect(CORNER_LEFT, CORNER_TOP, CORNER_WIDTH, CORNER_HEIGHT));

	_leftBottomCorner.setTexture(texture);
	_leftBottomCorner.setTextureRect(sf::IntRect(CORNER_LEFT, CORNER_BOTTOM, CORNER_WIDTH, -CORNER_HEIGHT));

	_rightTopCorner.setTexture(texture);
	_rightTopCorner.setTextureRect(sf::IntRect(CORNER_RIGHT, CORNER_TOP, -CORNER_WIDTH, CORNER_HEIGHT));

	_rightBottomCorner.setTexture(texture);
	_rightBottomCorner.setTextureRect(sf::IntRect(CORNER_RIGHT, CORNER_BOTTOM, -CORNER_WIDTH, -CORNER_HEIGHT));

	_horizontalTopWall.setTexture(texture);
	_horizontalTopWall.setTextureRect(sf::IntRect(HORIZONTAL_WALL_LEFT, HORIZONTAL_WALL_TOP, HORIZONTAL_WALL_WIDTH, HORIZONTAL_WALL_HEIGHT));

	_horizontalBottomWall.setTexture(texture);
	_horizontalBottomWall.setTextureRect(sf::IntRect(HORIZONTAL_WALL_LEFT, HORIZONTAL_WALL_BOTTOM, HORIZONTAL_WALL_WIDTH, -HORIZONTAL_WALL_HEIGHT));
	
	_verticalLeftWall.setTexture(texture);
	_verticalLeftWall.setTextureRect(sf::IntRect(VERTICAL_WALL_LEFT, VERTICAL_WALL_TOP, VERTICAL_WALL_WIDTH, VERTICAL_WALL_HEIGHT));

	_verticalRightWall.setTexture(texture);
	_verticalRightWall.setTextureRect(sf::IntRect(VERTICAL_WALL_RIGHT, VERTICAL_WALL_TOP, -VERTICAL_WALL_WIDTH, VERTICAL_WALL_HEIGHT));
}


sf::Sprite Border::GetLeftTopCorner(int posX, int posY)
{
	_leftTopCorner.setPosition(posX, posY);
	return _leftTopCorner;
}

sf::Sprite Border::GetLeftBottomCorner(int posX, int posY)
{
	_leftBottomCorner.setPosition(posX, posY);
	return _leftBottomCorner;
}

sf::Sprite Border::GetRightTopCorner(int posX, int posY)
{
	_rightTopCorner.setPosition(posX, posY);
	return _rightTopCorner;
}

sf::Sprite Border::GetRightBottomCorner(int posX, int posY)
{
	_rightBottomCorner.setPosition(posX, posY);
	return _rightBottomCorner;
}

sf::Sprite Border::GetVerticalLeftWall(int posX, int posY)
{
	_verticalLeftWall.setPosition(posX, posY);
	return _verticalLeftWall;
}

sf::Sprite Border::GetVerticalRightWall(int posX, int posY)
{
	_verticalRightWall.setPosition(posX, posY);
	return _verticalRightWall;
}

sf::Sprite Border::GetHorizontalTopWall(int posX, int posY)
{
	_horizontalTopWall.setPosition(posX, posY);
	return _horizontalTopWall;
}

sf::Sprite Border::GetHorizontalBottomWall(int posX, int posY)
{
	_horizontalBottomWall.setPosition(posX, posY);
	return _horizontalBottomWall;
}

void Border::CreateMap(RenderWindow& window)
{
	//Отрисовываем игровое поле из тайликов
	   //В тайлах не выдержан размер, поэтому коэффициенты в некоторых местах
	   //подогнанны вручную...
	for (int i = 0; i < WIDTH_MAP; i++)
	{
		for (int j = 0; j < HEIGHT_MAP; j++)
		{
			if (i == 0 && j == 0)
				window.draw(this->GetLeftTopCorner(0, 0));
			else if (i < WIDTH_MAP - 1 && j == 0)
				window.draw(this->GetHorizontalTopWall(32 * i, 0));
			else if (i == WIDTH_MAP - 1 && j == 0)
				window.draw(this->GetRightTopCorner(32 * i, 0));
			else if (j > 0 && i == 0)
				window.draw(this->GetVerticalLeftWall(0, 30 * j));
			else if (j > 0 && i == WIDTH_MAP - 1)
				window.draw(this->GetVerticalRightWall(32 * i, 30 * j));
		}
	}
}

void Border::CreateMenu(RenderWindow& window)
{
	//Отрисовываем меню из тайликов
	   //В тайлах не выдержан размер, поэтому коэффициенты в некоторых местах
	   //подогнанны вручную...
	for (int i = WIDTH_MAP; i < WIDTH_MENU; i++)
	{
		for (int j = 0; j < HEIGHT_MENU; j++)
		{
			if (i == WIDTH_MAP && j == 0)
				window.draw(this->GetLeftTopCorner((32 * i), 0));
			else if (i < WIDTH_MENU - 1 && j == 0)
				window.draw(this->GetHorizontalTopWall(32 * i, 0));
			else if (i == WIDTH_MENU - 1 && j == 0)
				window.draw(this->GetRightTopCorner(32 * i, 0));
			else if (j > 0 && i == WIDTH_MAP && j < HEIGHT_MENU - 1)
				window.draw(this->GetVerticalLeftWall(32 * i, 30 * j));
			else if (j > 0 && i == WIDTH_MENU - 1 && j < HEIGHT_MENU - 1)
				window.draw(this->GetVerticalRightWall(32 * i, 30 * j));
			else if (j == HEIGHT_MENU - 1 && i == WIDTH_MAP)
				window.draw(this->GetLeftBottomCorner(32 * i, (30 * j)));
			else if (j == HEIGHT_MENU - 1 && i == WIDTH_MENU - 1)
				window.draw(this->GetRightBottomCorner(32 * i, 30 * j));
			else if (j == HEIGHT_MENU - 1 && i > WIDTH_MAP && i < WIDTH_MENU - 1)
				window.draw(this->GetHorizontalBottomWall(32 * i, 30 * j));
		}
	}
}





