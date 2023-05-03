#include "Ball.h"
#include <graphics.h>
#include <iostream>

int Ball::m_num = 0;
int Ball::m_allVelocity = 0;

Ball::Ball()
{
	m_num++;
}

Ball::Ball(int radius, int angle, int velocity, int x, int y) : m_radius(radius), m_angle(angle), m_velocity(velocity)
{
	m_position.x = x;
	m_position.y = y;
	m_direction.x = AMP * cos(angle * acos(-1) / 180);
	m_direction.y = AMP * sin(angle * acos(-1) / 180);
}

void Ball::setRadius(int radius)
{
	m_radius = radius;
}

void Ball::setAngle(int angle)
{
	m_angle = angle;
}

void Ball::setVelocity(int velocity)
{
	m_velocity = velocity;
}

void Ball::setPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}

void Ball::setDirection(int x, int y)
{
	m_direction.x = x;
	m_direction.y = y;
}

int Ball::getRadius() const
{
	return m_radius;
}

int Ball::getAngle() const
{
	return m_angle;
}

int Ball::getVelocity() const
{
	return m_velocity;
}

vector Ball::getPosition() const
{
	return m_position;
}

vector Ball::getDirection() const
{
	return m_direction;
}

void Ball::move()
{
	m_position.x += m_direction.x;
	m_position.y += m_direction.y;
    solveWallCollision();
}

void Ball::draw()
{
	setfillcolor(YELLOW);
	fillcircle(m_position.x, m_position.y, m_radius);
}

void Ball::solveWallCollision()
{
    if (m_position.x + m_radius > WIDTH)
    {
        m_direction.x = -m_direction.x;
        setPosition(WIDTH - getRadius(), getPosition().y); //处理重叠
    }
    if (m_position.x - m_radius < 0)
    {
        m_direction.x = -m_direction.x;
        setPosition(0 + getRadius(), getPosition().y);
    }
    if (m_position.y + m_radius > HEIGHT)
    {
        m_direction.y = -m_direction.y;
        setPosition(getPosition().x, HEIGHT - getRadius());
    }
    if (m_position.y - m_radius < 0)
    {
        m_direction.y = -m_direction.y;
        setPosition(getPosition().x, 0 + getRadius());
    }
}

int Ball::getNumOfBalls()
{
	return m_num;
}

void Ball::moveBalls(Ball *pBalls)
{
	for (int i = 0; i < m_num; i++)
	{
		(pBalls + i)->move();
	}
}

void Ball::drawBalls(Ball* pBalls)
{
	for (int i = 0; i < m_num; i++)
	{
		(pBalls + i)->draw();
	}
	FlushBatchDraw();
}

void Ball::solveBallCollision(Ball* pBalls)
{
    for (int i = 0; i < m_num; i++)
    {
        for (int j = 0; j < i; j++)
        {
            //检测碰撞
            if (pow(pBalls[i].getPosition().x - pBalls[j].getPosition().x, 2) +
                pow(pBalls[i].getPosition().y - pBalls[j].getPosition().y, 2) <=
                pow(pBalls[i].getRadius() + pBalls[j].getRadius(), 2))
            {
                //处理重叠
                //当前帧位置
                int xNowi = pBalls[i].getPosition().x;
                int yNowi = pBalls[i].getPosition().y;
                int xNowj = pBalls[j].getPosition().x;
                int yNowj = pBalls[j].getPosition().y;

                //重置至上一帧位置
                pBalls[i].setPosition(xNowi - pBalls[i].getDirection().x, yNowi - pBalls[i].getDirection().y);
                pBalls[j].setPosition(xNowj - pBalls[j].getDirection().x, yNowj - pBalls[j].getDirection().y);

                //根据动量和动能守恒原理处理"完全弹性碰撞"问题：
                //vi'=(mi-mj)/(mi+mj)*vi + 2mj/(mi+mj)*vj
                //vj'=2mi/(mi+mj)*vi + (mj-mi)/(mi+mj)*vj
                //此处m1、m2用半径三次方表示相对大小，v1、v2用方向向量表示；
                float mi = pow(pBalls[i].getRadius(), 3);
                float mj = pow(pBalls[j].getRadius(), 3);
                float vix = pBalls[i].getDirection().x;
                float vjx = pBalls[j].getDirection().x;
                float viy = pBalls[i].getDirection().y;
                float vjy = pBalls[j].getDirection().y;
                int vix_changed = static_cast<int>((mi - mj) / (mi + mj) * vix + 2 * mj / (mi + mj) * vjx);
                int viy_changed = static_cast<int>((mi - mj) / (mi + mj) * viy + 2 * mj / (mi + mj) * vjy);
                int vjx_changed = static_cast<int>(2 * mi / (mi + mj) * vix + (mj - mi) / (mi + mj) * vjx);
                int vjy_changed = static_cast<int>(2 * mi / (mi + mj) * viy + (mj - mi) / (mi + mj) * vjy);
                pBalls[i].setDirection(vix_changed, viy_changed);
                pBalls[j].setDirection(vjx_changed, vjy_changed);


                ////两球连线距离
                //int xDistance = static_cast<int>(xNowi - xNowj);
                //int yDistance = static_cast<int>(yNowi - yNowj);

                ////需要移动的距离
                //int xMovei = ((pBalls[i].getRadius() + pBalls[j].getRadius()) - xDistance) * pBalls[i].getRadius() / (pBalls[i].getRadius() + pBalls[j].getRadius());
                //int yMovei = ((pBalls[i].getRadius() + pBalls[j].getRadius()) - yDistance) * pBalls[i].getRadius() / (pBalls[i].getRadius() + pBalls[j].getRadius());
                //int xMovej = ((pBalls[i].getRadius() + pBalls[j].getRadius()) - xDistance) * pBalls[j].getRadius() / (pBalls[i].getRadius() + pBalls[j].getRadius());
                //int yMovej = ((pBalls[i].getRadius() + pBalls[j].getRadius()) - xDistance) * pBalls[j].getRadius() / (pBalls[i].getRadius() + pBalls[j].getRadius());
                //

                ////重置为接触位置,两球根据各自半径按比例“各退一步”
                //pBalls[i].setPosition(xNowi + xMovei, yNowi + yMovei);
                //pBalls[j].setPosition(xNowj - xMovej, yNowj - yMovej);
            }
        }
    }
}


Ball::~Ball()
{
}
