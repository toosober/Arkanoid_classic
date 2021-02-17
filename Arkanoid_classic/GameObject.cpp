
#include "GameObject.h"
#include "Menu.h"
#include <random>


//------------------------------------// GameObject //------------------------------------//

GameObject::GameObject(Image& image, float coordX, float coordY, float width, float height, int speedX, int speedY) : img(image)
{   
    texture.loadFromImage(image);
    this->coordX = coordX;
    this->coordY = coordY;
    this->width = width;
    this->height = height;
    this->speedX = speedX;
    this->speedY = speedY;
    isMove = false;
}

FloatRect GameObject::GetRect()
{
    return FloatRect(this->getPosition().x, this->getPosition().y, width, height);
}

Vector2f GameObject::GetSpeed()
{
    return Vector2f(speedX, speedY);
}

void GameObject::SetSpeed(Vector2f speed)
{
    speedX = speed.x;
    speedY = speed.y;
}

//------------------------------------// Platform //------------------------------------//

Platform::Platform(Image& image, float coordX, float coordY, float width, float height, int speedX, int speedY)
    : GameObject(image, coordX, coordY, width, height, speedX, speedY)
{
    this->setTexture(texture);
    this->setTextureRect(sf::IntRect(coordX, coordY, width, height));
}

void Platform::SetPlatform(bool choicePlatformType)
{
    if (this->typePlatform == largePlatform || this->typePlatform == smallPlatform)
    {
        this->typePlatform = mediumPlatform;
        this->coordX = 58;
        this->coordY = 302;
        this->width = 90;
        this->height = 31;
        this->setTextureRect(sf::IntRect(coordX, coordY, width, height));
        this->rightBorder = 684;
    }
    else if (this->typePlatform == mediumPlatform)
    {
        if (choicePlatformType == true)
        {
            this->coordX = 148;
            this->coordY = 302;
            this->width = 128;
            this->height = 31;
            this->typePlatform = largePlatform;
            this->setTextureRect(sf::IntRect(coordX, coordY, width, height));
            this->rightBorder = 645;
        }            
        else
        {
            this->coordX = 0;
            this->coordY = 302;
            this->width = 58;
            this->height = 31;
            this->typePlatform = smallPlatform;
            this->setTextureRect(sf::IntRect(coordX, coordY, width, height));
            this->rightBorder = 715;
        }
            
    }
}

void Platform::ResetTypePlatform()
{
    this->typePlatform = mediumPlatform;
    this->coordX = 58;
    this->coordY = 302;
    this->width = 90;
    this->height = 31;
    this->setTextureRect(sf::IntRect(coordX, coordY, width, height));
    this->rightBorder = 684;
}

//------------------------------------// Balls //------------------------------------//


Balls::Balls(Image& image, float coordX, float coordY, float width, float height, int speedX, int speedY)
    : GameObject(image, coordX, coordY, width, height, speedX, speedY)
{
    this->setTexture(texture);
    this->setTextureRect(sf::IntRect(coordX, coordY, width, height));

}

