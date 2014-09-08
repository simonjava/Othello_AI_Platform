//������һ��ʾ������ֻҪ��⵽���ʵĵ�������⣬��򵥵�AI
//**���µ���෽��ֵ�ø���**

#include <stdio.h>

int board[8][8] = {0};
int tail=0,ans[100][2];
/* �������(x,y),����xoffest,yoffset�ֱ�Ϊ��Ե�(x,y)��ƫ����*/
int legalDirect(int x, int y, int xoffest, int yoffset, int flag)
{
	x += xoffest;
	y += yoffset;
	if (x < 0 || x >= 8 || y < 0 || y >= 8)// �������̷�Χ
	{
		return 0;
	}
	if (board[x][y] == 2)
	{
		/* (x,y)ĳ������������ڵĶ�������,���������������Ƿ�
		*  ���ԳԶԷ���,�ݹ����
		*/
		flag = 1;
		return legalDirect(x, y, xoffest, yoffset, flag);
	}
	else if (board[x][y] == 1)
	{
		/* �����Լ�������,�ж��������֮ǰ�������Ƿ�ȫΪ�����ļ� legal=1*/
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

/* ����Ƿ��������,�񷵻� 0,�Ƿ��� 1*/
int legal(int x, int y)
{
	int i, j, flag;
	if (board[x][y]!=0)// �Ѿ�����
		return 0;
	/* ���(x,y)�����˸�����*/
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)// (x,y)�����
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

int value(int q)
{
	int x=ans[q][0],y=ans[q][1];
	if ((x==0)&&(y==0)||(x==0)&&(y==7)||(x==7)&&(y==0)||(x==7)&&(y==7)) return 999;
	else return 0;
	
}

void sp(int l,int r)

{
	int q,p,m,temp[2];
	q=l;p=r;m=value((l+r)/2);
	do{
		while (value(q)<m) q++;
		while (value(p)>m) p--;
		if (q<=p) {
			temp[0]=ans[q][0];
			ans[q][0]=ans[p][0];
			ans[p][0]=temp[0];
			temp[1]=ans[q][1];
			ans[q][1]=ans[p][1];
			ans[p][1]=temp[1];
			q++;p--;
		}
	}while (q<=p);
	if (l<p) sp(l,p);
	if (q<r) sp(q,r);
}

 int main()
{
	int ans[100][2]={0},i=0,j =0;
	
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
		scanf("%d",&board[i][j]);
		}
	
	for(j=0;j<8;j++)
		for(i=0;i<8;i++)
		{
			if(legal(i,j))
			{
				tail++;
				ans[tail][0]=i;
				ans[tail][1]=j;
			}
		}
	if (tail>1) sp(1,tail);
	printf("%d %d\n",ans[tail][0],ans[tail][1]);
	return 0;
}
