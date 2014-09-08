#include<cstdio>
#include<iostream>
using namespace std;

//所有的函数都调用board的像board2；


int board[8][8] = {{0}} , board2[8][8] = {{0}} ;                 //board2为board的像；
int DirectNumTemp = 0;                 // 对于（x，y）而言可行方向的翻转个数；
const int DEPTH = 7;                   //奇数 
const int First =40 ;

void Print()
{
	for(int i(0); i < 8; i++)
	{
		for(int j(0); j < 8; j++)
    	{		
    		printf("%d",board2[i][j]);
 		}
		printf("\n");
	}
	printf("\n");
}

//board到board2进行映射；
void CopyBoard()                                                 
{
    for(int i(0); i < 8; i++)
        for(int j(0); j < 8; j++)
            board2[i][j] = board[i][j];
}

void CopyToBoardTemp(int boardtemp[8][8])                                                 
{
    for(int i(0); i < 8; i++)
        for(int j(0); j < 8; j++)
            boardtemp[i][j] = board2[i][j];
}

//落子(x,y)在（i,j）方向上的可行性 ；
bool LegalDirect(int x, int y, int i, int j, int flag , int &DirectNumTemp)             
{
    // 并计算中间量DirectNumTemp为该方向上可以翻转的个数?
    x += i;
    y += j;

    if (x < 0 || x > 7 || y < 0 || y > 7)                        // 超出棋盘范围
        return 0;

    int flagtemp;
    if(board2[x][y] == 2)flagtemp = 0;                         //判断当前棋子是黑是白；
    else if(board2[x][y] == 1)flagtemp = 1;
    else return 0;										//如果没有棋子 ,返回；

    if(flag == flagtemp && DirectNumTemp != 0)return 1;    //判断当前棋子是否合之前一样；

    else if (flagtemp != flag )
        {
            DirectNumTemp ++;              //该方向上课翻转的个数加一。
            /* (x,y)某个方向的有相邻的对手棋子,继续检查这个方向是否
            *  可以吃对方子,递归调用
            */
            return LegalDirect(x, y, i, j, flag, DirectNumTemp);
        }
    return 0;
}

//检查是否可以落子；并且确定出(x,y)在(i,j)方向上
bool Legal(int x, int y, int flag)                                
{
    //所能翻转的个数DirectNum[i][j]; 并记录可行方向；    其只要满足两条性质。
    if (board2[x][y] != 0)                              // 已经下子
        return 0;
    int i, j;

    for (i = -1; i <= 1; i++)                          // 检测(x,y)坐标点八个方向
        {
            for (j = -1; j <= 1; j++)
                {
                    if (i == 0 && j == 0)                      // (x,y)点忽略
                        {
                            continue;
                        }
                    if (LegalDirect(x, y, i, j, flag, DirectNumTemp))
                        {
                        	DirectNumTemp = 0;                          //中间量置零
                            return 1;
                        }
                    DirectNumTemp = 0;                          //中间量置零
                }
        }
    return 0;
}

// 对于落子（x，y）对棋盘像board1进行翻转 ；
void make_move(int x , int y, int flag,int boardtemp[][8])                           
{
	CopyToBoardTemp(boardtemp);
    int i, j,temp1= ((flag==0) ?2:1 );
    board2[x][y] = temp1;
    for (i = -1; i <= 1; i++)                          // 检测(x,y)八个方向上所有满足情况进行翻转；
        {
            for (j = -1; j <= 1; j++)
                {
                    if (i == 0 && j == 0)                      // (x,y)点忽略；
                        continue;
                    if ( LegalDirect(x, y, i, j, flag, DirectNumTemp)) //该方向满足；
					{
						for(int k(0); k < DirectNumTemp + 1; k++)
                            board2[x + i * k][y + j * k] = temp1 ; //该方向上黑子翻转 ；
					}           
                    DirectNumTemp = 0;
                }
        }
}


void unmake_move(int boardtemp[8][8])                                                 
{
    for(int i(0); i < 8; i++)
        for(int j(0); j < 8; j++)
            board2[i][j] = boardtemp[i][j];
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
	if((x==2&&y==2 )||( x==2&&y==5 )||( x==5&&y==5 )|| (x==5&&y==2) )return 1;
	
	return 0;
} 

