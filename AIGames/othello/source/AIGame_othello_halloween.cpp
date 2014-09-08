/*此版本增加了对完整程度的判断，修复了（1，2）这种bug，还算了cut后的grade的平均值*/
/*共233行，是最终版本，再也不改了*/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define BEGIN 10
#define MID1 38
#define MID2 55
#define LEN 10
int in (int i, int j) {return (i>=1&&i<=8)&&(j>=1&&j<=8); }
int board[LEN][LEN];
int tbd1[LEN][LEN]; //己方棋盘
int tbd2[LEN][LEN];//对手棋盘
int boom;

int istype2 (int i, int j) {return ((i==2&&j==2) || (i==7&&j==7) || (i==2&&j==7) ||(i==7&&j==2));}
int grade (int i, int j, int bd[][LEN]);//棋盘上的点评分的代码
int legalDirect(int x, int y, int bd[][LEN], int color, int xoffest, int yoffset, int flag);
int legal(int x, int y, int bd[][LEN], int color);
int point (int i, int j, int T);//黑棋下某步的分数，分数高的获胜
int afput(int i, int j, int bd[][LEN], int color, int *m, int *M, int *ave);//在棋盘上放上了color的棋子后的反应，返回吃子数
int countmap (int bd[][LEN]);

 int main()
{
	int i =0;
	int j =0;
	int t, Max, Mi, Mj, sum;
	Max=-10000;

//freopen("in.txt", "r", stdin);
    memset (board, 0, sizeof (board));
    memset (tbd1, 0, sizeof (tbd1));
    memset (tbd2, 0, sizeof (tbd2));
    sum=0;
	for(i=1;i<=8;i++)
		for(j=1;j<=8;j++)
		{
            scanf("%d",&board[i][j]);
            if (board[i][j]) sum++;
		}

	for(j=1;j<=8;j++)
		for(i=1;i<=8;i++)
		{
			if(legal(i,j, board, 1))
			{
			   // printf (":::%d %d\n", i-1, j-1);
				t=point (i, j, sum)+100;
				if (t>=Max)
                    {Max=t; Mi=i; Mj=j; }
			}
		}
    printf("%d %d\n", Mi-1, Mj-1);
    /*t2=clock();
    printf("%d\n", t2);*/
    return 0;
}

int legalDirect(int x, int y, int bd[][LEN], int color, int xoffest, int yoffset, int flag)
{
	x += xoffest;
	y += yoffset;
	if (x < 1 || x > 8 || y < 1 || y > 8)// 超出棋盘范围
	{
		return 0;
	}
	if (bd[x][y] == 3-color)
	{
		flag = 1;
		return legalDirect(x, y, bd, color, xoffest, yoffset, flag);
	}
	else if (board[x][y] == color)
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

int legal(int x, int y, int bd[][LEN], int color)
{
	if (bd[x][y]!=0)// 已经下子
		return 0;
	int i, j, flag;
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)// (x,y)点忽略
			{
				continue;
			}
			flag = 0;
			if (legalDirect(x, y, bd, color, i, j, flag))
			{
				return 1;
			}
		}
	}
	return 0;
}

