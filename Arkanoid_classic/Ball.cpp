

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
    // ¬ этот блок попадаем при первой инициализации угла, на который вылетит шарик при нажатии клавиши space
    if (_flagInit)
    {
        _flagInit = false;
        _angleUnitCircle.x = angleUnitCircleX; //  оординаты точки на единичной окружности (направление полета шарика)
        _angleUnitCircle.y = angleUnitCircleY;
    }

     _speed = Vector2f (_acceleration * time * _angleUnitCircle.x, _acceleration*time* _angleUnitCircle.y); // ¬ектор полета шарика
    
    this->move(_speed); // ¬ызываем стандартную функцию move от класса Sprite


    // ѕосле сдвига провер€ем куда мы попали?

    // ѕровер€ем пересечение с левой стенкой карты
    if (this->GetRect().left < BORDER_LEFT)
    {
        this->setPosition(BORDER_LEFT, this->getPosition().y);      // ≈сли вдруг перелетели правую стенку, то уснатавливаемс€ в самое крайнее возможное положение
        _angleUnitCircle.x = -_angleUnitCircle.x;                    // ћен€ем направление на противоположное по х
    }

    // ѕровер€ем пересечение с правой стенкой
    if (this->GetRect().left+this->GetRect().width > BORDER_RIGHT)
    {
        // ≈сли вдруг перелетели правую стенку, то уснатавливаемс€ в самое крайнее возможное положение
        this->setPosition(BORDER_RIGHT-this->GetRect().width, this->getPosition().y);
        _angleUnitCircle.x = -_angleUnitCircle.x;          // ћен€ем направление на противоположное по х
    }

    // ѕровер€ем пересечение с потолком
    if (this->getPosition().y < BORDER_TOP)
    {
        this->setPosition(this->getPosition().x, BORDER_TOP); // ≈сли вдруг перелетели потолок, то устанавливаемс€ в саоме крайнее возможное положение
        _angleUnitCircle.y = -_angleUnitCircle.y;             // ћен€ем напрвалени€ на противоположное, по y
    }

    // Cтолкновение с платформой провер€ем и обрабатываем в классе Platform
    
    

    // ≈сли шарик упал (на этот случай нужно сделать отдельную функцию!!!)
    if (this->getPosition().y > BORDER_BOTTOM)
    {
       // Menu::GetInstance().SetCountlives(-1);
        /*creatorPlatform = new CreatorMediumPlatform();*/
        this->SetFlagInit(true);
        this->SetFlagMove(false);
    }

}


// ”величиваем скорость шарика в два раза
void Ball::SetSpeedFast()
{
    _acceleration *= 2;
}

// ”меньшаем скорость шарика в два раза
void Ball::SetSpeedSlow()
{
    _acceleration /= 2;
}


// ”станавливаем скорость вручную (функци€ будет нужна, когда буду делать бонусы)
void Ball::SetSpeed(float acceleration)
{
    _acceleration = acceleration;
}

