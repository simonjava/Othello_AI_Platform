#include <stdio.h>

int board[8][8] = {0},map[8][8] = {0},map1[8][8] = {0},map2[8][8] = {0},val[8][8] = {0};
int quan[8][8] = {1200, -1000,1000,-1000,-1000,1000,-1000,1200,
                  -1000,-1000 ,0   ,0    ,0    ,0   ,-1000,-1000,
                  1000 ,0     ,1000,1000 ,1000 ,1000,0    ,1000,
                  -1000,0     ,1000,1000 ,1000 ,1000,0    ,-1000,
                  -1000,0     ,1000,1000 ,1000 ,1000,0    ,-1000,
                  1000 ,0     ,1000,1000 ,1000 ,1000,0    ,1000,
                  -1000,-1000 ,0   ,0    ,0    ,0   ,-1000,-1000,
                  1200 , -1000,1000,-1000,-1000,1000,-1000,1200};
/* 从坐标点(x,y),其中xoffest,yoffset分别为相对点(x,y)的偏移量*/
int legalDirect(int x, int y, int xoffest, int yoffset, int flag)
{
	x += xoffest;
	y += yoffset;
	if (x < 0 || x >= 8 || y < 0 || y >= 8)// 超出棋盘范围
	{
		return 0;
	}
	if (map[x][y] == 2)
	{
		/* (x,y)某个方向的有相邻的对手棋子,继续检查这个方向是否
		*  可以吃对方子,递归调用
		*/
		flag = 1;
		return legalDirect(x, y, xoffest, yoffset, flag);
	}
	else if (map[x][y] == 1)
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
int direct(int x, int y)
{
    int xx = x,yy = y,p,q,i,j;
    for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		  map1[i][j] = map[i][j];
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)// (x,y)点忽略
			{
				continue;
			}
			while(map[x+i][y+j] == 2)
			{
                x += i;
                y += j; 
            }
            x += i;
            y += j; 
            if (x < 0 || x >= 8 || y < 0 || y >= 8)// 超出棋盘范围
        	{
        		continue;
        	}
            if(map[x][y] == 1)
            {
                for(p = xx,q = yy;p < x;p = p+i,q = q+j)
                    map1[p][q] = 1;
            }
        }
    }
}
/* 检查是否可以落子,否返回 0,是返回 1*/
int legal(int x, int y)
{
	if (map[x][y]!=0)// 已经下子
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
//翻转棋盘 
int turn()
{
    int i,j;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
            if(map[i][j] == 1)
                map1[i][j] = 2;
            else if (map[i][j] == 2)
                map1[i][j] = 1;
            else
                map1[i][j] = 0;
        }
    return 0;
}
//可以下子数 
int count()
{
    int n = 0,i,j;
	for(j=0;j<8;j++)
		for(i=0;i<8;i++)
		{
            if(legal(i,j))
            n++;
        }
    return n;
}
int angle()
{
    if(legal(0,0) || legal(0,7) || legal(7,0) || legal(7,7))
        return 600;
    else if(legal(0,2) || legal(0,5) || legal(7,2) || legal(7,5) || legal(2,0) || legal(5,0) || legal(2,7) || legal(5,7))
        return 400; 
    else
        return 0;
}
int value()
{
    int i,j,p,q;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		  val[i][j] = quan[i][j];
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
            for(p=0;p<8;p++)
		        for(q=0;q<8;q++)
                    map[p][q] = board[p][q];
            if(legal(i,j))
            {
                direct(p,q);
                for(p=0;p<8;p++)
		          for(q=0;q<8;q++)
		              map[p][q] = map1[p][q];
                turn();
                for(p=0;p<8;p++)
		          for(q=0;q<8;q++)
		              map[p][q] = map1[p][q];
                val[i][j] += 280/(count()+1);
                val[i][j] -=angle();
            }
            else 
                val[i][j] = -100000;
        }
}
 int main()
{
	int i =0,j =0,max = -100000,maxx,maxy;	
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
		scanf("%d",&board[i][j]);
		}
		value();
	for(j=0;j<8;j++)
		for(i=0;i<8;i++)
		{
            if(max<val[i][j])
            {
                max = val[i][j];
                maxx = i;
                maxy = j;
            }
		}
	printf("%d %d\n",maxx,maxy);
    return 1;
}
