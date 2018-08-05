#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include "init.h"
#include "judge.h"

#define U 1
#define D 2
#define L 3 
#define R 4 //�ߵ�״̬��U���� ��D���£�L:�� R����



//ȫ�ֱ���//
int status, sleeptime = 200;//��ÿ���ƶ���ʱ����200ms
snake *food;//ʳ��ָ��
snake *q;//�����ߵ�ʱ���õ���ָ��



void createfood()//�������ʳ�xҲ��ֻ����ż��(2-54)
{
	snake *food_1;
	srand((unsigned)time(NULL));
	//��ʼ��x����
	food_1 = (snake*)malloc(sizeof(snake));
	while ((food_1->x % 2) != 0) //��֤��Ϊż����ʹ��ʳ��������ͷ����
	{
		food_1->x = rand() % 52 + 2;
	}
	food_1->y = rand() % 24 + 1;
	q = head;
	while (q->next == NULL)
	{
		if (q->x == food_1->x && q->y == food_1->y) //�ж������Ƿ���ʳ���غ�
		{
			//�ͷ�ʳ��ڵ�
			free(food_1);
			createfood();
		}
		q = q->next;
	}
	Pos(food_1->x, food_1->y);
	food = food_1;
	SetColor(4);
	printf("��");
}



void snakemove()//��ǰ��,��U,��D,��L,��R
{
	snake * nexthead;
	//���ܴ�ǽ
	cantcrosswall();

	nexthead = (snake*)malloc(sizeof(snake));
	//ÿ�δӼ����õ�һ���¼����Ը��¼�������Ӧ
	if (status == U)
	{
		nexthead->x = head->x;
		nexthead->y = head->y - 1;
		if (nexthead->x == food->x && nexthead->y == food->y)//�����һ����ʳ�ͷ����һ����㣬����Ĳ���//
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				SetColor(6);
				printf("��");
				q = q->next;
			}
			score = score + point;
			createfood();
		}
		else //���û��ʳ�ͷ����ǰ�ƶ�������Ľ�����μ̳�ǰһ������������Ϣ�����һ���ڵ�ԭ����λ�����//
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				SetColor(9);
				printf("��");
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
		if (nexthead->x == food->x && nexthead->y == food->y) //��ʳ��
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				SetColor(6);
				printf("��");
				q = q->next;
			}
			score = score + point;
			createfood();
		}
		else //û��ʳ��
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				SetColor(12);
				printf("��");
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
		if (nexthead->x == food->x && nexthead->y == food->y)//��ʳ��
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				SetColor(6);
				printf("��");
				q = q->next;
			}
			score = score + point;
			createfood();
		}
		else //û��ʳ��
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				SetColor(14);
				printf("��");
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
		if (nexthead->x == food->x && nexthead->y == food->y)//��ʳ��
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL)
			{
				Pos(q->x, q->y);
				SetColor(6);
				printf("��");
				q = q->next;
			}
			score = score + point;
			createfood();
		}
		else //û��ʳ��
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				SetColor(6);
				printf("��");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf(" ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (biteself() == 1) //�ж��Ƿ��ҧ���Լ�
	{
		gameoverflag = 2;
		endgame();
	}
}


//����Ϸ
void gameplay()
{

	Pos(64, 15);
	SetColor(6);
	printf("���ܴ�ǽ������ҧ���Լ�\n");
	Pos(64, 16);
	SetColor(7);
	printf("�á�.��.��.���ֱ�����ߵ��ƶ�.");
	Pos(64, 17);
	SetColor(8);
	printf("F1 Ϊ���٣�F2 Ϊ����\n");
	Pos(64, 18);
	SetColor(9);
	printf("ESC ���˳���Ϸ.space����ͣ��Ϸ.");
	Pos(64, 20);
	SetColor(10);
	printf("~~**~~");
	status = R;
	while (1)
	{
		Pos(64, 10);
		printf("�÷֣�%d ", score);
		Pos(64, 11);
		printf("ÿ��ʳ��÷֣�%d��", point);
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
		//���٣�������С�����ƶ��¼�֮�����Ӧ�ٶȣ���Ӧʱ�䣩
		else if (GetAsyncKeyState(VK_F1))
		{
			if (sleeptime >= 50)
			{
				//ÿ�μ�ȥ30ms
				sleeptime = sleeptime - 30;
				//���ٽ�����,�Ժ�Ե�ʳ���ӷ�
				point = point + 2;
			}
		}
		//���٣��������������ƶ��¼�֮�����Ӧ�ٶȣ���Ӧʱ�䣩
		else if (GetAsyncKeyState(VK_F2))
		{
			if (sleeptime<350)
			{
				sleeptime = sleeptime + 30;
				//�����Ѷ��½����Ժ�Ե�ʳ��ּ���
				point= point- 2;
				if (sleeptime == 350)
				{
					point= 1; //��֤��ͷ�Ϊ1
				}
			}
		}
		//ˢ���¼��������¼�֮����sleeptime�ĺ���
		Sleep(sleeptime);
		snakemove();
	}
}



void game_init()//��Ϸ��ʼ��
{
	system("mode con cols=100 lines=30");
	welcomepage();
	Map_create();
	Snakeinit();
	createfood();
}

int main()
{
	//��ʼ����Ϸ
	game_init();
	//��ʼ����Ϸ
	gameplay();
	return 0;
}