/*int CanGoNum (int flag)                     //对于每一个（x，y）的下法后，白棋可以下的个数； 
{
	int w=0;
	for(int i(0); i<8; i++)
		for(int j(0); j<8; j++)
			if(Legal(i,j,flag))w++;                           
	return w;
}*/


int evaluation(int board2[8][8])
{
	int value(0), Total(0), White(0), Black(0), Conner(0);
	for(int i(0); i<8; i++)
		for(int j(0);j<8; j++)
		{
			if(board2[i][j]==2)White++;
			else if(board2[i][j]==1)Black++;
		}
	Total = Black + White ;
	if(Black < 5)value = -10000;
	for(int i(0); i<8; i++)
	for(int j(0); j<8; j++)
	{
		if(board2[i][j]==0)continue;
		if(isConner(i,j))
		{
			if(board2[i][j]==1)value+=1000;
			else value-=1000;
			Conner++;
		}
		if(is1BesideConner(i,j))
		{
			if(board2[i][j]==1)value-=100;
			else value+=100;
		}
		if(is2BesideConner(i,j))
		{
			if(board2[i][j]==1)value+=20;
			else value-=20;
		}
	}
	if(Conner>1)
	{
		value+=Black;
		value-=White;
	}
	else if(Total > First)
	{
		value-=Black;
		value+=White;
	}
//	cout << "evaluation" << value << endl;
	return value;
}


int get_exact()
{
	int value(0), White(0), Black(0);
	for(int i(0); i<8; i++)
		for(int j(0);j<8; j++)
		{
			if(board2[i][j]==2)White++;
			else if(board2[i][j]==1)Black++;
		}
	for(int i(0); i<8; i++)
		for(int j(0);j<8; j++)
			if(board2[i][j]==2){
				value+=Black;
				value-=White;
			}
//	cout << "get_exact" << value << endl;
	return value;
}

int alpha_beta(int alpha, int beta, int depth, int pass)
{
	int boardtemp[8][8] = {{0}};
	int flag(0);
	bool key (1);
	if(depth % 2 == 1)flag = 1;
	// 当前最佳估值，预设为负无穷大
	int best_value = -10000000;
	// 如果到达预定的搜索深度
	if (depth == DEPTH) {
		// 直接给出估值
		return evaluation(board2);
	}
	// 尝试每个下棋位置
	for(int i(0); i < 8; i++)
        for(int j(0); j < 8; j++)
                if(Legal(i, j, flag))
                {
                    make_move(i,j,flag,boardtemp);
                    // 对所形成的局面进行递归搜索
					int value = -alpha_beta(-beta, -alpha, depth+1, 0);
					// 恢复原来的局面
					unmake_move(boardtemp);
					// 如果这步棋引发剪枝
					if (value >= beta) 
					{
					// 停止对当前局面的搜索，立即返回
					return value;
					}
						// 如果这步棋更好
					if (value > best_value)
					{
						// 保存更好的结果
						best_value = value;
						// 更新估值下限
						if (value > alpha) 
						{
							alpha = value;
						}
					}
					key = 0;
				}
	// 如果没有合法棋步
	if (key)
	 {
		// 如果上一步棋也是弃着，表明对局结束
		if (pass) 
		{
			// 计算出盘面的精确比分
			return get_exact();
		}
		CopyToBoardTemp(boardtemp);
		// 递归搜索，并标明该步弃着
		best_value = -alpha_beta(-beta, -alpha, depth+1, 1);
		// 恢复原来的局面
		unmake_move(boardtemp);
	}
	// 返回最佳估值
	return best_value;
}

int main()
{
    int Total = 0;
    for(int i(0); i < 8; i++)                              //进行输入 ；
        for(int j(0); j < 8; j++)
            {
                scanf("%d", &board[i][j]);
                if(board[i][j] != 0)Total++;
            }
    CopyBoard();
    int xans(0),yans(0),flag(1),bestvalue(-100000),depth(1),value(-100000);
	
    for(int i(0); i < 8; i++)
        for(int j(0); j < 8; j++)
                if(Legal(i, j, flag))
                {
                	int boardtemp[8][8] = {{0}};
                	make_move(i,j,flag,boardtemp);
                	value =  -alpha_beta(-100000,100000,depth+1,0);
                	unmake_move(boardtemp);
                	if(value > bestvalue)
                	{
                		xans = i; yans = j; bestvalue = value ;
                	}
                }
    printf("%d %d",xans,yans);
	//选出极大值； 
}