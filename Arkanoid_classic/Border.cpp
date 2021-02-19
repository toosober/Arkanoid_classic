
#include "Border.h"

Border::Border()
{
	image.loadFromFile(IMGPATH);
	texture.loadFromImage(image);

	_leftTopCorner.setTexture(texture);
	_leftTopCorner.setTextureRect(sf::IntRect(CORNER_LEFT, CORNER_TOP, CORNER_WIDTH, CORNER_HEIGHT));

	_leftBottomCorner = _leftTopCorner;
	_leftBottomCorner.setRotation(-90.f);

	_rightTopCorner = _leftTopCorner;
	_rightTopCorner.setRotation(-180.f);

	_rightBottomCorner = _leftTopCorner;
	_rightBottomCorner.setRotation(-270.f);

	_horizontalWall.setTexture(texture);
	_horizontalWall.setTextureRect(sf::IntRect(WALL_LEFT, WALL_TOP, WALL_WIDTH, WALL_HEIGHT));

	_verticalWall = _horizontalWall;	
	_verticalWall.setRotation(90.f);
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

sf::Sprite Border::GetVerticalWall(int posX, int posY)
{
	_verticalWall.setPosition(posX, posY);
	return _verticalWall;
}

sf::Sprite Border::GetHorizontalWall(int posX, int posY)
{
	_horizontalWall.setPosition(posX, posY);
	return _horizontalWall;
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
				window.draw(this->GetHorizontalWall(31 * i, 0));
			else if (i == WIDTH_MAP - 1 && j == 0)
				window.draw(this->GetRightTopCorner((31 * i) - 4, 0));
			else if (j > 0 && i == 0)
				window.draw(this->GetVerticalWall(0, 29 * j));
			else if (j > 0 && i == WIDTH_MAP - 1)
				window.draw(this->GetVerticalWall(31 * i, 29 * j));
		}
	}
}

void Border::CreateMenu(RenderWindow& window)
{
	//Отрисовываем меню из тайликов
	   //В тайлах не выдержан размер, поэтому коэффициенты в некоторых местах
	   //подогнанны вручную...
	for (int i = (WIDTH_MAP); i < (WIDTH_MENU); i++)
	{
		for (int j = 0; j < HEIGHT_MENU; j++)
		{
			if (i == WIDTH_MAP && j == 0)
				window.draw(this->GetLeftTopCorner((i * 31), 0));
			else if (i < WIDTH_MENU - 1 && j == 0)
				window.draw(this->GetHorizontalWall(31 * i, 0));
			else if (i == WIDTH_MENU - 1 && j == 0)
				window.draw(this->GetRightTopCorner((31 * i) - 4, 0));
			else if (j > 0 && i == WIDTH_MAP && j < HEIGHT_MENU - 1)
				window.draw(this->GetVerticalWall(i * 31, 29 * j));
			else if (j > 0 && i == WIDTH_MENU - 1 && j < HEIGHT_MENU - 1)
				window.draw(this->GetVerticalWall(i * 31, 29 * j));
			else if (j == HEIGHT_MENU - 1 && i == WIDTH_MAP)
				window.draw(this->GetLeftBottomCorner((i * 31), (j * 29)));
			else if (j == HEIGHT_MENU - 1 && i == WIDTH_MENU - 1)
				window.draw(this->GetRightBottomCorner((i * 31) - 4, (j * 29)));
			else if (j == HEIGHT_MENU - 1 && i > WIDTH_MAP && i < WIDTH_MENU - 1)
				window.draw(this->GetHorizontalWall(31 * i, (j * 29 + 7)));
		}
	}
}





