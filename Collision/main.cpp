/*������־
* 1��С����
* ��Ա���ԣ��뾶��С������λ�á��ٶȡ���ɫ
* ��Ա�������������ԡ���ѯ����
* ��̬���ԣ���������
* ��̬������ͳ�ƶ�����������ʾ���ж����ж���ײ���������ж���
* 2���߽���
*/


#include <iostream>
#include <random>
#include <ctime>
#include <conio.h>
#include <stdio.h>
#include "Ball.h"

int main()
{
	//���������
	std::default_random_engine e;
	e.seed(time(0));
	std::uniform_int_distribution<int> randX(EDGE_X, WIDTH - EDGE_X);
	std::uniform_int_distribution<int> randY(EDGE_Y, HEIGHT - EDGE_Y);
	std::uniform_int_distribution<int> randR(10, 20);
	std::uniform_int_distribution<int> randV(100, 200);
	std::uniform_int_distribution<int> randA(10, 330);

	//���ڳ�ʼ��
	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();

	//��������
	Ball* pBalls = new Ball[10];
	for (int i = 0; i < 10; i++)
	{
		*(pBalls + i) = Ball(randR(e), randA(e), 100, randX(e), randY(e));
	}
	
	//��Ϸѭ��
	while (1)
	{
		Ball::solveBallCollision(pBalls);
		Ball::moveBalls(pBalls);
		Ball::drawBalls(pBalls);
		Sleep(static_cast<int>(1000 * AMP / 1000));
		cleardevice();
	}
	
	//�ͷŶ���
	delete [] pBalls;

	//��������
	getmessage(EX_CHAR);
	EndBatchDraw();
	closegraph();

}
