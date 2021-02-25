
#include "Bonus.h"


Bonus::Bonus(BlockType blockType, Vector2f startPosition) : _bonusType(blockType)
{
    this->setTexture(_texture);
    this->setPosition(startPosition);
   
    switch (_bonusType)
    {
    case BLUE:
        this->setTextureRect(sf::IntRect(BLUE_BONUS_LEFT, BLUE_BONUS_TOP, BONUS_WIDTH, BONUS_HEIGHT));
        break;
    case GREEN:
        this->setTextureRect(sf::IntRect(GREEN_BONUS_LEFT, GREEN_BONUS_TOP, BONUS_WIDTH, BONUS_HEIGHT));
        break;    
    case PINK:
        this->setTextureRect(sf::IntRect(PINK_BONUS_LEFT, PINK_BONUS_TOP, BONUS_WIDTH, BONUS_HEIGHT));
        break;
    case PURPLE:
        this->setTextureRect(sf::IntRect(PURPLE_BONUS_LEFT, PURPLE_BONUS_TOP, BONUS_WIDTH, BONUS_HEIGHT));
        break;
    case RED:
        this->setTextureRect(sf::IntRect(RED_BONUS_LEFT, RED_BONUS_TOP, BONUS_WIDTH, BONUS_HEIGHT));
        break;
    case YELLOW:
        this->setTextureRect(sf::IntRect(YELLOW_BONUS_LEFT, YELLOW_BONUS_TOP, BONUS_WIDTH, BONUS_HEIGHT));
        break;
    default:
        throw ("invalid argument bonusType");
        break;
    }
}

void Bonus::Move(float time)
{
    this->move(0, _speedFall * time);
}

void Bonus::CollisionWithPlatform(std::list<Ball*>& ball)
{
    switch (_bonusType)
    {
    case BLUE:
 //       ChangePlatform(platform); // Увеличиваем или уменьшаем платформу
        break;
    case RED:
//        LaserOnBoard(platform);  // Устанавливаем лазер на платформу
        break;
        
    case PURPLE:
        MultipleBall(ball); // Из каждого шарика в игре вылетает еще два шарика
        break;
    case PINK:
 //       ChangeSpeedBall(ball); // Ускоряем или замедляем шарик(и)
        break;
    case GREEN:
//        CatchBall(ball);    // Если шарик на экране остался один, он приклеивается к платформе
        break;
    case YELLOW:
        void AddLive();		// Этот бонус добавляет одну жизнь игроку
        break;
    default:
        throw("invalid _bonusType");
        break;
    }
}

 
 





void Bonus::MultipleBall(std::list<Ball*>& ball)
{
    std::list<Ball*>::iterator bl;
    std::list<Ball*>::iterator tempIt;
    unsigned ballCounter = Ball::GetBallCount();
    
    Vector2f angleUnitCircle;
    
    bl = ball.begin();

    while (ballCounter > 0 && bl != ball.end())
    {
        ball.push_back(new Ball((*bl)->GetSpeed(), false));
        tempIt = ball.end();
        tempIt--;
        (*tempIt)->setPosition((*bl)->getPosition());
        angleUnitCircle.x = (*bl)->GetAngleUnitCircle().x + 0.2;
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
        if ((*bl)->GetAngleUnitCircle().y < 0)
        {
            angleUnitCircle.y = -angleUnitCircle.y;
        }
        (*tempIt)->SetAngleUnitCircle(angleUnitCircle);

        ball.push_back(new Ball((*bl)->GetSpeed(), false));
        tempIt = ball.end();
        tempIt--;
        (*tempIt)->setPosition((*bl)->getPosition());
        angleUnitCircle.x = (*bl)->GetAngleUnitCircle().x - 0.2;
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
        if ((*bl)->GetAngleUnitCircle().y < 0)
        {
            angleUnitCircle.y = -angleUnitCircle.y;
        }
        (*tempIt)->SetAngleUnitCircle(angleUnitCircle);

        ballCounter--;
        bl++;
    }


}


void ChangePlatform(Platform* platform)
{

}

void LaserOnBoard(Platform* platform)
{

}

//void ChangeSpeedBall(std::list<Ball*>& ball)
//{

//}

//void CatchBall(std::list<Ball*>& ball)
//{

//}

void AddLive()
{

}