int grade (int i, int j, int bd[][LEN]) //为棋盘上的点估计分数的代码
{
    int g=0;int ii, jj;int a[9]={0};
    a[2]=1; a[7]=8; a[1]=1; a[8]=8;
     {
        if ((a[i]==1&&a[j]==1&&(i!=1||j!=1)) || (a[i]==8&&a[j]==8&&(i!=8||j!=8)) || (a[i]==1&&a[j]==8&&(i!=1||j!=8)) || (a[i]==8&&a[j]==1&&(i!=8||j!=1) ) ){
            if (bd[ a[i] ][ a[j] ]==0)
                g-=150;
        }

        else if (i==8||i==1) {
            if (3<=j&&j<=6)  g+=30;
            if (j==3 || j==6) g+=40;
        }
        else if (j==1||j==8) {
            if (3<=i&&i<=6)  g+=30;
            if (i==3 || i==6) g+=40;
        }
        else if (3<=i&&i<=6 && 3<=j&&j<=6) {
            g+=30;
        }
        else g+=10;
	if ((i==8&&j==8) || (i==1&&j==8) || (i==1&&j==1) || (i==8&&j==1)) {
            g+=500;
        }
        for (ii=-1; ii<=1; ii++) {
            for(jj=-1; jj<=1; jj++) {
                if (ii==0&&jj==0) continue;
                else {
                    if (1<=i+ii&&i+ii<=8 && 1<=j+jj&&j+jj<=8)
                    if (bd[i+ii][j+jj] !=0)
                    g+=2;
                }
            }
        }
    }
    return g;
}
int point (int i,int j, int T)
{
    int ii, jj, c1, c2, c2max=-1, g1, g2, g2max, m, M, ave;
    int flag=0, f=0;
        boom = 0;
        g1 = grade(i, j, board);//给board上的（i,j）打分
        memcpy (tbd1, board, LEN*LEN*sizeof(int));//拷贝到tbd1中
        c1=afput (i, j, tbd1, 1, &m, &M, &ave);//在tbd1的(i, j)点放己方棋子
        g1+=countmap(tbd1);
        g1 += ((3*m+0.3*M)+ave)/2;
        for(ii=1;ii<=8;ii++) {
            for(jj=1;jj<=8;jj++)
            {
                if(legal(ii,jj, tbd1, 2))//考虑对方能够走的情况
                {
                    f=1;
                    g2=grade(ii, jj, tbd1);
                    if (g2>g2max) g2max=g2;
                    memcpy(tbd2, tbd1, LEN*LEN*sizeof(int));//再次拷贝棋盘
                    c2 = afput (ii, jj, tbd2, 2, &m, &M, &ave);//在新棋盘上放对手的棋子
                    g2max +=(M*0.3+ave)/2;
                    if (tbd2[i][j]!=1) flag=1;//下下去之后又被吃掉，则flag=true，之后扣分
                    if (c2max<c2) c2max=c2;
                }
            }
        }
    c1*=8; c2max*=8;
    if (f==0)//对手不能落子了
        return 10000;
    if (T<BEGIN) {
        return 2*(g1-0.4*g2max) + 2*(c1-0.3*c2max) -(flag==1?10:0) - (boom==1?150:0);
    }
    else if (T >= BEGIN && T<MID1) {
        return  3*(g1-0.4*g2max) + (c1-0.3*c2max)-(flag==1?10:0) - (boom==1?150:0);
    }
    else if (T>=MID1 && T<MID2) {
        return  (g1-0.3*g2max) + 3*(c1-0.3*c2max)-(flag==1?10:0) - (boom==1?150:0);
    }
    else
        return (g1-0.45*g2max)+4*(c1-0.45*c2max)-(flag==1?10:0) - (boom==1?150:0);
}

int afput(int i, int j, int bd[][LEN], int color, int *m, int *M, int *ave)//在棋盘上放上了color的棋子后的反应，返回吃子数
{
    int dx, dy, cut, ti, tj, t;
    int a[9]={0};
    a[2]=1; a[7]=8; a[1]=1; a[8]=8;
    cut=0;*ave=0;
    *M=-10000; *m=10000;
    for (dx=-1; dx<=1; dx++) {
        for (dy=-1; dy<=1; dy++) {
            if (dx==0&&dy==0) continue;
            else {
                if (legalDirect(i, j, bd, color, dx, dy, 0)) {
                    ti=i; tj=j;
                    while (bd[ti+dx][tj+dy] == 3-color) {//是color另一边的棋子，则吃掉
                        ti+=dx; tj+=dy;
                        if (color == 1 && istype2(ti, tj) && bd[ a[ti] ][ a[tj] ]==0) {
                            boom = 1;
                        }
                        bd[ti][tj] = color;
                        if ((t=grade(ti, tj, bd) ) > *M) *M=t;
                        if (t<*m) *m=t;
                        *ave+=t;
                        cut++;
                    }
                }
            }
        }
    }
    *ave = *ave/cut;
    return cut;
}

int countmap (int bd[][LEN])
{
    int i, j, sum;
    for (i=1; i<=8; i++) {
        for (j=1; j<=8; j++) {
           if (in(i+1, j+1)) {
                if(bd[i+1][j+1]==1)
                    sum++;
           }
           if (in(i-1, j-1)) {
                if(bd[i-1][j-1]==1)
                    sum++;
           }
           if (in(i-1, j+1)) {
                if(bd[i-1][j+1]==1)
                    sum++;
           }
           if (in(i+1, j-1)) {
                if(bd[i+1][j-1]==1)
                    sum++;
           }
        }
    }
    if (i==1||i==8) sum+=5;
    if (j==1||j==8) sum+=5;
    return sum;
}

