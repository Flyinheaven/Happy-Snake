int gameoverflag = 0; //游戏分三种情况，1：撞到墙；2：咬到自己；3：主动退出游戏。
int score = 0, point = 10;//总得分与每次吃食物得分。

int biteself()//判断是否咬到了自己，判断有没有和头结点重合的结点
{
	snake *self;
	self = head->next;
	while (self != NULL)
	{
		if (self->x == head->x && self->y == head->y)
		{
			return 1;
		}
		self = self->next;
	}
	return 0;
}


void endgame()//结束游戏，分三种状态
{

	system("cls");
	Pos(24, 12);
	if (gameoverflag== 1)
	{
		printf("对不起，您撞到墙了。游戏结束.");
	}
	else if (gameoverflag == 2)
	{
		printf("对不起，您咬到自己了。游戏结束.");
	}
	else if (gameoverflag== 3)
	{
		printf("您的已经结束了游戏。");
	}
	Pos(24, 13);
	printf("您的得分是%d\n", score);
	exit(0);
}


void cantcrosswall()//不能穿墙
{
	if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26)
	{
		gameoverflag = 1;
		endgame();
	}
}

void game_pause()//暂停
{
	while (1)
	{
		Sleep(300);
		//一直沉睡，直到按下结束键
		if (GetAsyncKeyState(VK_SPACE))
		{
			break;
		}

	}
}

