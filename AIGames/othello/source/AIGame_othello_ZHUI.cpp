#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define FALSE -10000
struct point{
	int x;
	int y;
	int eat;
	int win;
	};
struct point suit[60];
struct point suitTemp[60];
int  point_value[8][8]={500, -50, 30, 10, 10, 30, -50, 500, -50, -250, 0, 0, 0, 0, -250, -50, 30, 0, 1, 2, 2, 1, 0, 30, 10, 0, 2, 16, 16, 2, 0, 10, 10, 0, 2, 16, 16, 2, 0, 10, 30, 0, 1, 2, 2, 1, 0, 30, -50, -250, 0, 0, 0, 0, -250, -50, 500, -50, 30, 10, 10, 30, -50, 500};
/* 从坐标点(x,y),其中xoffest,yoffset分别为相对点(x,y)的偏移量*/
int legalDirect(int x, int y, int xoffest, int yoffset, int flag, int count,int board[][8])
{
	x += xoffest;
	y += yoffset;
	if (x < 0 || x >= 8 || y < 0 || y >= 8)// 超出棋盘范围
	{
		return FALSE;
	}
	if (board[x][y] == 2)
	{
		/* (x,y)某个方向的有相邻的对手棋子,继续检查这个方向是否
		*  可以吃对方子,递归调用
		*/
		flag = 1;
		return legalDirect(x, y, xoffest, yoffset, flag,count+point_value[x][y],board);
	}
	else if (board[x][y] == 1)
	{
		/* 遇到自己的棋子,判断这个方向之前的棋子是否全为反方的即 legal=1*/
		if (flag == 1)
		{
			return count;
		}
		return FALSE;
	}
	else
		return FALSE;

	return FALSE;
}

int turnDirect(int x, int y, int xoffest, int yoffset, int flag,int board[][8])
{
	x += xoffest;
	y += yoffset;
	if (x < 0 || x >= 8 || y < 0 || y >= 8)// 超出棋盘范围
	{
		return 0;
	}
	if (board[x][y] == 2)
	{
		/* (x,y)某个方向的有相邻的对手棋子,继续检查这个方向是否
		*  可以吃对方子,递归调用
		*/
		flag = 1;
		if(turnDirect(x, y, xoffest, yoffset, flag,board))
		{
			board[x][y]=1;
			return 1;
		}
		else return 0;
	}
	else if (board[x][y] == 1)
	{
		/* 遇到自己的棋子,判断这个方向之前的棋子是否全为反方的即 legal=1*/
		if (flag == 1)
		{
			return 1;
		}
		return 0;
	}
	else
		return 0;

	return 0;
}

int turn(int x,int y,int board[][8])
{
	int i, j, flag;
	/* 检测(x,y)坐标点八个方向*/
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)// (x,y)点忽略
			{
				continue;
			}
			flag = 0;
			turnDirect(x, y, i, j, flag,board);
		}
	}
}


/* 检查是否可以落子,否返回 0,是返回 可以吃掉的子的数目*/
int legal(int x, int y, int board[][8])
{
	
	int C=0;
	if (board[x][y]!=0)// 已经下子
		return FALSE;
	int i, j, flag,count;
	int eat=1;
	count=point_value[x][y];
	/* 检测(x,y)坐标点八个方向*/
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)// (x,y)点忽略
			{
				continue;
			}
			flag = 0;
			int temp=legalDirect(x, y, i, j, flag, count,board);
			if(temp!=FALSE)
			{
				eat+=temp;
				C=1;
				}
		}
	}
	if(C)
		return eat;
	return FALSE;
}

int eatmost(int board[][8])
{
	int i,j;
	int k=0;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
			int eat;
			if(eat=legal(i,j,board))
			{
				suitTemp[k].x=i;
				suitTemp[k].y=j;
				suitTemp[k].eat=eat;
				k++;
			}
		}
	int N;
	int MAX;
	int temp=0;
	N=k;
	MAX=0;
	for(k=0; k< N; k++)
		if(suitTemp[k].eat>MAX) 
		{
			temp=k;
			MAX=suitTemp[k].eat;
		}
	//printf("\nYour opponet will play %d %d\n",suitTemp[temp].x,suitTemp[temp].y);
	return MAX;
}	
int shift (int board[][8])
{
	for(int j=0;j<8;j++)
		for(int i=0;i<8;i++)
		{
			if(board[i][j]==1) 
				board[i][j]=2;
			else if(board[i][j]==2) 
					board[i][j]=1;
		}
}
int show(int board[][8])
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
			printf("%d  ",board[i][j]);
		printf("\n");
	}
}
int value(int x,int y,int board[][8],int k)
{
	int board2[8][8]={0};
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			board2[i][j]=board[i][j];
	
	board2[x][y]=1;
	suit[k].win=0;			
	turn(x,y,board2);
	shift(board2);
	suit[k].win+=suit[k].eat-eatmost(board2);
	//shift(board2);
	//show(board2);
	//printf("The Point %d %d,eat %d;win %d\n\n\n",x,y,suit[k].eat,suit[k].win);
	return 1;

}

 int main()
{
	srand((int)time(0));
	int i =0;
	int j =0;
	int board[8][8] = {0};
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
		scanf("%d",&board[i][j]);
		}
	//shift(board);
	int k=0;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
			int eat;
			eat=legal(i,j,board);
			if(eat!= FALSE)
			{	
				suit[k].x=i;
				suit[k].y=j;
				suit[k].eat=eat;
				k++;
			}
		}
	int N;
	int MAX,temp;
	N=k;
	temp=-5000;
	for(k=0; k< N; k++)
	{
		int p;
		value(suit[k].x,suit[k].y,board,k);
		
		if(suit[k].win>temp) 
			{MAX=k;temp=suit[k].win;}
		else if(suit[k].win == temp && rand()%2)
				{MAX=k;temp=suit[k].win;}
	}
	printf("%d %d\n",suit[MAX].x,suit[MAX].y);
	return 1;
}
