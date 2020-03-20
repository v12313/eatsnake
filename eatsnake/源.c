#include<stdio.h>
#include<stdlib.h>
#include<windows.h> // ������õ�api
#include<time.h>//ʳ�����
#include <conio.h>//�������
//�����궨��
#define mapheight 25
#define mapwidth 60
#define snakesize 50


//�������
struct  
{
	int x, y;

}food;
//�ߵĽṹ��
struct 
{
	//��¼ÿһ���ߵ�����
	int x[snakesize];
	int y[snakesize];
	int len;
	int speed;
}snake;

//ȫ�ֱ���
int key = 'w'; //��ʼ���ƶ�����
int changflag = 0;//�ߵı仯��־

//�������-�����ܻ��� -�����󵽺���
//��ô�����˽����ҵ���߼�
// 1������ͼ
void drawmap()
{
	void gotxy(int x, int y);
	srand((unsigned int)time(NULL));// �����������
	//ʳ���   �����
	//1��Ȧ��
	//���ұ߿�
	for (int i =0;i<=mapheight;i++)
	{
		gotxy(0, i);
		printf("��");
		gotxy(mapwidth, i);
		printf("��");
	}
	// ���±߿�
	for (int i=0;i<=mapwidth;i+=2)
	{
		gotxy(i,0 );
		printf("��");
		gotxy(i, mapheight);
		printf("��");
	}
	//2������
	snake.len = 3;
	snake.speed = 300;
	//��ͷ ����Ļ�м�
	snake.x[0] = mapwidth / 2;
	snake.y[0] = mapheight / 2;
	gotxy(snake.x[0], snake.y[0]);
	printf("��");
	for (int k=1;k<snake.len;k++)
	{
		snake.x[k] = snake.x[k - 1] + 2;
		snake.y[k] = snake.y[k - 1];
		gotxy(snake.x[k], snake.y[k]);
		printf("��");
	}
	//3����ʳ��
		//3.1ȷ������
	int flag = 1;
	while (flag)
	{
		food.x = rand() % (mapwidth - 4) + 2;
		food.y = rand() % (mapheight - 2) + 1;
		if (food.x%2==0)
		{
			flag = 0;
		}

	}
	
	
		//3.2������
	gotxy(food.x, food.y);
	printf("��");
	gotxy(mapheight + 2, 0);
}
//2��ʳ��Ĳ���
void createfood()
{
	//�߰�ʳ�����
	
	if (snake.x[0]==food.x &&snake.y[0]==food.y)
	{
		snake.len++;
		changflag = 1;
		//gotxy(food.x, food.y);
		//printf("��");
		srand((unsigned int)time(NULL));
		int flag=1;
		//������ʳ�ﲻ�����ߵ����ϣ���������Ҫ��ż��
		while (flag)
		{
			food.x = rand() % (mapwidth - 4) + 2;
			food.y = rand() % (mapheight - 2) + 1;
			//�����µ�ʳ�ﲻ�����ߵ�����
			if (food.x % 2 == 0)
			{
				for (int k = 0; k < snake.len; k++)
				{
					if (snake.x[k] != food.x && snake.y[0] != food.y)
					{
						if (k == snake.len - 1)
						{
							//flag = 0;
							flag = 0; //ʳ�ﲻ���ʵı�־
							gotxy(food.x, food.y);
							printf("��");
							gotxy(mapheight + 2, 0);
							break;
						}


					}
				}


			}
			

		}
	
	}


}
//3����������
void keydown()
{

	if (_kbhit())
	{
		fflush(stdin);
		key = _getch();
	}
	if (!changflag)
	{
		gotxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
		printf("  ");
		gotxy(mapheight + 2, 0);
	}
	//����Ľ�����
	for (int i = snake.len - 1; i > 0; i--)
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}
	switch (key)
	{
	case 'w':
	case 'W':
		snake.y[0]--;
		break;
	case 's':
	case 'S':
		snake.y[0]++;
		break;
	case 'a':
	case 'A':
		snake.x[0] -= 2;
		break;
	case 'd':
	case 'D':
		snake.x[0] += 2;
		break;
	default:
		break;
	}
	gotxy(snake.x[0], snake.y[0]);
	printf("��");
	changflag = 0;
	gotxy(mapheight + 2, 0);
}
//�ߵ�״̬���ж��Ƿ����
int snakestatis()
{
	if (snake.x[0] == 0 || snake.x[0] == mapwidth - 2 || snake.y[0] == 0 || snake.y[0] == mapheight - 1) return 0;
	for (int k=1;k<snake.len;k++)
	{
		if (snake.x[0]==snake.x[k]&&snake.y[0]==snake.y[k])
		{
			return 0;
		}
	}
	
	return 1;
}
//��������-������ƶ�
void gotxy(int x, int y)//�����Ѿ���̭����Ҫ�Լ�ʵ��
{
	//����win32API��ȥ���ÿ���̨�Ĺ��λ��
	//1���ҵ�����̨���������
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//���ṹ��
	COORD coord;
	// 2����������
	coord.X = x;
	coord.Y = y;
	//ͬ��������̨
	SetConsoleCursorPosition(handle,coord);
}

//
//ģ�黯���
int main()
{
	drawmap();
	//printf("gameover");
	while (1)
	{
		createfood();
		Sleep(snake.speed);
		keydown();
		if (!snakestatis())
		{
			break;
		}
	}
	gotxy(mapheight / 2, mapwidth / 2);
	printf("gameover\r\n");
	system("pause");
	return 0;
}