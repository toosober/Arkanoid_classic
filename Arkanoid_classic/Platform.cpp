
#include "Platform.h"
#include "Config.h"



//-------------------------------------------------------------------------Platform

//движение платформы
void Platform::Move(const float speed, const float time)
{
    this->move(speed * time, 0);
}


// Пересечение платформы с шариком
// на вход принимаем шарик, который столкнулся с платформой и вектор его движения на единичной окружности
// возвращаем новый вектор движения шарика на единичной окружности
Vector2f Platform::CollisionWithBall(Vector2f angleUnitCircle, Ball& ball) //Пересечение платформы с шариком
{
    float collisionLocation = this->CollisionLocation(ball);

    // Если центр шарика по координате х находится левее платформы
    if (collisionLocation < 0)
    {
        return this->BallCollisionLeftWall(angleUnitCircle, ball);
    }
    // Если центр шарика по координате х находится на левом крае
    else if (collisionLocation < 8)
    {
        return this->BallCollisionLeftEdge(angleUnitCircle, ball);
    }
    // Если центр шарика по координате х находится по середине между левым и правым краем
    else if (collisionLocation < this->GetRect().width - 8)
    {
        return this->BallCollisionStandart(angleUnitCircle, ball);
    }
    // Если центр шарика по координате х находится на правом крае
    else if (collisionLocation < this->GetRect().width)
    {
        return this->BallCollisionRightEdge(angleUnitCircle, ball);
    }
    // Если центр шарика по коориднае х находится правее платформы
    else
    {
        return this->BallCollisionRightWall(angleUnitCircle, ball);
    }

}

Vector2f Platform::BallCollisionLeftEdge(Vector2f angleUnitCircle, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height);

    //Если приземлились на платформу практически прямо
    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
    {
        angleUnitCircle.x = -0.9;
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));        
    }
    else if (angleUnitCircle.x > 0) //иначе если летим слева направо и ударяемся в левый угол, то должны отразиться обратно
    {
        angleUnitCircle.x = -angleUnitCircle.x;        //отражаемся по х
        angleUnitCircle.y = -angleUnitCircle.y;        //отражаемся по y                    
    }
    else if (angleUnitCircle.x < 0) // Иначе если летим справа налево, то должны улететь под большим углом
    {
        angleUnitCircle.x = -0.95;                                 //отражаемся по х
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.y, 2));        //отражаемся по y
    }

    return angleUnitCircle;
    

}

Vector2f Platform::BallCollisionRightEdge(Vector2f angleUnitCircle, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height);

    //Если приземлились на платформу практически прямо
    if (angleUnitCircle.x > -0.001 && angleUnitCircle.x < 0.001)
    {
        angleUnitCircle.x = -0.9;
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
    }
    else if (angleUnitCircle.x < 0) //иначе если летим cправа налево и ударяемся в правый угол, то должны отразиться обратно
    {
        angleUnitCircle.x = -angleUnitCircle.x;        //отражаемся по х
        angleUnitCircle.y = -angleUnitCircle.y;        //отражаемся по y                    
    }
    else if (angleUnitCircle.x > 0) // Иначе если летим слева направо, то должны улететь под большим углом
    {
        angleUnitCircle.x = 0.95;                                 //отражаемся по х
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.y, 2));        //отражаемся по y
    }

    return angleUnitCircle;


}

Vector2f Platform::BallCollisionStandart(Vector2f angleUnitCircle, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height);

    // Если по х практически не смещаемся и попадаем в центральную часть платформы, то должны улететь либо вправо, либо влево в зависимости от
    //состояния переменной change_angel
    if (angleUnitCircle.x < 0.001 && angleUnitCircle.x > -0.001)
    {
        std::random_device rd;
        std::mt19937 mersenne(rd());

        if (mersenne() % 2)
        {
            angleUnitCircle.x = 0.5;
        }
        else
        {
            angleUnitCircle.x = -0.5;
        }

        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
    }
    // Иначе просто меняем направления полета по y
    else
    {
        angleUnitCircle.y = -angleUnitCircle.y;
    }

    return angleUnitCircle;
}

