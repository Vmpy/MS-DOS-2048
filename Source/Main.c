#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

int _2048[4][4];

int Score = 0;

int CountZero(int,int,int);
void GameOver(void);
void Start(void);
void Play(void);
void Display(void);

void Seed(void); 
int Random(void);

int Left(void);
int Right(void);
int Down(void);
int Up(void);
int Detection(void);

int main(void)
{
	char choice;
	God:
	srand((unsigned)(time(0)));
	Start();
	Play();
	Sleep(3000);
	GameOver();
	printf("\n\nDo you want to play again?(X\\Y)\n\n");
	Jeez:
	scanf("%c",&choice);
	switch(choice)
	{
		case 'X':
		case 'x': goto God;break;
		case 'Y':
		case 'y':break;
		default:goto Jeez;break;
	}
	return 0;
}

void Start(void)
{
	int count,temp;
	int x,y;
	temp = -1;
	for(count = 0;count < 2;count++){
		loop:
		x = rand() % 4;
		y = rand() % 4;
		if(x == temp){
			goto loop;
		}
		temp = x;
		_2048[x][y] = Random(); 
	}
	for(x = 0;x < 4;x++){
		for(y = 0;y < 4;y++){
			_2048[x][y] = 0;
		}
	}
	Display();
}

void Play(void)
{
	int num;
	char enter;
	while(Detection()){
		enter = getch();
		switch(enter){
			case 'W':Up();break;
			case 'S':Down();break;
			case 'A':Left();break;
			case 'D':Right();break;
			default: continue;
		}
	}
}

int Up(void)
{
	int x,y;
	int decide = 0;                     //判断是否有元素合并 
	for(x = 0;x < 4;x++){
		for(y = 1;y < 4;y++){		//这里的y初始化为1，因为数组第一个元素没有移动意义。
			if(_2048[x][y] == 0){
				continue;
			}
			else if(_2048[x][y-1] == _2048[x][y]){
				Score += (_2048[x][y-1] = _2048[x][y]*2);
				_2048[x][y] = 0;
				decide = 1;
				continue;
			}
			else if(_2048[x][y-2] == _2048[x][y]){
				if(_2048[x][y-1] == 0){						//判断挨近元素是否为空 
					Score += (_2048[x][y-2] = _2048[x][y]*2);
					_2048[x][y] = 0;
					decide = 1;
				}
				continue;
			}
			else if(_2048[x][y-3] == _2048[x][y]){
				if(_2048[x][y-2] == 0 && _2048[x][y-1] == 0){
					Score += (_2048[x][y-3] = _2048[x][y]*2);
					_2048[x][y] = 0;
					decide = 1;
				}
				continue;
			}
			else if(_2048[x][y-1] != 0){
				continue;
			}
			else if(_2048[x][y-1] == 0){
				_2048[x][y-CountZero(1,x,y)] = _2048[x][y];		
				_2048[x][y] = 0;
				decide = 1;
			}
		}
	}
	if(decide){
		Seed();
	}
	system("cls");
	Display();
	return 0; 
}

int Down(void)
{
	int x,y;
	int decide = 0;                     //判断是否有元素合并 
	for(x = 0;x < 4;x++){
		for(y = 0;y < 3;y++){		//这里的y小于3，因为第四号元素无移动意义 
			if(_2048[x][y] == 0){
				continue;
			}
			else if(_2048[x][y+1] == _2048[x][y]){
				Score += (_2048[x][y+1] = _2048[x][y]*2);
				_2048[x][y] = 0;
				decide = 1;
				continue;
			}
			else if(_2048[x][y+2] == _2048[x][y]){
				if(_2048[x][y+1] == 0){
					Score += (_2048[x][y+2] = _2048[x][y]*2);
					_2048[x][y] = 0;
					decide = 1;
				}
				continue;
			}
			else if(_2048[x][y+3] == _2048[x][y]){
				if(_2048[x][y+2] == 0 && _2048[x][y+1] == 0){
					Score += (_2048[x][y+3] = _2048[x][y]*2);
					_2048[x][y] = 0;
					decide = 1;
				}
				continue;
			}
			else if(_2048[x][y+1] != 0){
				continue;
			}
			else if(_2048[x][y+1] == 0){
				_2048[x][y+CountZero(2,x,y)] = _2048[x][y];		
				_2048[x][y] = 0;
				decide = 1;
			}
		}
	}
	if(decide){
		Seed();
	}
	system("cls");
	Display();
	return 0; 
}

