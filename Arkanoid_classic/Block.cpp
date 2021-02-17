#include "Block.h"

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

            Menu::GetInstance().SetCountScore(10 * ball.GetScoreRatio());
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