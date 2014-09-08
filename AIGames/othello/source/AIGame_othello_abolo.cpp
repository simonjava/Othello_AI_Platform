#include <stdio.h>
#include <stdlib.h>

int board[8][8] = {0},map[8][8];
int mapvalue[8][8]={
{10000,-30,40,40,40,40,-30,10000},
{-30,-30,10,10,10,10,-30,-40},
{40,10,30,10,10,30,10,40},
{40,10,10,30,30,10,10,40},
{40,10,10,30,30,10,10,40},
{40,10,30,10,10,30,10,40},
{-30,-30,10,10,10,10,-30,-30},
{10000,-30,40,40,40,-30,10000}};
int turnnumber;
/* ´Ó×ø±êµã(x,y),ÆäÖÐxoffest,yoffset·Ö±ðÎªÏà¶Ôµã(x,y)µÄÆ«ÒÆÁ¿*/
int legalDirect(int x, int y, int xoffest, int yoffset, int flag)
{
	x += xoffest;
	y += yoffset;
	if (x < 0 || x >= 8 || y < 0 || y >= 8)// ³¬³öÆåÅÌ·¶Î§
	{
		return 0;
	}
	if (board[x][y] == 2)
	{
		/* (x,y)Ä³¸ö·½ÏòµÄÓÐÏàÁÚµÄ¶ÔÊÖÆå×Ó,¼ÌÐø¼ì²éÕâ¸ö·½ÏòÊÇ·ñ
		*  ¿ÉÒÔ³Ô¶Ô·½×Ó,µÝ¹éµ÷ÓÃ
		*/
		flag = 1;
		return legalDirect(x, y, xoffest, yoffset, flag);
	}
	else if (board[x][y] == 1)
	{
		/* Óöµ½×Ô¼ºµÄÆå×Ó,ÅÐ¶ÏÕâ¸ö·½ÏòÖ®Ç°µÄÆå×ÓÊÇ·ñÈ«Îª·´·½µÄ¼´ legal=1*/
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

/* ¼ì²éÊÇ·ñ¿ÉÒÔÂä×Ó,·ñ·µ»Ø 0,ÊÇ·µ»Ø 1*/
int legal(int x, int y)
{
	if (board[x][y]!=0)// ÒÑ¾­ÏÂ×Ó
		return 0;
	int i, j, flag;
	/* ¼ì²â(x,y)×ø±êµã°Ë¸ö·½Ïò*/
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)// (x,y)µãºöÂÔ
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
}int changemap(int x,int y)
{
	int i,j,k,xx,yy,p,q;
	turnnumber=0;
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			if (i != 0 || j != 0)
			for (k=1;k<8;k++)
			{
				xx=k*i+x;
				yy=k*j+y;
				if (xx < 0 || xx >= 8 || yy < 0 || yy >= 8 || board[xx][yy]==0)// ³¬³öÆåÅÌ·¶Î§
				{
					break;
				}
				if (board[xx][yy]==1)
				{
					for (p=0;p<k;p++)
					{
						board[x+p*i][y+p*j]=1;
						turnnumber+=mapvalue[x+p*i][y+p*j];
					}
					break;
				}
			}
		}
	}
	 	board[x][y]=1;
		return turnnumber;
}

int max(int a,int b)
{
	if (a>b) return a;
	return b;
}

int main()
{
	int i,j,p,q,value,k,ans=-1000000,ansx,ansy,flag;
	int tmap[8][8];
	int a[4]={0,0,7,7};
	int b[4]={7,0,0,7};
	for(i=0;i<8;i++)
	for(j=0;j<8;j++)
	{
		scanf("%d",&map[i][j]);
		board[i][j]=map[i][j];
	}
	for (i=0;i<8;i++)
	for (j=0;j<8;j++)
	if (legal(i,j))
	{
		changemap(i,j);
		value=0;
		/*for (p=0;p<8;p++)
		for (q=0;q<8;q++)
		{
			if (board[p][q]==1)
			value+=mapvalue[p][q];
			if (board[p][q]==2)
			value-=mapvalue[p][q];
		}*/
		value=turnnumber;
		for (p=0;p<8;p++)
		{
			flag=0;
			for (q=0;q<8;q++)
			if (board[p][q]!=1)
			flag=1;
			if (!flag) value+=50;
		}
		for (q=0;q<8;q++)
		{
			flag=0;
			for (p=0;p<8;p++)
			if (board[p][q]!=1)
			flag=1;
			if (!flag) value+=50;
		}
		for (k=0;k<4;k++)
		if (legal(a[k],b[k]))	value*=2;
		for(p=0;p<8;p++)
			for(q=0;q<8;q++) 
			{
				if (board[p][q]==1) board[p][q]=2;
				else if (board[p][q]==2) board[p][q]=1;
			}
		for (k=0;k<4;k++)
		if (legal(a[k],b[k]))	value /=4;
		if (ans<value)
		{	
			ansx=i;
			ansy=j;
			ans=value;
		}
		for(p=0;p<8;p++) for(q=0;q<8;q++) board[p][q]=map[p][q];
	}
	printf("%d %d\n",ansx,ansy);
	return 1;
}

/*int main()
{
	int i , j , p , q , nvalue , tvalue , ansx , ansy;
	freopen("1.txt","r",stdin);
	nvalue = 10000000;
    for(i=0;i<8;i++)
	for(j=0;j<8;j++)
	{
		scanf("%d",&map[i][j]);
	}
	for (i=0;i<8;i++)
	for (j=0;j<8;j++)
	{
    	for(p=0;p<8;p++)
		for(q=0;q<8;q++) 
		{
		   board[p][q] = map[p][q];
		}
	  if (legal(i , j))
	  {
	  	changemap(i , j);
	  	for(p=0;p<8;p++)
		for(q=0;q<8;q++) 
		{
			if (board[p][q]==1) board[p][q]=2;
			else if (board[p][q]==2) board[p][q]=1;
		}
		tvalue = basic();
		if (tvalue < nvalue)
		{
			ansx=i; ansy=j; nvalue=tvalue;
		}
	  }
	}
    printf("%d %d\n" , ansx , ansy);
    return 1;
}*/