#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define LEN 10
int myb [LEN][LEN]={0};
int tb [LEN][LEN] ={0};//用于判断是否下子后能单独成行列，即privat
int youb[LEN][LEN]={0};
int judge_spe1 (int i,int j);//是否为一号位,在restore_p中用到
int judge_spe2 (int i,int j);//是否为二号位,在restore_p中用到
int restore_p (int i,int j);
int legal (int i,int j,int b[][LEN]);//顺便返回吃子数
int pro_point (int i,int j,int b[][LEN],int num,int y_sum);//产生分数,加权所得
int in (int i,int j){return (i>=1&&i<=8)&&(j>=1&&j<=8);}
int side1 (int i,int j,int b[][LEN]);
int side2 (int i,int j,int b[][LEN]);//边的判断，必须根据占边后别人的情况给分！。（若有反转，翻转后）无相邻敌方棋子
//（或者有相邻但是是诱惑对方下一号位）给100，其中能下在别人边线两子之间的（200）要给予很高优先级。
int privat (int i,int j,int b[][LEN]);//能使边路单独成行列并且字数达到4个以上给100.
int isside (int i,int j){return (i==1)||(i==8)||(j==1)||(j==8);}//判断是否为边
int cornor(int i,int j);
int iscornor(int i,int j){return ((i==1)||(i==8))&&((j==1)||(j==8));}
int cornor(int i,int j)
{
	if(i<=2)
	{
		if(j<=2)return myb[1][1];
		else if(j>=7)return myb[1][8];
	}
	else if(i>=7)
	{
		if(j<=2)return myb[8][1];
		else if(j>=7)return myb[8][8];
	}
}
int side1 (int i,int j,int b[][LEN])
{
	if(b[i][j-1]==2&&b[i][j+1]==2)return 200;
	else if((b[i][j-1]==2&&b[i][j+1]==0)||(b[i][j+1]==2&&b[i][j-1]==0))return -150;
	else
		return 0;
}
int side2 (int i,int j,int b[][LEN])
{
	if(b[i-1][j]==2&&b[i+1][j]==2)return 100;
	else if((b[i-1][j]==2&&b[i+1][j]==0)||(b[i+1][j]==2&&b[i-1][j]==0))return -150;
	else
		return 0;
}
int privat (int i,int j,int b[][LEN],int ti,int tj,int side)
{
	int ti1=i+ti,tj1=j+tj,state=0,count=1;
	while(in(ti1,tj1))
	{
		if(b[ti1][tj1]==1)count++;
		if(b[ti1][tj1]==2)state++;
		ti1+=ti;
	    tj1+=tj;
	}
	if((state==0)&&(count>=(side==1? 3:5)))return 1;
	ti1=i-ti,tj1=j-tj;count=1;state=0;
    while((in(ti1,tj1)))
	{
		if(b[ti1][tj1]==1)count++;
		if(b[ti1][tj1]==2)state++;
		ti1-=ti;
	    tj1-=tj;
	}
	if((state==0)&&(count>=(side==1? 3:5)))return 1;
/*	for(ii=1;ii<=8;ii++)
	{
		if(b[ii][j]==1&&b[ii-1][j]==1)count_c++;
		if(b[ii][j]==2)state_c=1;
		if(b[i][ii]==1&&b[i][ii-1]==1)count_r++;
		if(b[i][ii]==2)state_r=1;
	}
*/
	return 0;
}
int judge_spe2 (int i,int j)
{
	if(((i==3)||(i==6))&&((j==1)||(j==2)||(j==3)||(j==6)||(j==7)||(j==8)))return 1;
	else if(((i==1)||(i==2)||(i==7)||(i==8))&&((j==3)||(j==6)))return 1;
	else 
		return 0;
}

int judge_spe1 (int i,int j)
{
	if((i==1||i==8)&&(j==2)||(j==7))return 1;
	else if(((i==2)||(i==7))&&((j==1)||(j==2)||(j==7)||(j==8)))return 1;
	else
		return 0;
}

int restore_p (int i,int j)//一号位扣1000，二号位奖励50.
{
	if(iscornor(i,j))return 2000;
	else if(judge_spe1(i,j)&&cornor(i,j)!=1)return -1000;
	else if(judge_spe2(i,j)&&cornor(i,j)!=1)return 50;
	else
		return 0;
}
int main()
{
	int i =0,j =0;
//	int t1, t2;
	int t, Max, Mi, Mj, sum,num,y_sum;//y_sum用于计算吃子所占对方总子数比例
	Max = -10000;

 //freopen("in.txt", "r", stdin);
//t1=clock();
    sum=0;y_sum=0;
	for(i=1;i<=8;i++)
		for(j=1;j<=8;j++)
		{
            scanf("%d",&myb[i][j]);
			tb[i][j]=myb[i][j];
            if (myb[i][j]) sum++;
			if (myb[i][j]==2)y_sum++;
		}

	for(j=1;j<=8;j++)
		for(i=1;i<=8;i++)
		{
			if(num=legal(i,j, myb))
			{
			   // printf (":::%d %d\n", i-1, j-1);
				if(sum<=58&&sum>=10)
				    t = pro_point(i,j,myb,num,y_sum);
				else if(sum>58||sum<10)
				{
					t = 10*num;
					if(judge_spe1(i,j))t-=1000;
					if(iscornor(i,j))t+=1000;
				}
//				if(i==2&&j==7)printf("*%d\n",t);
				if (t>=Max)
				{Max=t; Mi=i; Mj=j; }
			}
		}
    printf("%d %d\n", Mi-1, Mj-1);
//	printf("%d\n",Max);
    /*t2=clock();
    printf("%d\n", t2);*/
    return 0;
}

