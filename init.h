// 定义蛇身节点
typedef struct SNAKE{
	int x;
	int y;
	struct SNAKE*next;
}snake;
snake *head;	//头指针
//设置光标位置
void Pos(int x, int y)
{
	//坐标类型结构体
	COORD pos;
	pos.X = x;
	pos.Y = y;
	//定义并初始化句柄
	HANDLE Houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	//设置光标位置
	SetConsoleCursorPosition(Houtput, pos);
}

void SetColor(int color_num) //需包含头文件windows.h
{
	using namespace std;
	HANDLE color; //声明一个句柄
	color = GetStdHandle(STD_OUTPUT_HANDLE); //取得标准输出句柄
	SetConsoleTextAttribute(color, color_num);
	//设置颜色函数SetConsoleTextAttribute有两个参数，第一个为句柄，第二个为颜色代表值 
	//可以使用「|」在第二个参数所填颜色间隔开，实现混色
}

//欢迎界面
void welcomepage()
{
	Pos(40, 12);
	SetColor(6);
	printf("~~欢迎来到兰航的贪吃蛇游戏~~");
	Pos(40, 25);
	printf("用↑，↓，←，→控制蛇的移动\n");
	system("pause");
	system("cls");
}
//初始化地图58/2=29列26行
void Map_create()
{
	int i;
	//■占两个字符的位置(光标移动一位对应一个字符，两个字符光标每次移动两位，也就是坐标值每次加2，一个坐标值对应一个字符位)
	//上下 
	for (i = 0; i < 58; i += 2)
	{
		//移动光标
		Pos(i, 0);
		SetColor(4);
		//每个坐标值是一个字符大小，每个正方形占两个字符的大小。
		printf("■");
		Pos(i, 26);
		SetColor(6);
		printf("■");
	}
	//左右	y取1,2,3...25
	for (i = 0; i < 26; i++)
	{
		//移动光标
		Pos(0, i);
		SetColor(4);
		printf("■");
		Pos(56, i);
		SetColor(6);
		printf("■");
	}
	printf("\n");
}

//初始化蛇身,x,y坐标的取值范围57和25，x只能取0，2，4，6.。。
void Snakeinit()
{
	snake *tail;	//尾指针，用来操纵尾结点（每个指针指向一个正方形）
	int i;
	tail = (snake*)malloc(sizeof(snake));	//初始化尾指针,采用头插法
	tail->x = 24;	//这个设定注定头节点的x坐标只能是偶数，即初始化的第一个正方形的坐标奇偶性决定了以后每个结点x坐标的奇偶性（每次左右移动两个字符大小，不改奇偶性）
	tail->y = 5;	//y坐标任意
	tail->next = NULL;
	//生成五节长的小蛇
	for (i = 1; i <= 4; i++)
	{
		//生成头指针,每次将头指针赋值给尾指针，使蛇增加一节,前面的节已经链在了链表中
		head = (snake*)malloc(sizeof(snake));
		head->next = tail;
		head->x = 24 + 2 * i;
		head->y = 5;
		tail = head;
	}
	//此时尾指针指向头部
	//从头部开始打印小蛇
	while (tail != NULL)
	{
		//修改光标
		Pos(tail->x, tail->y);
		SetColor(2);
		printf("■");
		tail = tail->next;
	}


}