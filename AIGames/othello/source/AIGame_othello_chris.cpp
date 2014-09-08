#include <stdio.h>
int board[8][8] = {0};/* 从坐标点(x,y),其中xoffest,yoffset分别为相对点(x,y)的偏移量*/
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

 int main()
{
	int i =0;
	int j =0;

	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
		scanf("%d",&board[i][j]);
		}
        if(legal(0,0)) printf("0 0\n");
        else if(legal(7,7)) printf("7 7\n");
        else if(legal(0,7)) printf("0 7\n");
        else if(legal(7,0)) printf("7 0\n");
        else{
            for(j=0;j<8;j++){
                for(i=0;i<8;i++){
                    if(legal(i,j)){
                        if((i==0)||(j==0)) printf("%d %d\n",i,j);
                        else if((i==7)||(j==7)) printf("%d %d\n",i,j);
                        else if(legal(i,j)){
                            if((i==1&&j==1)||(i==6&&j==1)||(i==1&&j==6)||(i==6&&j==6)) continue;
                            if((i==1&&j==0)||(i==0&&j==1)||(i==0&&j==6)||(i==6&&j==0)||(i==7&&j==6)||(i==6&&j==7)||(i==7&&j==1)||(i==1&&j==7)) continue;
                            else printf("%d %d\n",i,j);
                        }
                        if(i==EOF||j==EOF){
                            for(j=0;j<8;j++){
                                for(i=0;i<8;i++){
                                    if(legal(i,j)){
                                        printf("%d %d\n",i,j);
                                        }
                                    }
                                }
                            }
                        return 1;
                        }
                    }
            }
        }
}