int legal (int i,int j,int b[][LEN])
{
	if(b[i][j])return 0;
	int ii,jj;
	int t_r,t_c;
	int count,state;
	int sum=0;
	tb[i][j]=1;
	for(ii=1;ii<=8;ii++)//还原tb值
		for(jj=1;jj<=8;jj++)
			tb[ii][jj]=b[ii][jj];
	for(ii =-1;ii <=1;ii ++)
		for(jj =-1;jj <=1;jj ++)
		{
			count =0;
			state =0;
			if(ii==0&&jj==0)continue;
			else{				
				for(t_r =i+ii,t_c = j+jj;in(t_r,t_c);t_r =t_r+ii,t_c = t_c+jj)
				{
					if(b[t_r][t_c]==2){state=1;tb[t_r][t_c]=1;count++;}
					else if(b[t_r][t_c]==0)break;
					else if(b[t_r][t_c]==1)
					{
						if(state==1)
							sum+=count;
						break;
					}
				}
			}
		}
    return sum;
}

int nonchance(int t,int b[][LEN],int tb [][LEN])
{
	int ii,jj,state=0;
	if(t==-1)
	{
		for(ii=1,jj=1;in(ii,jj);ii++,jj++)
			if(tb[ii][jj]==1)state++;
	}
	else if(t==1)
	{
		for(ii=1,jj=8;in(ii,jj);ii++,jj--)
			if(tb[ii][jj]==1)state++;
	}
	if(state==0)return 1;
	else return 0;
}
int ispriv_midd(int tb1[][LEN])
{
	int ii=0,jj=0,state=0,count=0,sign,t;
    while(in(++ii,++jj))
	{
        if(tb1[ii][jj]==2)state++;
		if(tb1[ii-1][jj-1]==0&&tb1[ii][jj]==1)
		{
			sign=1;
			count=1;
		}
		if(tb1[ii][jj]==0)
		{
			sign=0;
			if(count>=5)
				t++;
		}
		if(sign=1&&tb1[ii][jj]==1)count++;
	}
	if(t&&state==0)return 1;

	ii=9,jj=0,state=0,count=0,sign,t;
    while(in(--ii,++jj))
	{
        if(tb1[ii][jj]==2)state++;
		if(tb1[ii+1][jj-1]==0&&tb1[ii][jj]==1)
		{
			sign=1;
			count=1;
		}
		if(tb1[ii][jj]==0)
		{
			sign=0;
			if(count>=5)
				t++;
		}
		if(sign=1&&tb1[ii][jj]==1)count++;
	}
	if(t&&state==0)return -1;
	return 0;
}
int pro_point (int i,int j,int b[][LEN],int num_me,int y_sum)
{
	int ii,jj,num_him;
	double proportion=num_me/y_sum;
	int point =0;
	point += restore_p(i,j);//相当于一个数据库，储存了每个位置的分数
	point += int(200 * proportion);
	if(i==1||i==8) point += 100+ side1 (i,j,tb);//边判断
	else if(j==1||j==8)point += 100+ side2 (i,j,tb);//边判断
	if((privat(i,j,tb,1,0,1)||privat(i,j,tb,0,1,1))&&isside(i,j)) point += 400;//此处之前tb仍为改过后的myb数组，仍可以使用。//此处isside的使用不符合本意，本意是使边路成行列。
	//以下是模拟进行这步棋(用还未还原的tb数组来赋值youb[i][j])，但是仅考虑对面吃子(若亏了，扣50)，或者占边（），来扣除一定分数。
	for(ii=1;ii<=8;ii++)
		for(jj=1;jj<=8;jj++)
		{
			if(tb[ii][jj])youb[ii][jj] = 3 - tb[ii][jj];
			else
				youb[ii][jj]=0;
		}
	int t1=0,t2=0,t3=0,max=0,t4=0,angle;

	if(angle=ispriv_midd(tb))point += 400;//趁tb仍未改变

	for(ii=1;ii<=8;ii++)
		for(jj=1;jj<=8;jj++)
		{
			if(num_him=legal(ii,jj, youb))
			{//此处legal改变了tb成对方做完这次改动后的数组
			if(num_him>max)
			{
				max=num_him;
			}
			max=num_him;
			if(ii==1||ii==8)
			    t1+=privat(ii,jj,tb,0,1,1);//对面占边且单独成行
			else if(jj==1||jj==8)
				t1+=privat(ii,jj,tb,1,0,1);
			t2 +=isside(ii,jj);//对面占边
			t3 += (ii==1||ii==8)&&(jj==1||jj==8);//对面占角
			t4 +=(angle)&&nonchance(angle,youb,tb);//nonchance用来看能不能吃我在中路成线的棋子，如果成线超过5个，而且敌方不能吃子，加250
			}
		}
	if(max>num_me)point -= 50;
	if(t1)point -= 400;
	if(t2)point -= 50;
    if(t3)point -= 1000;
	if(t4)point += 1200;
	return point;
}