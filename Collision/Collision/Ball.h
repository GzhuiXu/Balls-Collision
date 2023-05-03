#pragma once
#include <graphics.h>
#include <math.h>
#define WIDTH 600
#define HEIGHT 600
#define EDGE_X 20
#define EDGE_Y 20
#define AMP 10 //向量模量放大系数

struct vector
{
	int x;
	int y;
};

class Ball
{
private:
	int m_radius;		//半径
	int m_angle;		//角度
	int m_velocity;		//速度
	vector m_position;	//位置
	vector m_direction;	//方向，与角度存在换算关系

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
	void move();								//改变小球位置
	void draw();								//绘制小球
	void solveWallCollision();					//处理小球与墙壁的碰撞

public:
	static int getNumOfBalls();					//获取小球数量
	static void moveBalls(Ball* pBalls);		//改变所有小球位置
	static void drawBalls(Ball* pBalls);		//绘制所有小球
	static void solveBallCollision(Ball* pBalls);	//处理小球之间的碰撞
};

