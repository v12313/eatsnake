#include<stdio.h>
#include<stdlib.h>
#include<windows.h> // 光标设置的api
#include<time.h>//食物随机
#include <conio.h>//按键监控
//辅助宏定义
#define mapheight 25
#define mapwidth 60
#define snakesize 50


//数据设计
struct  
{
	int x, y;

}food;
//蛇的结构体
struct 
{
	//记录每一节蛇的坐标
	int x[snakesize];
	int y[snakesize];
	int len;
	int speed;
}snake;

//全局变量
int key = 'w'; //初始化移动方向
int changflag = 0;//蛇的变化标志

//函数设计-》功能划分 -》抽象到函数
//怎么抽象：了解具体业务逻辑
// 1、画地图
void drawmap()
{
	void gotxy(int x, int y);
	srand((unsigned int)time(NULL));// 随机函数种子
	//食物●   蛇身■
	//1、圈地
	//左右边框
	for (int i =0;i<=mapheight;i++)
	{
		gotxy(0, i);
		printf("■");
		gotxy(mapwidth, i);
		printf("■");
	}
	// 上下边框
	for (int i=0;i<=mapwidth;i+=2)
	{
		gotxy(i,0 );
		printf("■");
		gotxy(i, mapheight);
		printf("■");
	}
	//2、画蛇
	snake.len = 3;
	snake.speed = 300;
	//蛇头 在屏幕中间
	snake.x[0] = mapwidth / 2;
	snake.y[0] = mapheight / 2;
	gotxy(snake.x[0], snake.y[0]);
	printf("■");
	for (int k=1;k<snake.len;k++)
	{
		snake.x[k] = snake.x[k - 1] + 2;
		snake.y[k] = snake.y[k - 1];
		gotxy(snake.x[k], snake.y[k]);
		printf("■");
	}
	//3、画食物
		//3.1确定坐标
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
	
	
		//3.2画出来
	gotxy(food.x, food.y);
	printf("●");
	gotxy(mapheight + 2, 0);
}
//2、食物的产生
void createfood()
{
	//蛇把食物吃了
	
	if (snake.x[0]==food.x &&snake.y[0]==food.y)
	{
		snake.len++;
		changflag = 1;
		//gotxy(food.x, food.y);
		//printf("■");
		srand((unsigned int)time(NULL));
		int flag=1;
		//产生的食物不能在蛇的身上，并且坐标要是偶数
		while (flag)
		{
			food.x = rand() % (mapwidth - 4) + 2;
			food.y = rand() % (mapheight - 2) + 1;
			//产生新的食物不能在蛇的身上
			if (food.x % 2 == 0)
			{
				for (int k = 0; k < snake.len; k++)
				{
					if (snake.x[k] != food.x && snake.y[0] != food.y)
					{
						if (k == snake.len - 1)
						{
							//flag = 0;
							flag = 0; //食物不合适的标志
							gotxy(food.x, food.y);
							printf("●");
							gotxy(mapheight + 2, 0);
							break;
						}


					}
				}


			}
			

		}
	
	}


}
//3、按键操作
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
	//后面的结蛇身
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
	printf("■");
	changflag = 0;
	gotxy(mapheight + 2, 0);
}
//蛇的状态，判断是否结束
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
//辅助函数-》光标移动
void gotxy(int x, int y)//现在已经淘汰，需要自己实现
{
	//调用win32API，去设置控制台的光标位置
	//1、找到控制台的这个窗口
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//光标结构体
	COORD coord;
	// 2、设置坐标
	coord.X = x;
	coord.Y = y;
	//同步到控制台
	SetConsoleCursorPosition(handle,coord);
}

//
//模块化设计
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