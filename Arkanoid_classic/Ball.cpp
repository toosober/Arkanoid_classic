

#include "Ball.h"
#include "Menu.h"



Ball::Ball(float acceleration)    
{   
    this->setTexture(_texture);
    this->setTextureRect(sf::IntRect(BLUE_BALL_LEFT, BLUE_BALL_TOP, BLUE_BALL_WIDTH, BLUE_BALL_HEIGHT));
   _acceleration = acceleration;
   _flagInit = true;
   _flagMove = false;
}



void Ball::Move(double angleUnitCircleX, double angleUnitCircleY, float time)
{
    // В этот блок попадаем при первой инициализации угла, на который вылетит шарик при нажатии клавиши space
    if (_flagInit)
    {
        _flagInit = false;
        _angleUnitCircle.x = angleUnitCircleX; // Координаты точки на единичной окружности (направление полета шарика)
        _angleUnitCircle.y = angleUnitCircleY;
    }

     _speed = Vector2f (_acceleration * time * _angleUnitCircle.x, _acceleration*time* _angleUnitCircle.y); // Вектор полета шарика
    
    this->move(_speed); // Вызываем стандартную функцию move от класса Sprite


    // После сдвига проверяем куда мы попали?    
    

    // Если шарик упал (на этот случай нужно сделать отдельную функцию!!!)
    if (this->getPosition().y > BORDER_BOTTOM)
    {
       // Menu::GetInstance().SetCountlives(-1);
        /*creatorPlatform = new CreatorMediumPlatform();*/
        this->SetFlagInit(true);
        this->SetFlagMove(false);
    }

}


// Увеличиваем скорость шарика в два раза
void Ball::SetSpeedFast()
{
    _acceleration *= 2;
}

// Уменьшаем скорость шарика в два раза
void Ball::SetSpeedSlow()
{
    _acceleration /= 2;
}


// Устанавливаем скорость вручную (функция будет нужна, когда буду делать бонусы)
void Ball::SetSpeed(float acceleration)
{
    _acceleration = acceleration;
}