Vector2f Platform::BallCollisionLeftWall(Vector2f angleUnitCircle, Ball& ball)
{
    ball.setPosition(this->GetRect().left - ball.GetRect().width, ball.getPosition().y);
    angleUnitCircle.x = -1 * abs(angleUnitCircle.x);
    return angleUnitCircle;
}

Vector2f Platform::BallCollisionRightWall(Vector2f angleUnitCircle, Ball& ball)
{
    ball.setPosition(this->GetRect().left + this->GetRect().width, ball.getPosition().y);
    angleUnitCircle.x = abs(angleUnitCircle.x);
    return angleUnitCircle;
}

float Platform::CollisionLocation(Ball& ball)
{
    return ball.GetRect().left + ( ball.GetRect().width / 2 ) - this->GetRect().left;
}





//-------------------------------------------------------------------------MediumPlatform

MediumPlatform::MediumPlatform()
{   
    this->setTexture(_texture);
    this->setTextureRect(IntRect(MEDIUM_PLATFORM_LEFT, MEDIUM_PLATFORM_TOP, MEDIUM_PLATFORM_WIDTH, MEDIUM_PLATFORM_HEIGHT));
    
}



//--------------------------------------------------------------------------SmallPlatform
SmallPlatform::SmallPlatform()
{
    this->setTextureRect(IntRect(SMALL_PLATFORM_LEFT, SMALL_PLATFORM_TOP, SMALL_PLATFORM_WIDTH, SMALL_PLATFORM_HEIGHT));
}



//-------------------------------------------------------------------------------LargePlatform

LargePlatform::LargePlatform()
{  
    this->setTexture(_texture);
    this->setTextureRect(IntRect(LARGE_PLATFORM_LEFT, LARGE_PLATFORM_TOP, LARGE_PLATFORM_WIDTH, LARGE_PLATFORM_HEIGHT));
}

Vector2f LargePlatform::CollisionWithBall(Vector2f angleUnitCircle, Ball& ball)
{
    float collisionLocation = this->CollisionLocation(ball);
    // Если центр шарика по координате х находится левее платформы
    if (collisionLocation < 0)
    {
        return this->BallCollisionLeftWall(angleUnitCircle, ball);
    }
    // Если центр шарика по координате х находится на левом крае
    else if (collisionLocation < 8)
    {
        return this->BallCollisionLeftEdge(angleUnitCircle, ball);
    }
    // Если попали в край платформы основной зоны, но не в сам угол
    else if (collisionLocation < 16)
    {
        return this->BallCollisionLeftEdgePlus(angleUnitCircle, ball);
    }
    // Если попали в левую часть
    else if (collisionLocation < 58)
    {
        return this->BallCollisionStandart(angleUnitCircle, ball);
    }
    // Если попали в самый центр
    else if (collisionLocation < 72)
    {
        return this->BallCollisionCenter(angleUnitCircle, ball);
    }

    // Если попали в правую часть
    else if (collisionLocation < this->GetRect().width - 16)
    {
        return this->BallCollisionStandart(angleUnitCircle, ball);
    }
    else if (collisionLocation < this->GetRect().width - 8)
    {
        return this->BallCollisionRightEdgePlus(angleUnitCircle, ball);
    }
    // Если центр шарика по координате х находится на правом крае
    else if (collisionLocation < this->GetRect().width)
    {
        return this->BallCollisionRightEdge(angleUnitCircle, ball);
    }
    // Если центр шарика по коориднае х находится правее платформы
    else
    {
        return this->BallCollisionRightWall(angleUnitCircle, ball);
    }
}

