#pragma once
#include <graphics.h>
#include <math.h>
#define WIDTH 600
#define HEIGHT 600
#define EDGE_X 20
#define EDGE_Y 20
#define AMP 10 //����ģ���Ŵ�ϵ��

struct vector
{
	int x;
	int y;
};

class Ball
{
private:
	int m_radius;		//�뾶
	int m_angle;		//�Ƕ�
	int m_velocity;		//�ٶ�
	vector m_position;	//λ��
	vector m_direction;	//������Ƕȴ��ڻ����ϵ

	static int m_num;
	static int m_allVelocity;

public:
	Ball();
	Ball(int radius, int angle, int velocity, int x, int y);
	~Ball();
	void setRadius(int radius);
	void setAngle(int angle);
	void setVelocity(int velocity);
	void setPosition(int x, int y);
	void setDirection(int x, int y);
	int getRadius() const;
	int getAngle() const;
	int getVelocity() const;
	vector getPosition() const;
	vector getDirection() const;
public:
	void move();								//�ı�С��λ��
	void draw();								//����С��
	void solveWallCollision();					//����С����ǽ�ڵ���ײ

public:
	static int getNumOfBalls();					//��ȡС������
	static void moveBalls(Ball* pBalls);		//�ı�����С��λ��
	static void drawBalls(Ball* pBalls);		//��������С��
	static void solveBallCollision(Ball* pBalls);	//����С��֮�����ײ
};

