#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include "init.h"
#include "judge.h"

#define U 1
#define D 2
#define L 3 
#define R 4 //蛇的状态，U：上 ；D：下；L:左 R：右



//全局变量//
int status, sleeptime = 200;//蛇每次移动的时间间隔200ms
snake *food;//食物指针
snake *q;//遍历蛇的时候用到的指针



void createfood()//随机出现食物，x也是只能是偶数(2-54)
{
	snake *food_1;
	srand((unsigned)time(NULL));
	//初始化x坐标
	food_1 = (snake*)malloc(sizeof(snake));
	while ((food_1->x % 2) != 0) //保证其为偶数，使得食物能与蛇头对其
	{
		food_1->x = rand() % 52 + 2;
	}
	food_1->y = rand() % 24 + 1;
	q = head;
	while (q->next == NULL)
	{
		if (q->x == food_1->x && q->y == food_1->y) //判断蛇身是否与食物重合
		{
			//释放食物节点
			free(food_1);
			createfood();
		}
		q = q->next;
	}
	Pos(food_1->x, food_1->y);
	food = food_1;
	SetColor(4);
	printf("■");
}



void snakemove()//蛇前进,上U,下D,左L,右R
{
	snake * nexthead;
	//不能穿墙
	cantcrosswall();

	nexthead = (snake*)malloc(sizeof(snake));
	//每次从键盘拿到一个事件，对该事件进行响应
	if (status == U)
	{
		nexthead->x = head->x;
		nexthead->y = head->y - 1;
		if (nexthead->x == food->x && nexthead->y == food->y)//如果下一个有食物，头部加一个结点，其余的不动//
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				SetColor(6);
				printf("■");
				q = q->next;
			}
			score = score + point;
			createfood();
		}
		else //如果没有食物，头部向前移动，其余的结点依次继承前一个结点的坐标信息，最后一个节点原来的位置清空//
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				SetColor(9);
				printf("■");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf(" ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == D)
	{
		nexthead->x = head->x;
		nexthead->y = head->y + 1;
		if (nexthead->x == food->x && nexthead->y == food->y) //有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				SetColor(6);
				printf("■");
				q = q->next;
			}
			score = score + point;
			createfood();
		}
		else //没有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				SetColor(12);
				printf("■");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf(" ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == L)
	{
		nexthead->x = head->x - 2;
		nexthead->y = head->y;
		if (nexthead->x == food->x && nexthead->y == food->y)//有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				SetColor(6);
				printf("■");
				q = q->next;
			}
			score = score + point;
			createfood();
		}
		else //没有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				SetColor(14);
				printf("■");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf(" ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == R)
	{
		nexthead->x = head->x + 2;
		nexthead->y = head->y;
		if (nexthead->x == food->x && nexthead->y == food->y)//有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				SetColor(6);
				printf("■");
				q = q->next;
			}
			score = score + point;
			createfood();
		}
		else //没有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				SetColor(6);
				printf("■");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf(" ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (biteself() == 1) //判断是否会咬到自己
	{
		gameoverflag = 2;
		endgame();
	}
}


//玩游戏
void gameplay()
{

	Pos(64, 15);
	SetColor(6);
	printf("不能穿墙，不能咬到自己\n");
	Pos(64, 16);
	SetColor(7);
	printf("用↑.↓.←.→分别控制蛇的移动.");
	Pos(64, 17);
	SetColor(8);
	printf("F1 为加速，F2 为减速\n");
	Pos(64, 18);
	SetColor(9);
	printf("ESC ：退出游戏.space：暂停游戏.");
	Pos(64, 20);
	SetColor(10);
	printf("~~**~~");
	status = R;
	while (1)
	{
		Pos(64, 10);
		printf("得分：%d ", score);
		Pos(64, 11);
		printf("每个食物得分：%d分", point);
		if (GetAsyncKeyState(VK_UP) && status != D)
		{
			status = U;
		}
		else if (GetAsyncKeyState(VK_DOWN) && status != U)
		{
			status = D;
		}
		else if (GetAsyncKeyState(VK_LEFT) && status != R)
		{
			status = L;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && status != L)
		{
			status = R;
		}
		else if (GetAsyncKeyState(VK_SPACE))
		{
			game_pause();
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			gameoverflag = 3;
			endgame();
		}
		//加速，就是缩小两次移动事件之间的响应速度（反应时间）
		else if (GetAsyncKeyState(VK_F1))
		{
			if (sleeptime >= 50)
			{
				//每次减去30ms
				sleeptime = sleeptime - 30;
				//加速奖励分,以后吃到食物多加分
				point = point + 2;
			}
		}
		//减速，就是增加两次移动事件之间的响应速度（反应时间）
		else if (GetAsyncKeyState(VK_F2))
		{
			if (sleeptime<350)
			{
				sleeptime = sleeptime + 30;
				//减速难度下降，以后吃到食物分减少
				point= point- 2;
				if (sleeptime == 350)
				{
					point= 1; //保证最低分为1
				}
			}
		}
		//刷新事件，两次事件之间间隔sleeptime的毫秒
		Sleep(sleeptime);
		snakemove();
	}
}



void game_init()//游戏初始化
{
	system("mode con cols=100 lines=30");
	welcomepage();
	Map_create();
	Snakeinit();
	createfood();
}

int main()
{
	//初始化游戏
	game_init();
	//开始玩游戏
	gameplay();
	return 0;
}