Vector2f LargePlatform::BallCollisionLeftEdgePlus(Vector2f angleUnitCircle, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height); //если пересекли платформу, то выталкиваем шарик из платформы

    if (angleUnitCircle.x < 0.001 && angleUnitCircle.x > -0.001) //Если по х практически не смещаемся и попадаем в левый край, то должны слегка изменить свою траекторию
    {
        angleUnitCircle.x += -0.35;
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
    }
    else if (angleUnitCircle.x < 0) //иначе если летим справа налево и ударяемся в левый угол, то должны отразиться налево на чуть больший угол
    {
        if (angleUnitCircle.x > -0.8)     //проверяем не слишком ли тупой угол, чтобы шарик не начал летать параллельно платформе
            angleUnitCircle.x += -0.19;   //увеличиваем угол

        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2)); //приводим угол по у в соовтетствии с х
    }
    // иначе, если летим слева направо то не меняем направление движения по х, а только по y
    else
    {
        angleUnitCircle.y = -angleUnitCircle.y;
    }

    return angleUnitCircle;
        
}

Vector2f LargePlatform::BallCollisionRightEdgePlus(Vector2f angleUnitCircle, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height); //если пересекли платформу, то выталкиваем шарик из платформы

    if (angleUnitCircle.x < 0.001 && angleUnitCircle.x > -0.001) //Если по х практически не смещаемся и попадаем в правый край, то должны слегка изменить свою траекторию
    {
        angleUnitCircle.x += +0.35;
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
    }
    else if (angleUnitCircle.x > 0) //иначе если летим слева направо и ударяемся в правый угол, то должны отразиться вправо на чуть больший угол
    {
        if (angleUnitCircle.x < 0.8)     //проверяем не слишком ли тупой угол, чтобы шарик не начал летать параллельно платформе
            angleUnitCircle.x += 0.19;   //увеличиваем угол

        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2)); //приводим угол по у в соовтетствии с х
    }
    // иначе, если летим справа налево то не меняем направление движения по х, а только по y
    else
    {
        angleUnitCircle.y = -angleUnitCircle.y;
    }

    return angleUnitCircle;
}

Vector2f LargePlatform::BallCollisionCenter(Vector2f angleUnitCircle, Ball& ball)
{
    ball.setPosition(this->getPosition().x, this->GetRect().top - ball.GetRect().height); //если пересекли платформу, то выталкиваем шарик из платформы

    std::random_device rd;
    std::mt19937 mersenne(rd());
    //Если по х практически не смещаемся и попадаем в центральную часть платформы, то должны улететь либо вправо, либо влево в зависимости от
    //состояния переменной change_angel
    if (angleUnitCircle.x < 0.001 && angleUnitCircle.x > -0.001)
    {
        if (mersenne()%2)
        {
            angleUnitCircle.x = 0.5;                
        }
        else
        {
            angleUnitCircle.x = -0.5;                
        }
        angleUnitCircle.y = sqrt(1 - pow(angleUnitCircle.x, 2));
    }
    else //Иначе если двигались слева направо или справа налево, то начинаем лететь вертикально вверх
    {
        angleUnitCircle.x = 0;
        angleUnitCircle.y = -1;        
    }

    return angleUnitCircle;
}




//--------------------------------------------------------------------------------------Фабрика



void CreatorPlatform::ChangePlatform()
{   
    concretePlatform = this->FactoryMethod();
}



//FloatRect CreatorPlatform::SomeGetRect()
//{
//    FloatRect result = concretePlatform->GetRect();
//    return result;
//}
//
//void CreatorPlatform::SomeSetPosition(Vector2f position)
//{
//    concretePlatform->setPosition(position);
//    
//}
//
//void CreatorPlatform::SomeMove(const float speed, float time)
//{
//    concretePlatform->Move(speed, time);    
//}
//
//Vector2f CreatorPlatform::SomeGetPosition()
//{   
//    Vector2f result = concretePlatform->getPosition();
//    return result;
//}

void CreatorPlatform::SomeDraw(RenderWindow& window)
{
    window.draw(*concretePlatform);
}