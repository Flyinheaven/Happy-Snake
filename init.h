// ��������ڵ�
typedef struct SNAKE{
	int x;
	int y;
	struct SNAKE*next;
}snake;
snake *head;	//ͷָ��
//���ù��λ��
void Pos(int x, int y)
{
	//�������ͽṹ��
	COORD pos;
	pos.X = x;
	pos.Y = y;
	//���岢��ʼ�����
	HANDLE Houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	//���ù��λ��
	SetConsoleCursorPosition(Houtput, pos);
}

void SetColor(int color_num) //�����ͷ�ļ�windows.h
{
	using namespace std;
	HANDLE color; //����һ�����
	color = GetStdHandle(STD_OUTPUT_HANDLE); //ȡ�ñ�׼������
	SetConsoleTextAttribute(color, color_num);
	//������ɫ����SetConsoleTextAttribute��������������һ��Ϊ������ڶ���Ϊ��ɫ����ֵ 
	//����ʹ�á�|���ڵڶ�������������ɫ�������ʵ�ֻ�ɫ
}

//��ӭ����
void welcomepage()
{
	Pos(40, 12);
	SetColor(6);
	printf("~~��ӭ����������̰������Ϸ~~");
	Pos(40, 25);
	printf("�á������������������ߵ��ƶ�\n");
	system("pause");
	system("cls");
}
//��ʼ����ͼ58/2=29��26��
void Map_create()
{
	int i;
	//��ռ�����ַ���λ��(����ƶ�һλ��Ӧһ���ַ��������ַ����ÿ���ƶ���λ��Ҳ��������ֵÿ�μ�2��һ������ֵ��Ӧһ���ַ�λ)
	//���� 
	for (i = 0; i < 58; i += 2)
	{
		//�ƶ����
		Pos(i, 0);
		SetColor(4);
		//ÿ������ֵ��һ���ַ���С��ÿ��������ռ�����ַ��Ĵ�С��
		printf("��");
		Pos(i, 26);
		SetColor(6);
		printf("��");
	}
	//����	yȡ1,2,3...25
	for (i = 0; i < 26; i++)
	{
		//�ƶ����
		Pos(0, i);
		SetColor(4);
		printf("��");
		Pos(56, i);
		SetColor(6);
		printf("��");
	}
	printf("\n");
}

//��ʼ������,x,y�����ȡֵ��Χ57��25��xֻ��ȡ0��2��4��6.����
void Snakeinit()
{
	snake *tail;	//βָ�룬��������β��㣨ÿ��ָ��ָ��һ�������Σ�
	int i;
	tail = (snake*)malloc(sizeof(snake));	//��ʼ��βָ��,����ͷ�巨
	tail->x = 24;	//����趨ע��ͷ�ڵ��x����ֻ����ż��������ʼ���ĵ�һ�������ε�������ż�Ծ������Ժ�ÿ�����x�������ż�ԣ�ÿ�������ƶ������ַ���С��������ż�ԣ�
	tail->y = 5;	//y��������
	tail->next = NULL;
	//������ڳ���С��
	for (i = 1; i <= 4; i++)
	{
		//����ͷָ��,ÿ�ν�ͷָ�븳ֵ��βָ�룬ʹ������һ��,ǰ��Ľ��Ѿ�������������
		head = (snake*)malloc(sizeof(snake));
		head->next = tail;
		head->x = 24 + 2 * i;
		head->y = 5;
		tail = head;
	}
	//��ʱβָ��ָ��ͷ��
	//��ͷ����ʼ��ӡС��
	while (tail != NULL)
	{
		//�޸Ĺ��
		Pos(tail->x, tail->y);
		SetColor(2);
		printf("��");
		tail = tail->next;
	}


}