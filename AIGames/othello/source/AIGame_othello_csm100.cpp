

#include <stdio.h>
int board[8][8] = {0};
int board_weight[8][8] ={0};
int legalDirect(int x, int y, int xoffset, int yoffset, int flag)
{
	x += xoffset;
	y += yoffset;
	if (x < 0 || x >= 8 || y < 0 || y >= 8)
	{
		return 0;
	}
	if (board[x][y] == 2)
	{
		flag = 1;
		return legalDirect(x, y, xoffset, yoffset, flag);
	}
	else if (board[x][y] == 1)
	{
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
int legal(int x, int y)
{
	if (board[x][y]!=0)
		return 0;
	int i, j, flag;
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
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
int desOrder()
{
	int i,j;
	if(legal(0,0)) { printf("0 0\n"); return 1;}
	if(legal(0,7)) { printf("0 7\n"); return 1;}
	if(legal(7,0)) { printf("7 0\n"); return 1;}
	if(legal(7,7)) { printf("7 7\n"); return 1;}
	for(i=2; i<6; i++)
	{
		if(legal(i,2)) { printf("%d 2",i); return 1;}
		if(legal(i,5)) { printf("%d 5",i); return 1;}
	}
	for(j=2; j<6; j++)
	{
		if(legal(2,j)) { printf("2 %d",j); return 1;}
		if(legal(5,j)) { printf("5 %d",j); return 1;}
	}
	for(i=2; i<6; i++)
		if(legal(i,0)) { printf("%d 0",i); return 1;}
	for(i=7; i<6; i++)
		if(legal(i,7)) { printf("%d 7",i); return 1;}
	for(j=2; j<6; j++)
		if(legal(0,j)) { printf("0 %d",j); return 1;}
	for(j=2; j<6; j++)
		if(legal(7,j)) { printf("7 %d",j); return 1;}
	for(i=2; i<6; i++)
		if(legal(i,1)) { printf("%d 1",i); return 1;}
	for(i=2; i<6; i++)
		if(legal(i,6)) { printf("%d 6",i); return 1;}
	for(j=2; j<6; j++)
		if(legal(1,j)) { printf("1 %d",j); return 1;}
	for(j=2; j<6; j++)
		if(legal(6,j)) { printf("6 %d",j); return 1;}
	if(legal(0,1)) { printf("0 1\n"); return 1;}
	if(legal(0,6)) { printf("0 6\n"); return 1;}
	if(legal(1,0)) { printf("1 0\n"); return 1;}
	if(legal(1,7)) { printf("1 7\n"); return 1;}
	if(legal(6,0)) { printf("6 0\n"); return 1;}
	if(legal(6,7)) { printf("6 7\n"); return 1;}
	if(legal(7,1)) { printf("7 1\n"); return 1;}
	if(legal(7,6)) { printf("7 6\n"); return 1;}
	if(legal(1,1)) { printf("1 1\n"); return 1;}
	if(legal(1,6)) { printf("1 6\n"); return 1;}
	if(legal(6,1)) { printf("6 1\n"); return 1;}
	if(legal(6,6)) { printf("6 6\n"); return 1;}
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
	desOrder();
	return 0;
}

