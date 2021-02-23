
#include "Config.h"
#include "Block.h"


Block::Block(BlockType blockType, bool bonus)
{
    _bonus = bonus;
    _blockType = blockType;
    this->setTexture(_texture);

    if (_bonus)
    {
        switch (_blockType)
        {
        case BLUE:
            this->setTextureRect(sf::IntRect(BLUE_BONUS_BLOCK_LEFT, BLUE_BONUS_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case GREEN:
            this->setTextureRect(sf::IntRect(GREEN_BONUS_BLOCK_LEFT, GREEN_BONUS_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case ORANGE:
            this->setTextureRect(sf::IntRect(ORANGE_BLOCK_LEFT, ORANGE_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case PINK:
            this->setTextureRect(sf::IntRect(PINK_BONUS_BLOCK_LEFT, PINK_BONUS_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case PURPLE:
            this->setTextureRect(sf::IntRect(PURPLE_BONUS_BLOCK_LEFT, PURPLE_BONUS_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case RED:
            this->setTextureRect(sf::IntRect(RED_BONUS_BLOCK_LEFT, RED_BONUS_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case YELLOW:
            this->setTextureRect(sf::IntRect(YELLOW_BONUS_BLOCK_LEFT, YELLOW_BONUS_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        default:
            throw ("invalid argument blockType");
            break;
        }
    }
    else
    {
        switch (_blockType)
        {
        case BLUE:
            this->setTextureRect(sf::IntRect(BLUE_BLOCK_LEFT, BLUE_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case GREEN:
            this->setTextureRect(sf::IntRect(GREEN_BLOCK_LEFT, GREEN_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case ORANGE:
            this->setTextureRect(sf::IntRect(ORANGE_BLOCK_LEFT, ORANGE_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case PINK:
            this->setTextureRect(sf::IntRect(PINK_BLOCK_LEFT, PINK_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case PURPLE:
            this->setTextureRect(sf::IntRect(PURPLE_BLOCK_LEFT, PURPLE_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case RED:
            this->setTextureRect(sf::IntRect(RED_BLOCK_LEFT, RED_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        case YELLOW:
            this->setTextureRect(sf::IntRect(YELLOW_BLOCK_LEFT, YELLOW_BLOCK_TOP, BLOCK_WIDTH, BLOCK_HEIGHT));
            break;
        default:
            throw ("invalid argument blockType");
            break;
        }
    }



    
    
}

Vector2f Block::BallCollision(Vector2f angleUnitCircle, Ball& ball)
{
    float ballLeftX = ball.GetRect().left;                                        // Левый край шарика
    float ballRightX = ball.GetRect().left + ball.GetRect().width;                // Правый край ширка
    float ballTopY = ball.GetRect().top;                                          // Верх шарика
    float ballBottomY = ball.GetRect().top + ball.GetRect().height;               // Низ шарика
    float ballCenterX = ball.GetRect().left + (ball.GetRect().width / 2);         // Координаты центра шарика по х
    float ballCenterY = ball.GetRect().top + (ball.GetRect().height / 2);         // Координаты центра шарика по y

    float blockBottomY = this->GetRect().top + this->GetRect().height;             // Низ блока
    float blockTopY = this->GetRect().top;                                         // Верх блока
    float blockLeftX = this->GetRect().left;                                       // левый край блока
    float blockRightX = this->GetRect().left + this->GetRect().width;              // правый край блока
    


    // Столкновение с левым нижним углом
    if (ballCenterX < blockLeftX && ballCenterY > blockBottomY)                     // По х - центр шарика находится левее чем левый край блока,
    {                                                                               // а по y - центр шарика находится ниже чем низ блока      
        return BallCollisionLeftBottomCorner(angleUnitCircle, ball);
    }    
    // Столкновение с левым верхним углом
    else if (ballCenterX < blockLeftX && ballCenterY < blockTopY)                   // По х - центр шарика находится левее чем левый край блока                                                             
    {                                                                               // По y - центр шарика находится выше чем верх блока 
        return BallCollisionLeftTopCorner(angleUnitCircle, ball);
    }

    // Столкновение с правм верхним углом
    else if (ballCenterX > blockRightX && ballCenterY < blockTopY)                 // По х - центр шарика находится правее чем правый край блкоа                         
    {                                                                              // По y - центр шарика находится выше чем верх блока         
        return BallCollisionRightTopCorner(angleUnitCircle, ball);
    }

    // Столкновение с парвым нижним углом
    else if (ballCenterX > blockRightX && ballCenterY > blockBottomY)                // По х - центр находится правее чем правый край блока        
    {                                                                                // По у - центр находится ниже чем низ блока   
        return BallCollisionRightBottomCorner(angleUnitCircle, ball);
    }

    // Столкновение с низом
    else if (ballCenterX > blockLeftX && ballCenterX < blockRightX                   // Если по х находимся в диапазоне блока
        && ballBottomY > blockBottomY)                                               // И по y находимся ниже нижнего края
    {
        return BallCollisionBottomWall(angleUnitCircle, ball);
    }

    // Столкновение с верхом
    else if (ballCenterX > blockLeftX && ballCenterX < blockRightX                       // Если по х находимся в диапазоне блока
        && ballTopY < blockTopY)                                                         // И по y находимся выше верхнего края края
    {
        return BallCollisionBottomWall(angleUnitCircle, ball);
    }

    // Если находимся с левоой стороны
    else if (ballCenterY > blockTopY && ballCenterY < blockBottomY                      // Если по y находимся в диапазоне платформы
        && ballLeftX < blockLeftX)                                                      // И по х находимся слева
    {
        return BallCollisionBottomWall(angleUnitCircle, ball);
    }

    // Если находимся с правой стороны
    else if (ballCenterY > blockTopY && ballCenterY < blockBottomY                      // Если по y находимся в диапазоне платформы
        && ballRightX > blockRightX)                                                    // И по х находимся справа
    {
        return BallCollisionBottomWall(angleUnitCircle, ball);
    }
    else
    {
        return Vector2f(angleUnitCircle.x*0, angleUnitCircle.y*0);                      // Неизвестная ситуация, шарик остановится.
    }
}


Vector2f Block::BallCollisionRightBottomCorner(Vector2f angleUnitCircle, Ball& ball)
{
    // Если попали в этот угол то устанавливаемся в максимально возможное положение по 
    ball.setPosition(this->GetRect().left + BLOCK_WIDTH - BLUE_BALL_WIDTH / 2, this->GetRect().top + BLOCK_HEIGHT);

    //Если приземлились на блок практически прямо
    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
    {
        angleUnitCircle.x = 0.9;                                   //отлетаем налево
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
    }
    else 
    {
        angleUnitCircle.x = -angleUnitCircle.x;                     //отражаемся по х
        angleUnitCircle.y = abs(angleUnitCircle.y);                 //отражаемся по y только вниз                    
    }
    
    if (_bonus)
    {
        this->BonusCreate();
    }

    return angleUnitCircle;
}

Vector2f Block::BallCollisionLeftBottomCorner(Vector2f angleUnitCircle, Ball& ball)
{
    // Если попали в этот угол то устанавливаемся в максимально возможное положение по 
    ball.setPosition(this->GetRect().left + BLUE_BALL_WIDTH / 2, this->GetRect().top + BLOCK_HEIGHT);

    //Если приземлились на блок практически прямо
    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
    {
        angleUnitCircle.x = -0.9;                                   //отлетаем налево
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
    }
    else
    {
        angleUnitCircle.x = -angleUnitCircle.x;                     //отражаемся по х
        angleUnitCircle.y = abs(angleUnitCircle.y);                 //отражаемся по y только вниз                    
    }

    if (_bonus)
    {
        this->BonusCreate();
    }

    return angleUnitCircle;
}

Vector2f Block::BallCollisionRightTopCorner(Vector2f angleUnitCircle, Ball& ball)
{
    // Если попали в этот угол то устанавливаемся в максимально возможное положение по 
    ball.setPosition(this->GetRect().left + BLOCK_WIDTH - BLUE_BALL_WIDTH / 2, this->GetRect().top - BLUE_BALL_HEIGHT);

    //Если приземлились на блок практически прямо
    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
    {
        angleUnitCircle.x = 0.9;                                   //отлетаем налево
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
    }
    else
    {
        angleUnitCircle.x = -angleUnitCircle.x;                         //отражаемся по х
        angleUnitCircle.y = -1 * abs(angleUnitCircle.y);                 //отражаемся по y только вниз                    
    }

    if (_bonus)
    {
        this->BonusCreate();
    }

    return angleUnitCircle;
}

Vector2f Block::BallCollisionLeftTopCorner(Vector2f angleUnitCircle, Ball& ball)
{
    // Если попали в этот угол то устанавливаемся в максимально возможное положение по 
    ball.setPosition(this->GetRect().left + BLUE_BALL_WIDTH / 2, this->GetRect().top - BLUE_BALL_HEIGHT);

    //Если приземлились на блок практически прямо
    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
    {
        angleUnitCircle.x = -0.9;                                   //отлетаем налево
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
    }
    else
    {
        angleUnitCircle.x = -angleUnitCircle.x;                         //отражаемся по х
        angleUnitCircle.y = -1 * abs(angleUnitCircle.y);                 //отражаемся по y только вниз                    
    }

    if (_bonus)
    {
        this->BonusCreate();
    }

    return angleUnitCircle;
}

Vector2f Block::BallCollisionBottomWall(Vector2f angleUnitCircle, Ball& ball)
{
    // Если попали в это место то устанавливаемся в максимальное положение
    ball.setPosition(ball.getPosition().x, this->GetRect().top + BLOCK_HEIGHT);
   
    angleUnitCircle.y = abs(angleUnitCircle.y);                 //отражаемся по y только вниз                    
   
    if (_bonus)
    {
        this->BonusCreate();
    }

    return angleUnitCircle;
}

Vector2f Block::BallCollisionTopWall(Vector2f angleUnitCircle, Ball& ball)
{
    // Если попали в это место то устанавливаемся в максимально возможное положение
    ball.setPosition(ball.getPosition().x, this->GetRect().top - BLUE_BALL_HEIGHT);

    angleUnitCircle.y = -1 * abs(angleUnitCircle.y);                 //отражаемся по y только вверх                    

    if (_bonus)
    {
        this->BonusCreate();
    }

    return angleUnitCircle;
}

Vector2f Block::BallCollisionLeftWall(Vector2f angleUnitCircle, Ball& ball)
{
    // Если попали в этот угол то устанавливаемся в максимально возможное положение
    ball.setPosition(this->GetRect().left-BLUE_BALL_WIDTH, ball.getPosition().y);

    angleUnitCircle.x = -1 * abs(angleUnitCircle.x);                         //отражаемся по х
    
    if (_bonus)
    {
        this->BonusCreate();
    }

    return angleUnitCircle;
}

Vector2f Block::BallCollisionRightWall(Vector2f angleUnitCircle, Ball& ball)
{
    // Если попали в это место то устанавливаемся в максимально возможное положение
    ball.setPosition(this->GetRect().left + BLOCK_WIDTH, ball.getPosition().y);

    angleUnitCircle.x = abs(angleUnitCircle.x);                         //отражаемся по х

    if (_bonus)
    {
        this->BonusCreate();
    }

    return angleUnitCircle;
}


void Block::BonusCreate()
{
   /* Vector2f startPosition;
    startPosition.x = this->GetRect().left + BLOCK_WIDTH / 2 - BONUS_WIDTH / 2;
    startPosition.y = this->GetRect().top;
    bonus.push_back(new Bonus(_blockType, startPosition));*/
}