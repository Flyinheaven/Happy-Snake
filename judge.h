int gameoverflag = 0; //��Ϸ�����������1��ײ��ǽ��2��ҧ���Լ���3�������˳���Ϸ��
int score = 0, point = 10;//�ܵ÷���ÿ�γ�ʳ��÷֡�

int biteself()//�ж��Ƿ�ҧ�����Լ����ж���û�к�ͷ����غϵĽ��
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


void endgame()//������Ϸ��������״̬
{

	system("cls");
	Pos(24, 12);
	if (gameoverflag== 1)
	{
		printf("�Բ�����ײ��ǽ�ˡ���Ϸ����.");
	}
	else if (gameoverflag == 2)
	{
		printf("�Բ�����ҧ���Լ��ˡ���Ϸ����.");
	}
	else if (gameoverflag== 3)
	{
		printf("�����Ѿ���������Ϸ��");
	}
	Pos(24, 13);
	printf("���ĵ÷���%d\n", score);
	exit(0);
}


void cantcrosswall()//���ܴ�ǽ
{
	if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26)
	{
		gameoverflag = 1;
		endgame();
	}
}

void game_pause()//��ͣ
{
	while (1)
	{
		Sleep(300);
		//һֱ��˯��ֱ�����½�����
		if (GetAsyncKeyState(VK_SPACE))
		{
			break;
		}

	}
}

