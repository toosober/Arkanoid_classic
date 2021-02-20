

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



void Ball::Move(double angleUnitCircleX, double angleUnitCircleY, float time, CreatorPlatform* creatorPlatform)
{
    // В этот блок попадаем при первой инициализации угла, на который вылетит шарик при нажатии клавиши space
    if (_flagInit)
    {
        _flagInit = false;
        _angleUnitCircle.x = angleUnitCircleX; // Координаты точки на единичной окружности (направление полета шарика)
        _angleUnitCircle.y = angleUnitCircleY;
    }

     _speed = Vector2f (_acceleration * time * _angleUnitCircle.x, _acceleration*time* _angleUnitCircle.y); //вектор полета шарика
    
    this->move(_speed); //вызываем стандартную функцию move от класса Sprite


    // После сдвига проверяем куда мы попали?

    // Проверяем пересечение с левой стенкой карты
    if (this->GetRect().left < BORDER_LEFT)
    {
        this->setPosition(BORDER_LEFT, this->getPosition().y);      //если вдруг перелетели правую стенку, то уснатавливаемся в самое крайнее возможное положение
        _angleUnitCircle.x = -_angleUnitCircle.x;                    //меняем направление на противоположное по х
    }

    //проверяем пересечение с правой стенкой
    if (this->GetRect().left+this->GetRect().width > BORDER_RIGHT)
    {
        //если вдруг перелетели правую стенку, то уснатавливаемся в самое крайнее возможное положение
        this->setPosition(BORDER_RIGHT-this->GetRect().width, this->getPosition().y);
        _angleUnitCircle.x = -_angleUnitCircle.x;          //меняем направление на противоположное по х
    }

    //проверяем пересечение с потолком
    if (this->getPosition().y < BORDER_TOP)
    {
        this->setPosition(this->getPosition().x, BORDER_TOP); //если вдруг перелетели потолок, то устанавливаемся в саоме крайнее возможное положение
        _angleUnitCircle.y = -_angleUnitCircle.y;    // меняем напрваления на противоположное, по y
    }

    // Проверяем столкновение с платформой
    if (this->GetRect().intersects(creatorPlatform->GetInstance()->GetRect()))
    {
        _angleUnitCircle = creatorPlatform->GetInstance()->CollisionWithBall(_angleUnitCircle, *this);
    }
    

    //если шарик упал
    if (this->getPosition().y > BORDER_BOTTOM)
    {
       // Menu::GetInstance().SetCountlives(-1);
        creatorPlatform = new CreatorMediumPlatform();
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

void Ball::SetSpeed(float acceleration)
{
    _acceleration = acceleration;
}