void Balls::Move(double unit_circle_x, double unit_circle_y, float time, Platform* platform) //координаты точки на единичной окружности (направление полета шарика)
{
    //в этот блок попадаем при первой инициализации угла, на который вылетит шарик при нажатии клавиши space
    if (initialization)
    {
        initialization = false;
        angle_unit_circle_x = unit_circle_x;
        angle_unit_circle_y = unit_circle_y;
    }

    speed_vector_x = speedX * time * angle_unit_circle_x; //вектор движения по x
    speed_vector_y = speedY * time * angle_unit_circle_y; //вектор движения по y


    this->move(speed_vector_x, speed_vector_y); //вызываем стандартную функцию move от класса Sprite
    
    //после сдвига проверяем куда мы попали?

    //проверяем пересечение с левой стенкой карты
    if (this->GetRect().left < 25)
    {
        this->setPosition(25, this->getPosition().y);       //если вдруг перелетели правую стенку, то уснатавливаемся в самое крайнее возможное положение
        angle_unit_circle_x = -angle_unit_circle_x;         //меняем направление на противоположное по х
    }

    //проверяем пересечение с правой стенкой
    if (this->GetRect().left > 760)
    {
        //если вдруг перелетели правую стенку, то уснатавливаемся в самое крайнее возможное положение
        this->setPosition(760, this->getPosition().y);
        angle_unit_circle_x = -angle_unit_circle_x;         //меняем направление на противоположное по х
    }

    //проверяем пересечение с потолком
    if (this->getPosition().y < 25)
    {
        this->setPosition(this->getPosition().x, 25); //если вдруг перелетели потолок, то устанавливаемся в саоме крайнее возможное положение
        angle_unit_circle_y = -angle_unit_circle_y;   // меняем напрваления на противоположное, по y
    }


    //Далее сложный блок, взаимодействия с платформой. 
    //Платформа может находится в трех состояниях (маленькая платформа, средняя, большая платформа
    //Физика отражения у маленькой платформы и у средней - одинаковая
    //У большой платформы верхняя часть платформы разделена на 7 областей, при попадании в которые шарик ведет себя по разному
    //поэтому необходимо проверять с какой платформой столкнулись
    //и вызывать соответствующую функцию обработки
    //В платформу можно врезаться сверху, с левого бока и с правого бока
    

    ball_center_x = this->GetRect().left + (this->GetRect().width / 2);       // центр шарика по х
    ball_center_y = this->GetRect().top + (this->GetRect().height / 2);       // центр шарика по y
    ball_right_x = this->GetRect().left + this->GetRect().width;              // правый край по х
    ball_left_x = this->GetRect().left;                                       // левый край по х

    platform_left_x = platform->GetRect().left;                               // левый край платформы по х
    platform_right_x = platform->GetRect().left + platform->GetRect().width;  // правый край платформы по х
    platform_top_y = platform->GetRect().top;                                 // верх платформы

    if (platform->GetPlatformType() == 2)
        CollisionLargePlatform(platform);
    else
        CollisionSmallAndMediumPlatform(platform);

    //если шарик упал
    if (this->getPosition().y > 700)
    {
        Menu::GetInstance().SetCountlives(-1);
        if (Menu::GetInstance().GetCountlives() > 0)
        {
            platform->ResetTypePlatform();
            this->setPosition(platform->getPosition().x + 56, platform->getPosition().y - 16);
        }

        this->ResetBallPositionOnPlatform();
        this->ResetGreenBonus();
        this->SetIsMove(false);
        this->initialization = true;
        this->score_ratio = 1;
    }
    
}

