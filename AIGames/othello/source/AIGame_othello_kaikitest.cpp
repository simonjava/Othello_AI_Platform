#include <iostream>

using namespace std;

//所有的函数都调用board的像board2； 
int board[8][8] = {{0}} , board2[8][8] = {{0}};                     //board2为board的像； 
int DirectNum[2][2]={{0}} , DirectNumTemp[1]={0};                       // 对于（x，y）而言可行方向的翻转个数； 


struct Av{                                                          //用来存下所有可行的情况；power为权值；
	int x;
	int y;
	int power;
}av[30];


void CopyBoard()                                                    //board到board2进行映射； 
{
	for(int i(0); i<8; i++)
		for(int j(0); j<8; j++)
			board2[i][j]=board[i][j];
} 


void ChangeBoard()                                                 //黑白转换 
{
	for(int i(0); i<8; i++)
		for(int j(0); j<8; j++)
		{
			if(board2[i][j]==1)board2[i][j]=2;
			else if(board2[i][j]==2)board2[i][j]=1;
		}
}


int legalDirect(int x, int y, int i, int j, int flag)              //落子(x,y)在（i,j）方向上的可行性 ； 
{																   // 并计算中间量DirectNumTemp为该方向上可以翻转的个数?
	x += i;
	y += j;
	if (x < 0 || x >7 || y < 0 || y > 7)                         // 超出棋盘范围
	{
		return 0;
	}
	if (board2[x][y] == 2)
	{
     	DirectNumTemp[0]+=1;              //该方向上课翻转的个数加一。 
		                              /* (x,y)某个方向的有相邻的对手棋子,继续检查这个方向是否
		                              *  可以吃对方子,递归调用
	                               	  */
		flag = 1;
		return legalDirect(x, y, i, j, flag);
	}
	else if (board2[x][y] == 1)
	{
		/* 遇到自己的棋子,判断这个方向之前的棋子是否全为反方的即 flag=1*/
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


int legal(int x, int y)                                 //检查是否可以落子；并且确定出(x,y)在(i,j)方向上
{														//所能翻转的个数DirectNum[i][j]; 并记录可行方向；    其只要满足两条性质。
	if (board2[x][y]!=0)                                // 已经下子
		return 0;
	int i, j, flag;
	
	for (i = -1; i <= 1; i++)                          /* 检测(x,y)坐标点八个方向*/
	{
		for (j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)                      // (x,y)点忽略
			{
				continue;
			}
			flag = 0;
			if (legalDirect(x, y, i, j, flag))
			{
				return 1;
			}
			DirectNumTemp[0]=0;                            //中间量置零
		}
	}
	return 0;
}


int CanEatNum(int x,int y)                                //返回落子(x,y)能吃掉多少对方的子 
{
	CopyBoard();
	int i, j, flag,w=0;
	for (i = -1; i <= 1; i++)                          /* 检测(x,y)坐标点八个方向*/
	{
		for (j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)                      // (x,y)点忽略
			{
				continue;
			}
			flag = 0;
			if (legalDirect(x, y, i, j, flag))
			{
				w+= DirectNumTemp[0];
			}
			DirectNumTemp[0]=0;                            //中间量置零
		}
	}
	return w;
} 


void fanzhuan(int x ,int y)                           // 对于落子（x，y）对棋盘像board1进行翻转 ； 
{
	int i, j, flag;
	CopyBoard();
	board2[x][y]=1;
	for (i = -1; i <= 1; i++)                          // 检测(x,y)八个方向上所有满足情况进行翻转； 
	{
		for (j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)                      // (x,y)点忽略； 
			{
				continue;
			}
			flag = 0;
			if (legalDirect(x, y, i, j, flag))             //该方向满足； 
			{
				for(int k(0); k<DirectNumTemp[0]+1; k++){
					board2[x+i*k][y+j*k]= 1 ;          //该方向上黑子翻转 ； 
				} 
			}
			DirectNumTemp[0]=0;                            //中间量置零； 
		}
	}
}


bool isConner(int x ,int y)                           //是否为四个角； 
{
	if(x==0&&y==0)return 1;
	else if(x==0&&y==7)return 1;
	else if(x==7&&y==0)return 1;
	else if(x==7&&y==7)return 1;
	return 0; 
}

bool is1BesideConner(int x ,int y)                   //与4个角相邻的12个位置； 
{
	if(x==0||x==7)
		if(y==1||y==6)return 1;
	if(x==1||x==6)
		if(y==0||y==1||y==6||y==7)return 1;
	return 0;
}


bool is2BesideConner(int x ,int y)                   //与4个角隔两位的16个位置； 
{
	if(y==5||y==2)
		if(x==1||x==0||x==6||x==7)return 1;
	if(x==5||x==2)
			if(y==1||y==0||y==6||y==7)return 1;
	return 0;
} 


