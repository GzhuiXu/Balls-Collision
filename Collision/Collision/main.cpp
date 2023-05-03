/*开发日志
* 1、小球类
* 成员属性：半径大小、球心位置、速度、颜色
* 成员方法：设置属性、查询属性
* 静态属性：对象数量
* 静态方法：统计对象数量、显示所有对象、判断碰撞、更新所有对象
* 2、边界类
*/


#include <iostream>
#include <random>
#include <ctime>
#include <conio.h>
#include <stdio.h>
#include "Ball.h"

int main()
{
	//生成随机数
	std::default_random_engine e;
	e.seed(time(0));
	std::uniform_int_distribution<int> randX(EDGE_X, WIDTH - EDGE_X);
	std::uniform_int_distribution<int> randY(EDGE_Y, HEIGHT - EDGE_Y);
	std::uniform_int_distribution<int> randR(10, 20);
	std::uniform_int_distribution<int> randV(100, 200);
	std::uniform_int_distribution<int> randA(10, 330);

	//窗口初始化
	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();

	//创建对象
	Ball* pBalls = new Ball[10];
	for (int i = 0; i < 10; i++)
	{
		*(pBalls + i) = Ball(randR(e), randA(e), 100, randX(e), randY(e));
	}
	
	//游戏循环
	while (1)
	{
		Ball::solveBallCollision(pBalls);
		Ball::moveBalls(pBalls);
		Ball::drawBalls(pBalls);
		Sleep(static_cast<int>(1000 * AMP / 1000));
		cleardevice();
	}
	
	//释放对象
	delete [] pBalls;

	//结束窗口
	getmessage(EX_CHAR);
	EndBatchDraw();
	closegraph();

}
