#include <stdio.h>
int binx , biny ;
int recordx ,recordy ;
int ans , step = 0 ;
int board[8][8] = {0};
int legalDirect(int x, int y, int xoffest, int yoffset, int flag)
{
	x += xoffest;
	y += yoffset;
	if (x < 0 || x >= 8 || y < 0 || y >= 8)
	{
		return 0;
	}
	if (board[x][y] == 2)
	{
		flag = 1;
		return legalDirect(x, y, xoffest, yoffset, flag);
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

 int main()
{
	int i =0;
	int j =0;
	binx = 0 ;
	biny = 0 ;
	ans = 0 ;
	for(i=0;i<8;i++)
    {
		for(j=0;j<8;j++)
		{
		scanf("%d",&board[i][j]);
		}
    }
    if(legal(0,0)){printf("0 0\n");return 1 ;}
    else if(legal(0,7)){printf("0 7\n");return 1 ;}
    else if(legal(7,0)){printf("7 0\n");return 1 ;}
    else if(legal(7,7)){printf("7 7\n");return 1 ;}
	for(j=0;j<8;j++)
		for(i=0;i<8;i++)
		{
			if(legal(i,j))
			{
			    step =  0 ;
			    for( binx = i + 1 ; board[binx][j] == 2 && binx <= 7 ; binx++) { if(board[binx+1][j]==1) step += binx - i ;}
			    for( binx = i - 1 ; board[binx][j] == 2 && binx >= 0 ; binx--) {if(board[binx-1][j]==1) step += i - binx ;}
			    for( biny = j - 1 ; board[i][biny] == 2 && biny >= 0 ; biny--) {if(board[i][biny-1]==1) step += j - biny ;}
			    for( biny = j + 1 ; board[i][biny] == 2 && biny <= 7 ; biny++ ) {if(board[i][biny+1]==1) step += biny - j;}
			    for( binx = i + 1 , biny = j + 1 ; board[binx][biny] ==2 && binx <= 7 && biny <= 7; binx++ ,biny++ ) {if(board[binx+1][biny+1]==1) step += binx - i ;}
			    for( binx = i + 1 , biny = j - 1 ; board[binx][biny] ==2 && binx <= 7 && biny >= 0; binx++ ,biny-- ) {if(board[binx+1][biny-1]==1) step += binx - i ;}
			    for( binx = i - 1 , biny = j + 1 ; board[binx][biny] ==2 && binx >= 0 && biny <= 7; binx-- ,biny++ ) {if(board[binx-1][biny+1]==1) step += biny - j ;}
			    for( binx = i - 1 , biny = j - 1 ; board[binx][biny] ==2 && binx >=0 && biny >= 0; binx-- ,biny-- ) {if(board[binx-1][biny-1]==1) step += i - binx ;}
			    if( ans < step )
                {
                    ans = step ;
                    recordx = i ;
                    recordy = j ;
                }
                if( ans == step )
                {
                    if( i==0 || j==0 || j==7 || i==7)
                    {
                        ans = step ;
                        recordx = i ;
                        recordy = j ;
                    }

                }

			}
		}

    printf("%d %d\n",recordx,recordy);
    return 1;
}