int Left(void)
{
	int x,y;
	int decide = 0;                     //判断是否有元素合并 
	for(x = 1;x < 4;x++){				//这里的x从1开始，因为第0号元素无移动意义
		for(y = 0;y < 4;y++){		 
			if(_2048[x][y] == 0){
				continue;
			}
			else if(_2048[x-1][y] == _2048[x][y]){
				Score += (_2048[x-1][y] = _2048[x][y]*2);
				_2048[x][y] = 0;
				decide = 1; 
				continue;
			}
			else if(_2048[x-2][y] == _2048[x][y]){
				if(_2048[x-1][y] == 0){
					Score += (_2048[x-2][y] = _2048[x][y]*2);
					_2048[x][y] = 0;
					decide = 1;
				}
				continue;
			}
			else if(_2048[x-3][y] == _2048[x][y]){
				if(_2048[x-2][y] == 0 && _2048[x-1][y] == 0){
					Score += (_2048[x-3][y] = _2048[x][y]*2);
					_2048[x][y] = 0;
					decide = 1;
				}
				continue;
			}
			else if(_2048[x-1][y] != 0){
				continue;
			}
			else if(_2048[x-1][y] == 0){
				_2048[x-CountZero(3,x,y)][y] = _2048[x][y];		
				_2048[x][y] = 0;
				decide = 1;
			}
		}
	}
	if(decide){
		Seed();
	}
	system("cls");
	Display();
	return 0; 
} 

int Right(void)
{
	int x,y;
	int decide = 0;                     //判断是否有元素合并 
	for(x = 2;x >= 0;x--){				//这里的x从1开始，因为第0号元素无移动意义
		for(y = 0;y < 4;y++){		 
			if(_2048[x][y] == 0){
				continue;
			}
			else if(_2048[x+1][y] == _2048[x][y]){
				Score += (_2048[x+1][y] = _2048[x][y]*2);
				_2048[x][y] = 0;
				decide = 1; 
				continue;
			}
			else if(_2048[x+2][y] == _2048[x][y]){
				if(_2048[x+1][y] == 0){
					Score += (_2048[x+2][y] = _2048[x][y]*2);
					_2048[x][y] = 0;
					decide = 1;
				}
				continue;
			}
			else if(_2048[x+3][y] == _2048[x][y]){
				if(_2048[x+2][y] == 0 && _2048[x+1][y] == 0){
					Score += (_2048[x+3][y] = _2048[x][y]*2);
					_2048[x][y] = 0;
					decide = 1;
				}
				continue;
			}
			else if(_2048[x+1][y] != 0){
				continue;
			}
			else if(_2048[x+1][y] == 0){
				_2048[x+CountZero(4,x,y)][y] = _2048[x][y];		
				_2048[x][y] = 0;
				decide = 1;
			}
		}
	}
	if(decide){
		Seed();
	}
	system("cls");
	Display();
	return 0; 
} 

void Display(void)
{
	printf("\n\n\n\t\t\t         BUGS 2048         ");
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
	printf("\t\t\t分数:%5d            \n\n",Score);
	printf("\t\t\t操作: W:↑ S:↓ A:← D:→\n\n");
	system("color E");
}

int CountZero(int No,int x,int y)
{
	int count = 0;
	int TMP;
	switch(No)
	{
		case 1:{
				for(TMP = 0;TMP < y;TMP++)
				{				//纵向统计 从上至下 
					if(_2048[x][TMP] == 0)
					{
						count++;
					}
				}
				break;
			}
		case 2:{
				for(TMP = 3;TMP > y;TMP--)
				{
					if(_2048[x][TMP] == 0)
					{
						count++;
					}
				}
				break;
			}
		case 3:{
				for(TMP = 0;TMP < x;TMP++){
					if(_2048[TMP][y] == 0){
						count++;
					}
				}
				break;
			} 
		case 4:{
				for(TMP = 3;TMP > x;TMP--){
					if(_2048[TMP][y] == 0){
						count++;
					}
				}
				break;
			}
	}
	return count;
}

int Detection(void)
{
	int x,y;
	int count = 0;
	int check = 0;
	for(x=0;x < 4;x++){
		for(y=0;y < 4;y++){
			if(_2048[x][y] != 0)
			{
				count++;
			}
		}
	}
	/*如果满员*/
	if(count == 16)
	{
		for(x=0;x < 4;x++){
		for(y=0;y < 4;y++){
			if(_2048[x][y] != _2048[x][y-1] && _2048[x][y+1] != _2048[x][y]){
				return 0;
			}else if(_2048[x][y] != _2048[x-1][y] && _2048[x+1][y] != _2048[x][y]){
				return 0;
			}
		}
	}
	}
	
	return 1;
}

void GameOver(void)
{
	printf("\n\n");
	printf("\t\t\t\t-----Game Over-----\n\n");
	printf("\t\t\t\t Maker: vmpy (flee"); 
	return;
}

void Seed(void)
{
	int x,y;
	again:
	x = rand()%4;
	y = rand()%4;
	if(_2048[x][y] != 0){
		goto again;
	}
	_2048[x][y] = Random();
}

int Random(void)
{
	int a;
	int b;
	a = rand()%10;
	b = rand()%2;
	return a>b?2:4;
}