int WhiteCanGoNum (int x , int y)                     //对于每一个（x，y）的下法后，白棋可以下的个数； 
{
	int a=x,b=y;
	CopyBoard(); 
	fanzhuan(a,b);                                   
	ChangeBoard(); 									//棋盘黑白互换，来使函数legalDirect可以直接调用从而调用legal；
	int w=0;
	for(int i(0); i<8; i++)
		for(int j(0); j<8; j++)
			if(legal(i,j))w++;                           
	CopyBoard();                                    //复原； 
	return w;
} 


bool WhiteCanGotoConner(int x, int y)                 //黑棋下完后白棋  可以  去角落的情况； 
{
	int a=x,b=y;
	CopyBoard();
	fanzhuan(a,b);
	ChangeBoard();
	if(legal(0,0)||legal(7,7)||legal(0,7)||legal(7,0))
	{
		CopyBoard();
		return 1; 
	}
	CopyBoard();
	return 0;
}

bool WhiteCanGotoConner2(int x, int y)
{
	CopyBoard();
	int a=x,b=y;
	fanzhuan(a,b);
	ChangeBoard();
	for(int i(0); i<8; i++)
		for(int j(0); j<8; j++)
		{
			int a1=i,b1=j;
			if(is2BesideConner(a1,b1))
				if(legal(a1,b1)){
					CopyBoard();
					return 1; 
				}
		}
	CopyBoard();
	return 0;
}

bool CanEatWhiteInConner2(int x ,int y)
{
	CopyBoard();
	int a=x,b=y;
	fanzhuan(a,b);
	ChangeBoard();
	for(int i(0); i<8; i++)
		for(int j(0); j<8; j++)
		{
			int a1=i,b1=j;
			if(is2BesideConner(a1,b1))
				if(board[i][j]!=board2[i][j]){
					CopyBoard();
					return 1; 
				}
		}
	CopyBoard();
	return 0;
}

int GiveAv(Av av[])                                          //给所有的可行的下法赋值到av[]中，并返回可行的个数； 
{
	int k=0,a,b;
	for(int i(0); i<8; i++)
		for(int j(0); j<8; j++)
		{
			a=i;
			b=j;
			if(legal(a,b)){
				av[k].x = i;
				av[k].y = j;
				k++;
			}
		}
			
	return k ;
}









void Power(int k)                                       //初始权值计算； 
{
	
	for(int i(0); i<k; i++)
	{
		av[i].power=0;
		int x=av[i].x;
		int y=av[i].y;
		if(isConner(x,y))av[i].power+=35;
		if(WhiteCanGotoConner(x,y))av[i].power-=35;
		if(WhiteCanGotoConner2(x,y))av[i].power-=35;
		if(is1BesideConner(x,y))av[i].power-=30;
		if(is2BesideConner(x,y))av[i].power+=5;
		if(CanEatWhiteInConner2(x,y))av[i].power+=10;
	}
}



 int main()
{
	int w=0;
	for(int i(0); i<8; i++)                                //进行输入 ； 
		for(int j(0); j<8; j++)
		{
			cin >> board[i][j]; 
			if(board[i][j]==2||board[i][j]==1)w++;
		} 
		
	CopyBoard();
	
	bool key1=0, key2=0 ,key3=0;                                 				//第一阶段，第二阶段，第三阶段
	if(board[0][0]+board[0][7]+board[7][0]+board[7][7]>1)key3=1;				//第四阶段判断； 
	if(board[0][0]!=0||board[0][7]!=0||board[7][0]!=0||board[7][7]!=0)key2=1;  //第三阶段的判别； 
	if(w>38)key1=1;																//第二阶段的判断； 
	
	int k;
	k=GiveAv(av);
	Power(k);
	
	if(key3==1)                                                                 //第四阶段，吃掉尽可能多的棋子； 
	{
		for(int i(0); i<k; i++)
		{     
			av[i].power+=CanEatNum(av[i].x,av[i].y)*10;
		}
	}
	
	else if(key2==1)															//第三阶段，让白字少走，吃掉尽可能少的棋子； 
	{    
		for(int i(0); i<k; i++)
		{     
			av[i].power-=CanEatNum(av[i].x,av[i].y)*3;
			av[i].power-=WhiteCanGoNum(av[i].x,av[i].y)*8;
		}
		
	}

	else if(key1==1)                                                    		//第二阶段，尽可能让白子少走； 
	{
		for(int i(0); i<k; i++)
		{
			av[i].power-=CanEatNum(av[i].x,av[i].y)*4;
			av[i].power-=WhiteCanGoNum(av[i].x,av[i].y)*8;
		}
		
		
		
		
	}

	else                                                                        //第一种情况，尽可能少吃； 
	{
		for(int i(0); i<k; i++)
		{
			av[i].power-=CanEatNum(av[i].x,av[i].y)*8;
		}
		

	}
	
	int x=av[0].x,y=av[0].y,max=av[0].power;
	for(int i(1); i<k; i++)
		 if(av[i].power>max)
		 {
		 	max=av[i].power;
		 	x=av[i].x;
		 	y=av[i].y;
		 }
	if(k==0)return 1;
	
	

	cout << x <<" "<< y;	                                			//进行输出 
		return 1;
}