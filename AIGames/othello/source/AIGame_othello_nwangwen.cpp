//������һ��ʾ������ֻҪ��⵽���ʵĵ�������⣬��򵥵�AI
//**���µ���෽��ֵ�ø���**

#include <stdio.h>

int board[8][8] = {0};
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
	if (board[x][y]!=0)// �Ѿ�����
		return 0;
	int i, j, flag;
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

 int main()
{
	int i =0;
	int j =0;
	
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
				printf("%d %d\n",i,j);
				return 1;
			}
		}
}


