#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define RIGHT 3
#define LEFT 0
#define UP 0
#define DOWN 3

int _2048[4][4];

int Display(void);//显示操作 
int MakeEmpty(void);//清空地图 
int Init(void);//初始化操作 
int Random(void);//地图随机生成2或4 
int Move(char Mode);//数字的移动 
int FindMax(void);//找到地图中的最大数，作为分数 
int Play(void);//第二Main函数 
int GameOver(void);//游戏结束 
int End(void);//最终选择 

int main(void)
{
	srand((unsigned)time(NULL));
	PlayAgain:
	Init();
	Play();
	if(End())
	{
		goto PlayAgain;
	}
	return 0;
}

int Init(void)
{
	MakeEmpty();
	return _2048[rand()%4][rand()%4] = Random();
}

int MakeEmpty(void)
{
	int x,y;
	for(x = 0;x < 4;x++)
	{
		for(y = 0;y < 4;y++)
		{
			_2048[x][y] = 0;
		}
	}
	return 0;
}

int Move(char Mode)
{
	int x,y;
	int Tmp; 
	switch(Mode)
	{
		case 'A':
		case 'a':
		{
			for(x = LEFT;x <= RIGHT;x++)
			{
				for(y = UP;y <= DOWN;y++)
				{
					Tmp = x;
					if(_2048[Tmp-1][y] == _2048[Tmp][y])
					{
						_2048[Tmp-1][y] *= 2;
						_2048[Tmp][y] = 0;
					}
					while(!_2048[Tmp-1][y] && Tmp-1 >= LEFT)
					{
						_2048[Tmp-1][y] = _2048[Tmp][y];
						_2048[Tmp][y] = 0;
						Tmp--;
					}
					if(_2048[Tmp-1][y] == _2048[Tmp][y])
					{
						_2048[Tmp-1][y] *= 2;
						_2048[Tmp][y] = 0;
					}
				}
			}
			break;
		}
		case 'D':
		case 'd':
		{
			for(x = RIGHT;x >= LEFT;x--)
			{
				for(y = UP;y <= DOWN;y++)
				{
					Tmp = x;
					if(_2048[Tmp+1][y] == _2048[Tmp][y])
					{
						_2048[Tmp+1][y] *= 2;
						_2048[Tmp][y] = 0;
					}
					while(!_2048[Tmp+1][y] && Tmp+1 <= RIGHT)
					{
						_2048[Tmp+1][y] = _2048[Tmp][y];
						_2048[Tmp][y] = 0;
						Tmp++;
					}
					if(_2048[Tmp+1][y] == _2048[Tmp][y])
					{
						_2048[Tmp+1][y] *= 2;
						_2048[Tmp][y] = 0;
					}
				}
			}
			break;
		}
		case 'W':
		case 'w':
		{
			for(x = LEFT;x <= RIGHT;x++)
			{
				for(y = UP;y <= DOWN;y++)
				{
					Tmp = y;
					if(_2048[x][Tmp-1] == _2048[x][Tmp])
					{
						_2048[x][Tmp-1] *= 2;
						_2048[x][Tmp] = 0;
					}
					while(!_2048[x][Tmp-1] && Tmp-1 >= UP)
					{
						_2048[x][Tmp-1] = _2048[x][Tmp];
						_2048[x][Tmp] = 0;
						Tmp--;
					}
					if(_2048[x][Tmp-1] == _2048[x][Tmp])
					{
						_2048[x][Tmp-1] *= 2;
						_2048[x][Tmp] = 0;
					}
				}
			}
			break;
		}
		case 'S':
		case 's': 
		{
			for(x = LEFT;x <= RIGHT;x++)
			{
				for(y = DOWN;y >= UP;y--)
				{
					Tmp = y;
					if(_2048[x][Tmp+1] == _2048[x][Tmp])
					{
						_2048[x][Tmp+1] *= 2;
						_2048[x][Tmp] = 0;
					}
					while(!_2048[x][Tmp+1] && Tmp+1 <= DOWN)
					{
						_2048[x][Tmp+1] = _2048[x][Tmp];
						_2048[x][Tmp] = 0;
						Tmp++;
					}
					if(_2048[x][Tmp+1] == _2048[x][Tmp])
					{
						_2048[x][Tmp+1] *= 2;
						_2048[x][Tmp] = 0;
					}
				}
			}
			break;
		}
		default:return 1;
	}
	return 0;
}

int Play(void)
{
	char Enter;
	int x,y; 
	while(1)
	{
		Display();
		Enter = getch();
		Move(Enter);
		if(!GameOver())
		{
			break;
		}
		do
		{
			x = rand()%4;
			y = rand()%4;
		}while(_2048[x][y]);
		_2048[x][y] = Random();
		system("cls");
	}
	return;
}

int Random(void)
{
	return (rand()%4 == 0)?4:2;
}

int FindMax(void)
{
	int Max = _2048[0][0];
	int xPos,yPos;
	for(xPos = 0;xPos < 4;xPos++)
	{
		for(yPos = 0;yPos < 4;yPos++)
		{
			if(_2048[xPos][yPos] > Max)
			{
				Max = _2048[xPos][yPos];
			}
		}
	}
	return Max;
}

int GameOver(void)
{
	int x,y;
	int count;
	for(x = 0;x < 4;x++)
	{
		for(y = 0;y < 4;y++)
		{
			if(_2048[x][y])
			{
				count++;
			}
		}
	}
	if(count == 4*4)
	{
		for(x = 0;x < 4;x++)
		{
			for(y = 0;y < 4;y++)
			{
				if(_2048[x][y] == _2048[x+1][y] || _2048[x][y] == _2048[x][y+1])
				{
					return 1;
				}
			}
		}
		return 0;
	}
	return 1;
}

int Display(void)
{
	printf("\n\n\n\t\t\t          2048         ");
	printf("\n\n\n\t\t\t---------------------------\n");
	printf("\t\t\t┏━━┳━━┳━━┳━━┓\n");
	printf("\t\t\t┃%4d┃%4d┃%4d┃%4d┃\n",_2048[0][0],_2048[1][0],_2048[2][0],_2048[3][0]);
	printf("\t\t\t┣━━╋━━╋━━╋━━┫\n");
	printf("\t\t\t┃%4d┃%4d┃%4d┃%4d┃\n",_2048[0][1],_2048[1][1],_2048[2][1],_2048[3][1]);
	printf("\t\t\t┣━━╋━━╋━━╋━━┫\n");
	printf("\t\t\t┃%4d┃%4d┃%4d┃%4d┃\n",_2048[0][2],_2048[1][2],_2048[2][2],_2048[3][2]);
	printf("\t\t\t┣━━╋━━╋━━╋━━┫\n");
	printf("\t\t\t┃%4d┃%4d┃%4d┃%4d┃\n",_2048[0][3],_2048[1][3],_2048[2][3],_2048[3][3]);
	printf("\t\t\t┗━━┻━━┻━━┻━━┛\n");
	printf("\t\t\t---------------------------\n");
	printf("\t\t\t分数:%5d            \n\n",FindMax());
	printf("\t\t\t操作: W:↑ S:↓ A:← D:→\n\n");
	system("color E");
	return 0;
}

int End(void)
{
	int ch = 0;
	system("cls");
	printf("游戏结束!\n");
	printf("最终分数:%d\n\n",FindMax());
	printf("1.退出游戏.\n\n2.再来一局.\n\n");
	
	do
	{
		scanf("%d",&ch);
	}while(ch != 1 && ch != 2);
	
	switch(ch)
	{
		case 1:return 0;
		case 2:return 1;
	}
	return (int)("Impossible");
}
