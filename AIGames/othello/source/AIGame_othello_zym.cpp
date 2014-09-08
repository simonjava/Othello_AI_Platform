//如下是一个示例程序，只要检测到合适的点就下在这，最简单的AI
//**以下的许多方法值得复用**

#include <stdio.h>

int board[8][8] = {0};
int grade[8][8]={{100,-100,50,0,0,50,-100,100},
                     {-100,-100,10,20,20,10,-100,-100},
                     {50,10,30,30,30,30,10,50},
                     {0,20,30,30,30,30,20,0},
                     {0,20,30,30,30,30,20,0},
                     {50,10,30,30,30,30,10,50},
                     {-100,-100,10,30,30,10,-100,-100},
                     {100,-100,50,0,0,50,-100,100}
                     };
/* 从坐标点(x,y),其中xoffest,yoffset分别为相对点(x,y)的偏移量*/
int legalDirect(int x, int y, int xoffest, int yoffset, int flag)
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
		return legalDirect(x, y, xoffest, yoffset, flag);
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

/* 检查是否可以落子,否返回 0,是返回 1*/
int legal(int x, int y)
{
	if (board[x][y]!=0)// 已经下子
		return 0;
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
			if (legalDirect(x, y, i, j, flag))
			{
				return 1;
			}
		}
	}
	return 0;
}

int legalDirect2(int x, int y, int xoffest, int yoffset, int flag)
{
	x += xoffest;
	y += yoffset;
	if (x < 0 || x >= 8 || y < 0 || y >= 8)// 超出棋盘范围
	{
		return 0;
	}
	if (board[x][y] == 1)
	{
		/* (x,y)某个方向的有相邻的自己棋子,继续检查这个方向是否
		*  可以吃自己子,递归调用
		*/
		flag = 1;
		return legalDirect(x, y, xoffest, yoffset, flag);
	}
	else if (board[x][y] == 2)
	{
		/* 遇到敌方的棋子,判断这个方向之前的棋子是否全为己方的即 legal=1*/
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

/* 检查是否可以落子,否返回 0,是返回 1*/
int legal2(int x, int y)
{
	if (board[x][y]!=0)// 已经下子
		return 0;
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
			if (legalDirect(x, y, i, j, flag))
			{
				return 1;
			}
		}
	}
	return 0;
}
 int min1(int i,int j){
   int a;
   board[i][j]=1;
   a=-200;
   int i0,j0;
   	for(j0=0;j0<8;j0++)
		for(i0=0;i0<8;i0++)
		{
			if(legal2(i0,j0))
			{
                 if(a<grade[i0][j0]) a=grade[i0][j0];
			}
		}
	board[i][j]=0;
	return a;
}
 int main()
{
    int i =0;
	int j =0;
	
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
		scanf("%d",&board[i][j]);
		}
	int max,min;
	max=-200;
	min=200;
    int k,l,min0; 
	for(j=0;j<8;j++)
		for(i=0;i<8;i++)
		{
			if(legal(i,j))
			{
                 if(grade[i][j]==100) goto OUT;
                 min0=min1(i,j);
                 if(min0==100&&max!=-200) continue;
                 if(grade[i][j]>max){k=i;l=j;min=min0;}
                 else if(grade[i][j]==max){
                      if(min0<min){k=i;l=j;min=min0;}
                 }
			}
		}
OUT:printf("%d %d\n",k,l);
	return 1;
}
