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
        setPosition(WIDTH - getRadius(), getPosition().y); //�����ص�
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
            //�����ײ
            if (pow(pBalls[i].getPosition().x - pBalls[j].getPosition().x, 2) +
                pow(pBalls[i].getPosition().y - pBalls[j].getPosition().y, 2) <=
                pow(pBalls[i].getRadius() + pBalls[j].getRadius(), 2))
            {
                //�����ص�
                //��ǰ֡λ��
                int xNowi = pBalls[i].getPosition().x;
                int yNowi = pBalls[i].getPosition().y;
                int xNowj = pBalls[j].getPosition().x;
                int yNowj = pBalls[j].getPosition().y;

                //��������һ֡λ��
                pBalls[i].setPosition(xNowi - pBalls[i].getDirection().x, yNowi - pBalls[i].getDirection().y);
                pBalls[j].setPosition(xNowj - pBalls[j].getDirection().x, yNowj - pBalls[j].getDirection().y);

                //���ݶ����Ͷ����غ�ԭ����"��ȫ������ײ"���⣺
                //vi'=(mi-mj)/(mi+mj)*vi + 2mj/(mi+mj)*vj
                //vj'=2mi/(mi+mj)*vi + (mj-mi)/(mi+mj)*vj
                //�˴�m1��m2�ð뾶���η���ʾ��Դ�С��v1��v2�÷���������ʾ��
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


                ////�������߾���
                //int xDistance = static_cast<int>(xNowi - xNowj);
                //int yDistance = static_cast<int>(yNowi - yNowj);

                ////��Ҫ�ƶ��ľ���
                //int xMovei = ((pBalls[i].getRadius() + pBalls[j].getRadius()) - xDistance) * pBalls[i].getRadius() / (pBalls[i].getRadius() + pBalls[j].getRadius());
                //int yMovei = ((pBalls[i].getRadius() + pBalls[j].getRadius()) - yDistance) * pBalls[i].getRadius() / (pBalls[i].getRadius() + pBalls[j].getRadius());
                //int xMovej = ((pBalls[i].getRadius() + pBalls[j].getRadius()) - xDistance) * pBalls[j].getRadius() / (pBalls[i].getRadius() + pBalls[j].getRadius());
                //int yMovej = ((pBalls[i].getRadius() + pBalls[j].getRadius()) - xDistance) * pBalls[j].getRadius() / (pBalls[i].getRadius() + pBalls[j].getRadius());
                //

                ////����Ϊ�Ӵ�λ��,������ݸ��԰뾶������������һ����
                //pBalls[i].setPosition(xNowi + xMovei, yNowi + yMovei);
                //pBalls[j].setPosition(xNowj - xMovej, yNowj - yMovej);
            }
        }
    }
}


Ball::~Ball()
{
}