void Balls::CollisionSmallAndMediumPlatform(Platform* platform)
{
    if (this->GetRect().intersects(platform->GetRect())) //Если пересеклись с платформой, то обнуляем коэффициент бонуса за выбитые блоки и проверяем где?
    {
        this->score_ratio = 1;
        if (greenBonus)
        {
            initialization = true;
            SetIsMove(false);
            this->SetBallPositionOnPlatform(this->GetRect().left - platform->GetRect().left);

        }
        //Если центр шарика по координате х находится с левого края в диапазоне платформы от нулевого до 8 пикселя?
        else if (ball_center_x - platform_left_x >= 0 && ball_center_x - platform_left_x < 8)
        {
            if (speed_vector_x < 0.001 && speed_vector_x > -0.001) //Если по х практически не смещаемся и попадаем в левый край, то должны улететь влево
            {
                angle_unit_circle_x = -0.9;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
            else if (speed_vector_x > 0) //иначе если летим слева направо и ударяемся в левый угол, то должны отразиться обратно
            {
                angle_unit_circle_x = -angle_unit_circle_x; //отражаемся по х
                angle_unit_circle_y = -angle_unit_circle_y; //отражаемся по y
            }
            else if ((speed_vector_x < 0)) //иначе если летим справа налево у ударяемся о левый угол, то должны изменить вектор движения
            {
                angle_unit_circle_x = -0.9;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
        }
        else if (platform_right_x - ball_center_x >= 0 && platform_right_x - ball_center_x < 8)
        {
            if (speed_vector_x < 0.001 && speed_vector_x > -0.001) //Если по х практически не смещаемся и попадаем в правый край, то должны улететь вправо
            {
                angle_unit_circle_x = 0.9;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
            else if (speed_vector_x < 0) //иначе если летим справа налево и ударяемся в правый угол, то должны отразиться обратно
            {
                angle_unit_circle_x = -angle_unit_circle_x; //отражаемся по х
                angle_unit_circle_y = -angle_unit_circle_y; //отражаемся по y
            }
            else if ((speed_vector_x > 0)) //иначе если летим слева направо у ударяемся о правый угол, то должны изменить вектор движения
            {
                angle_unit_circle_x = 0.9;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
        }
        else if (ball_center_x - platform_left_x > 0 && ball_center_x - platform_right_x < 0)
        {
            this->setPosition(this->getPosition().x, platform_top_y - this->GetRect().height); //если пересекли платформу, то выталкиваем шарик из платформы
            //Если по х практически не смещаемся и попадаем в центральную часть платформы, то должны улететь либо вправо, либо влево в зависимости от
            //состояния переменной change_angel
            if (speed_vector_x < 0.001 && speed_vector_x > -0.001)
            {
                if (change_angle)
                {
                    angle_unit_circle_x = 0.5;
                    change_angle = false;
                }
                else
                {
                    angle_unit_circle_x = -0.5;
                    change_angle = true;
                }
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }

            else
                angle_unit_circle_y = -angle_unit_circle_y; //просто меняем направление движения
        }

        //Теперь обрабатываем попадание в левую и правую стенку платформы

        //Если правая стенка ширка пересекла левую стенку платформы, а левая стенка шарика не пересекла левую стенку платформы
        //При этом центр шарика по y опустился ниже верхнего уровня платформы:
        if (ball_right_x >= platform_left_x && ball_left_x < platform_left_x && ball_center_y > platform_top_y)
        {

            //выталкиваем шарик из платформы
            this->setPosition(platform_left_x - this->GetRect().width, this->getPosition().y);

            angle_unit_circle_x = -1 * abs(angle_unit_circle_x); //толкаем шарик в противоположном от платформы направлении
        }
        //если левая стенка шарика находится внутри платформы, а правая стенка шарика снаружи платформы
        //при этом центр шарика по y опустился ниже верхнего уровня платформы
        else if (ball_left_x <= platform_right_x && ball_right_x > platform_right_x && ball_center_y > platform_top_y)
        {

            this->setPosition(platform_right_x, this->getPosition().y);
            angle_unit_circle_x = abs(angle_unit_circle_x); //толкаем шарик в противоположном от платформы направлении
        }
    }
}

void Balls::CollisionLargePlatform(Platform* platform)
{
    if (this->GetRect().intersects(platform->GetRect())) //Если пересеклись с платформой, то обнуляем коэффициент бонуса за выбитые блоки и проверяем где?
    {
        this->score_ratio = 1;
        
        if (greenBonus)
        {   
            initialization = true;
            SetIsMove(false);
            this->SetBallPositionOnPlatform(this->GetRect().left - platform->GetRect().left);
        }

        //Если центр шарика по координате х находится с левого края в диапазоне платформы от нулевого до 8 пикселя?
        if (ball_center_x - platform_left_x >= 0 && ball_center_x - platform_left_x < 8)
        {
            if (speed_vector_x < 0.001 && speed_vector_x > -0.001) //Если по х практически не смещаемся и попадаем в левый край, то должны улететь влево
            {
                angle_unit_circle_x = -0.9;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
            else if (speed_vector_x > 0) //иначе если летим слева направо и ударяемся в левый угол, то должны отразиться обратно
            {
                angle_unit_circle_x = -angle_unit_circle_x; //отражаемся по х
                angle_unit_circle_y = -angle_unit_circle_y; //отражаемся по y
            }
            else if ((speed_vector_x < 0)) //иначе если летим справа налево у ударяемся о левый угол, то должны изменить вектор движения
            {
                angle_unit_circle_x = -0.9;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
        }

        //Если центр шарика по координате х находится в диапазоне от 8 до 16 пикселя (край платформы но уже не угол)
        else if (ball_center_x - platform_left_x >= 8 && ball_center_x - platform_left_x < 16)
        {
            this->setPosition(this->getPosition().x, platform_top_y - this->GetRect().height); //если пересекли платформу, то выталкиваем шарик из платформы

            if (speed_vector_x < 0.001 && speed_vector_x > -0.001) //Если по х практически не смещаемся и попадаем в левый край, то должны слегка изменить свою траекторию
            {
                angle_unit_circle_x += -0.19;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
            else if (speed_vector_x < 0) //иначе если летим справа налево и ударяемся в левый угол, то должны отразиться налево на чуть больший угол
            {
                if (angle_unit_circle_x > -0.8)     //проверяю не слишком ли тупой угол, чтобы шарик не начал летать параллельно платформе
                    angle_unit_circle_x += -0.19;   //увеличиваю угол

                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2)); //привожу угол по у в соовтетствии с х
            }
            // иначе, если летим слева направо то не меняем направление движения по х, а только по y
            else
                angle_unit_circle_y = -angle_unit_circle_y;

        }

        //Если центр шарика по координате х находится в диапазоне от 16 до 58 пикселя
        else if (ball_center_x - platform_left_x >= 16 && ball_center_x - platform_left_x < 58)
        {
            this->setPosition(this->getPosition().x, platform_top_y - this->GetRect().height); //если пересекли платформу, то выталкиваем шарик из платформы

            //Если по х практически не смещаемся и попадаем в левую часть платформы, то должны слегка изменить свою траекторию улетев влево
            if (speed_vector_x < 0.001 && speed_vector_x > -0.001)
            {
                angle_unit_circle_x += -0.5;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
            //если летим справа налево или слева направо, то вектор движения изменяем только по y
            else
                angle_unit_circle_y = -angle_unit_circle_y;
        }

        //Если попали в центр платформы в дипазон от 58 до 72 пикселя
        else if (ball_center_x - platform_left_x >= 58 && ball_center_x - platform_left_x < 72)
        {
            this->setPosition(this->getPosition().x, platform_top_y - this->GetRect().height); //если пересекли платформу, то выталкиваем шарик из платформы

            //Если по х практически не смещаемся и попадаем в центральную часть платформы, то должны улететь либо вправо, либо влево в зависимости от
            //состояния переменной change_angel
            if (speed_vector_x < 0.001 && speed_vector_x > -0.001)
            {
                if (change_angle)
                {
                    angle_unit_circle_x = 0.5;
                    change_angle = false;
                }
                else
                {
                    angle_unit_circle_x = -0.5;
                    change_angle = true;
                }
                    
                

                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
            else //Иначе если двигались слева направо или справа налево, то начинаем лететь вертикально вверх
            {
                angle_unit_circle_x = 0;
                angle_unit_circle_y = 1;
            }
        }

        //Если центр шарика по координате х находится в диапазоне от 72 до 113 пикселя
        else if (ball_center_x - platform_left_x >= 72 && ball_center_x - platform_left_x < 113)
        {
            this->setPosition(this->getPosition().x, platform_top_y - this->GetRect().height); //если пересекли платформу, то выталкиваем шарик из платформы

            //Если по х практически не смещаемся и попадаем в правую часть платформы, то должны слегка изменить свою траекторию улетев вправо
            if (speed_vector_x < 0.001 && speed_vector_x > -0.001)
            {
                angle_unit_circle_x += 0.5;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
            //если летим справа налево или слева направо, то вектор движения изменяем только по y
            else
                angle_unit_circle_y = -angle_unit_circle_y;
        }

        //Если центр шарика по координате х находится в диапазоне от 113 до 120 пикселя (край платформы но не угол)
        else if (ball_center_x - platform_left_x >= 113 && ball_center_x - platform_left_x < 120)
        {
            this->setPosition(this->getPosition().x, platform_top_y - this->GetRect().height); //если пересекли платформу, то выталкиваем шарик из платформы

            if (speed_vector_x < 0.001 && speed_vector_x > -0.001) //Если по х практически не смещаемся и попадаем в правый край, то должны слегка изменить свою траекторию
            {
                angle_unit_circle_x += 0.19;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
            else if (speed_vector_x > 0) //иначе если летим слева направо и ударяемся в правый край, то должны отразиться направо на чуть больший угол
            {
                if (angle_unit_circle_x < 0.8)     //проверяем не слишком ли тупой угол, чтобы шарик не начал летать параллельно платформе
                    angle_unit_circle_x += 0.19;   //увеличиваем угол

                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2)); //приводим угол по у в соовтетствии с новым направлением по х
            }
            // иначе, если летим справа налево то не меняем направление движения по х, а только по y
            else
                angle_unit_circle_y = -angle_unit_circle_y;
        }

        //Если центр шарика по координате х находится с правого края в диапазоне платформы от 120 до 128 пикселя?
        else if (ball_center_x - platform_left_x >= 120 && ball_center_x - platform_left_x < 128)
        {
            if (speed_vector_x < 0.001 && speed_vector_x > -0.001) //Если по х практически не смещаемся и попадаем в правый край, то должны улететь вправо
            {
                angle_unit_circle_x = 0.9;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
            else if (speed_vector_x < 0) //иначе если летим справа налево и ударяемся в правый угол, то должны отразиться обратно
            {
                angle_unit_circle_x = -angle_unit_circle_x; //отражаемся по х
                angle_unit_circle_y = -angle_unit_circle_y; //отражаемся по y
            }
            else if ((speed_vector_x > 0)) //иначе если летим слева направо у ударяемся о правый угол, то должны изменить вектор движения
            {
                angle_unit_circle_x = 0.9;
                angle_unit_circle_y = sqrt(1 - pow(angle_unit_circle_x, 2));
            }
        }

        //Теперь обрабатываем попадание в левую и правую стенку платформы

        //Если правая стенка ширка пересекла левую стенку платформы, а левая стенка шарика не пересекла левую стенку платформы
        //При этом центр шарика по y опустился ниже верхнего уровня платформы:
        if (ball_right_x >= platform_left_x && ball_left_x < platform_left_x && ball_center_y > platform_top_y)
        {

            //выталкиваем шарик из платформы
            this->setPosition(platform_left_x - this->GetRect().width, this->getPosition().y);

            angle_unit_circle_x = -1 * abs(angle_unit_circle_x); //толкаем шарик в противоположном от платформы направлении
        }
        //если левая стенка шарика находится внутри платформы, а правая стенка шарика снаружи платформы
        //при этом центр шарика по y опустился ниже верхнего уровня платформы
        else if (ball_left_x <= platform_right_x && ball_right_x > platform_right_x && ball_center_y > platform_top_y)
        {

            this->setPosition(platform_right_x, this->getPosition().y);

            angle_unit_circle_x = abs(angle_unit_circle_x); //толкаем шарик в противоположном от платформы направлении
        }
    }

}




void Balls::SetSpeedFast(int x)
{
    speedX *= 2;
    speedY *= 2;

}

void Balls::SetSpeedSlow(int x)
{
    speedX /= 2;
    speedY /= 2;

}

void Balls::ChangeVector(int x)
{
    if (x == 0)
        angle_unit_circle_x = -angle_unit_circle_x;
    else if (x == 1)
        angle_unit_circle_y = -angle_unit_circle_y;
    else if (x == 2)
    {
        angle_unit_circle_x = -angle_unit_circle_x;
        angle_unit_circle_y = -angle_unit_circle_y;
    }
    else
        std::cout << "bad index: " << x << std::endl;


}


//------------------------------------// Bonus //------------------------------------//

Bonus::Bonus(Image& image, unsigned bonusType, float coordX, float coordY, float width, float height, int speedX, int speedY)
    : GameObject(image, coordX, coordY, width, height, speedX, speedY)
{
    this->bonusType = bonusType;
    this->setTexture(texture);
    this->width = 27;
    this->height = 30;
    switch (bonusType)
    {
    case blue:
        this->coordX = 456;
        this->coordY = 449;
        break;
    case green:
        this->coordX = 488;
        this->coordY = 449;
        break;
    case pink:
        this->coordX = 520;
        this->coordY = 449;
        break;
    case purple:
        this->coordX = 553;
        this->coordY = 449;
        break;
    case red:
        this->coordX = 456;
        this->coordY = 482;
        break;
    case yellow:
        this->coordX = 488;
        this->coordY = 481;
        break;
        
    }

    this->setTextureRect(sf::IntRect(this->coordX, this->coordY, this->width, this->height));
    
}

void Bonus::CollisionAndMove(std::list<Bonus*>& bonuses, std::list<Bonus*>::iterator bns, Platform& platform, Balls& ball, float time)
{
    std::random_device rd;
    std::mt19937 mersenne(rd());
    for (bns = bonuses.begin(); bns != bonuses.end();)
    {
        (*bns)->move(0, (0.1 * time));

        if ((*bns)->GetRect().intersects(platform.GetRect()))
        {
            switch ((*bns)->bonusType)
            {
            case blue:
                platform.SetPlatform(mersenne() % 2);
                break;
            case green:
                ball.SetGreenBonus();
                break;
            case pink:
                break;
            case purple:
                
                break;
            case red:
                break;
            case yellow:
                Menu::GetInstance().SetCountlives(1);
                break;
            default:
                break;
            }

            bns = bonuses.erase(bns);
        }

        else
        {   
            bns++;
        }

            
    }
}

//------------------------------------// Block //------------------------------------//

Block::Block(Image& image, float coordX, float coordY, float width, float height, bool bonus, unsigned blockType, int speedX, int speedY)
    : GameObject(image, coordX, coordY, width, height, speedX, speedY)
{
    
    this->bonus = bonus;
    this->blockType = blockType;
    this->setTexture(texture);
    this->setTextureRect(sf::IntRect(coordX, coordY, width, height));
}

bool Block::Collision(std::list<Block*>& blocks, std::list<Block*>::iterator blks, Balls& ball, std::list<Bonus*>& bonuses, std::list<Bonus*>::iterator bns)
{
    float ball_left_x = ball.GetRect().left;                                        // левый край шарика
    float ball_right_x = ball.GetRect().left + ball.GetRect().width;                // правый край ширка
    float ball_top_y = ball.GetRect().top;                                          // верх шарика
    float ball_bottom_y = ball.GetRect().top + ball.GetRect().height;               // низ шарика
    float ball_center_x = ball.GetRect().left + (ball.GetRect().width / 2);
    float ball_center_y = ball.GetRect().top + (ball.GetRect().height / 2);

    //обрабатываем пересечене с блоками
    for (blks = blocks.begin(); blks != blocks.end();)
    {
        
        //Если шарик пересек блок, проверяем бонусный ли это шарик и с какой стороны произошло столкновение, а также подсчитываем очки
        if ((*blks)->GetRect().intersects(ball.GetRect())) 
        {
            
            Menu::GetInstance().SetCountScore(10*ball.GetScoreRatio());
            std::cout << "ball.GetScoreRatio(): " << ball.GetScoreRatio() << std::endl;
            ball.IncreaseValue_ScoreRatio();

            if ((*blks)->bonus)
            {
                bonuses.push_back(new Bonus((*blks)->img, (*blks)->blockType));
                bns = bonuses.end();
                bns--;
                (*bns)->setPosition((*blks)->GetRect().left + ((*blks)->GetRect().width / 2), (*blks)->GetRect().top);
            }
               

            
            if (ball_top_y <= (*blks)->GetRect().top + (*blks)->GetRect().height // если шарик соприкоснулся с блоком снизу
                && ball_bottom_y > (*blks)->GetRect().top + (*blks)->GetRect().height
                && ball_center_x >= (*blks)->GetRect().left
                && ball_center_x <= (*blks)->GetRect().left + (*blks)->GetRect().width)
            {
                //устанавливаем позицию шарика в максимально возможное близкое положение к блоку и меняем вектор движения по y
                ball.setPosition(ball.getPosition().x, (*blks)->GetRect().top + (*blks)->GetRect().height);
                ball.ChangeVector(1);
            }
            else if (ball_top_y < (*blks)->GetRect().top // иначе если шарик соприкоснулся с блоком сверху
                && ball_bottom_y >= (*blks)->GetRect().top
                && ball_center_x >= (*blks)->GetRect().left
                && ball_center_x <= (*blks)->GetRect().left + (*blks)->GetRect().width)
            {
                //устанавливаем позицию шарика в максимально возможное близкое положение к блоку и меняем вектор движения по y
                ball.setPosition(ball.getPosition().x, (*blks)->GetRect().top - ball.GetRect().height);
                ball.ChangeVector(1);
            }

            else if (ball_left_x < (*blks)->GetRect().left //иначе если врезались в левую сторону блока
                && ball_right_x >= (*blks)->GetRect().left)
                //&& ball_center_y >= (*blks)->GetRect().top
                //&& ball_center_y <= (*blks)->GetRect().top + (*blks)->GetRect().height)
            {
                //устанавливаем позицию шарика в максимально возможное близкое положение к блоку и меняем вектор движения по х
                ball.setPosition((*blks)->GetRect().left - ball.GetRect().width, ball.getPosition().y);
                ball.ChangeVector(0);
            }

            else if (ball_left_x <= (*blks)->GetRect().left + (*blks)->GetRect().width //иначе если врезались в правую сторону блока
                && ball_right_x > (*blks)->GetRect().left + (*blks)->GetRect().width)
                //&& ball_center_y >= (*blks)->GetRect().top
                //&& ball_center_y <= (*blks)->GetRect().top + (*blks)->GetRect().height)
            {
                //устанавливаем позицию шарика в максимально возможное близкое положение к блоку и меняем вектор движения по х
                ball.setPosition((*blks)->GetRect().left + (*blks)->GetRect().width, ball.getPosition().y);
                ball.ChangeVector(0);
            }

            blks = blocks.erase(blks);
        }

        else
            blks++;

        if (blocks.empty())
        {
            return true;
        }
    }

    return false;
}



