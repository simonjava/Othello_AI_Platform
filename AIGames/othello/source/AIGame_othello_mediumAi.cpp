#include<stdio.h>
#include<stdlib.h>

int board[10][10],maxi,maxj,DEPTH,S;            //定义棋盘,落子坐标,搜索深度,棋子颜色 

//函数声明 
void saveBoard (int temp[][10]);     //保存棋盘
void resetBoard (int temp[][10]);   //恢复棋盘 
int judge (int x,int y,int s);      //判断board[x][y]能否下棋
void newBoard (int x,int y, int s);           //建立新棋盘
long alphabeta (int s,int depth, long alpha,long beta);         //alpha-beta剪枝
int totalCount ();                    //计算当前棋盘棋子总数
int count (int s);                    //计算当前棋盘s子的个数(s=1黑棋,s=2白棋)
int mobility (int s);                  //计算s子的行动力(可下棋的位置数) 
int preMobility (int s);               //计算s子的潜在行动力(临近对手棋子的空格数)
int stab (int s);                       //稳定子分数估值 
int H_AX (int i,int s);                  //水平方向稳定子个数 
int V_AX (int j,int s);                 //垂直方向稳定子个数 
int BD_AX( int i,int j,int s);          //左上到右下方向稳定子判断 
int FD_AX (int i,int j,int s);          //右上到左下方向稳定子判断 
long cornerValue(int s);                 //边角估值
long lineValue (int s);                 //行估值 
long firstValue (int s);                //开局估值
long midValue(int s);                   //中局估值 
long lastValue (int com,int opp);       //终局估值 
long Value(int s);                      //估值函数 
long lastFind(int s,int depth, long alpha,long beta);        //终局搜索  

int main()
{
	int i,j,com,opp;					//i,j循环变量 
	char s1[9][9];						//保存输入的棋盘
	
	for(i=0;i<10;i++){					//设置棋盘边界为数字8

                      board[0][i]=8;board[9][i]=8;
                      board[i][0]=8;board[i][9]=8;

                      }

	S=1;				//输入黑棋(1)或白棋(2)
	
	com=S ;opp=(S==1)?2:1;			//com是电脑棋的颜色,opp是对手棋的颜色
	
	for(i=1;i<=8;i++)				//用int数组保存当前棋盘状态
                 {
               //   scanf("%s",s1[i]);
                  for(j=1;j<=8;j++) 
					  scanf("%d",&board[i][j]);
               //   board[i][j+1]=s1[i][j]-'0';

                                 }

	if(totalCount()<=18)  DEPTH=7;						//设置开局搜索深度
	
	if(totalCount()>18&&totalCount()<40)	DEPTH=7;       //中局搜索深度

	
	if(totalCount()>=40&&totalCount()<45)	DEPTH=9;       //中局搜索深度

	if(totalCount()>=45&&totalCount()<51)	DEPTH=11;       //中局搜索深度

	alphabeta(S,DEPTH,-100000000,100000000);				//α-β搜索 设置α为负无穷,β正无穷

	if(totalCount()>=51)  lastFind(S,DEPTH,-100000000,100000000);		//终局搜索

	printf("%d %d",maxi-1,maxj-1);								//下棋

 
}


void saveBoard(int temp[][10])      //保存棋盘 
{
     int i,j;
     for(i=0;i<10;i++)
     for(j=0;j<10;j++)
      temp[i][j]=board[i][j];
}

void resetBoard(int temp[][10])   //恢复棋盘 
{
     int i,j;
     for(i=0;i<10;i++)
     for(j=0;j<10;j++)
      board[i][j]=temp[i][j];
      
}
      


int judge(int x,int y,int s)	//判断board[x][y]能否下棋
{
    int m=x , n=y;                //保存当前坐标
    int com=s , opp=(s==1)?2:1;  //com是电脑棋的颜色,opp是对手棋的颜色
    
    if(board[x][y]!=0) return 0;      //位置不为空,返回0
    //左边
    while(board[x][--y] == opp);
    if(board[x][y]==com && board[x][y+1]==opp)	return 1;  		//&&board[x][y+1]==opp避免左边只有1颗自己棋的状态  
	else { x=m ;  y=n; }		 //恢复坐标 
	
    //右边 
    while(board[x][++y] == opp);
    if(board[x][y]==com && board[x][y-1]==opp)	return 1;   
    else { x=m ; y=n; } 

    //上边 
    while(board[--x][y] == opp);
    if(board[x][y]==com && board[x+1][y]==opp)	return 1;   
    else { x=m ; y=n; } 
	
    //下边
    while(board[++x][y] == opp);
    if(board[x][y]==com && board[x-1][y]==opp)	return 1;   
    else { x=m ; y=n; }
	
    //左上
    while(board[--x][--y] == opp);
    if(board[x][y]==com && board[x+1][y+1]==opp)	return 1;   
    else { x=m ; y=n; }

    //右上
    while(board[--x][++y] == opp);
    if(board[x][y]==com && board[x+1][y-1]==opp)	return 1;   
    else { x=m ; y=n; }

    //左下
    while(board[++x][--y] == opp);
    if(board[x][y]==com && board[x-1][y+1]==opp)	return 1;   
    else { x=m ; y=n; }
    //右下
    while(board[++x][++y] == opp);
    if(board[x][y]==com && board[x-1][y-1]==opp)	return 1;   
    else { x=m ; y=n; }
    
    return 0;			//不能下棋
}                   


void newBoard(int x,int y, int s)           //建立新棋盘
{
     int m=x , n=y;                              //保存当前坐标
     int com=s , opp=(s==1)?2:1;                //com是电脑棋的颜色,opp是对手棋的颜色
    
     
     //左边
     while(board[x][--y]==opp);
     if(board[x][y]==com && board[x][y+1]==opp){
                      for(;y<n;)
                                board[x][++y]=com;             //吃棋 
								 }               
     else { x=m ;y=n; }                                      //恢复坐标 

     //右边 
     while(board[x][++y] ==opp);
     if(board[x][y]==com && board[x][y-1]==opp){
                      for(;y>n;)
                               board[x][--y]=com;  
								 } 
     else { x=m ;y=n; } 

     //上边 
     while(board[--x][y] ==opp);
     if(board[x][y]==com && board[x+1][y]==opp){
                      for(;x<m;)
                                board[++x][y]=com; 
								 }  
     else { x=m ;y=n; }
	 
     //下边
     while(board[++x][y] ==opp);
     if(board[x][y]==com && board[x-1][y]==opp){
                      for(;x>m;)
                                board[--x][y]=com; 
									}
     else { x=m ;y=n; }
	 
     //左上
     while(board[--x][--y] ==opp);
     if(board[x][y]==com && board[x+1][y+1]==opp){
                      for(;x<m&&y<n;)
                                     board[++x][++y]=com;
										 }   
     else { x=m ;y=n; }

     //右上
     while(board[--x][++y] ==opp);
     if(board[x][y]==com && board[x+1][y-1]==opp){
                      for(;x<m&&y>n;)
                                     board[++x][--y]=com;
										}   
     else { x=m ;y=n; }

     //左下
     while(board[++x][--y] ==opp);
     if(board[x][y]==com && board[x-1][y+1]==opp){
                      for(;x>m&&y<n;)
                                     board[--x][++y]=com;
										}   
     else { x=m ;y=n; }

     //右下
     while(board[++x][++y] ==opp);
     if(board[x][y]==com && board[x-1][y-1]==opp){
                      for(;x>m&&y>n;)
                                     board[--x][--y]=com;
										}   
     else { x=m ;y=n; }
    

} 


long alphabeta (int s,int depth, long alpha,long beta)         //alpha-beta剪枝
{
    int com,opp,temp[10][10],i,j,flag=0,k=0;					//temp保存棋盘 flag为跳出外层循环标志 k是否有棋可下 
    long value;
    com=s ;	opp=(s==1)?2:1;
    if(depth<=0)   return Value(s);							//到达深度返回估植
    
    if(depth%2==0){											//该层为MAX结点
		for(i=1;i<9;i++){
			for(j=1;j<9;j++)
				if(judge(i,j,com)){
                                    k=1;                  //可下棋 
									saveBoard(temp);				//保存棋盘
									newBoard(i,j,com);			//下棋 建立新棋盘
									value=alphabeta(opp,depth-1,alpha,beta);		//搜索下一结点
									resetBoard(temp);				//恢复棋盘
									if(value>alpha&&value<beta){
																alpha=value;
																if(depth==DEPTH){			//如果是初始棋盘 保存下棋坐标
																					maxi=i;	
																					maxj=j;
																					}
																	}

										else if (value>=beta){				//剪枝
																alpha=value;
																flag=1;
																break;
																}
									}
			if(flag){				//跳出外层循环
					flag=0;
					break;
						}
		}//for
    if(k==0) return Value(S);             //如果没棋可下 返回当前估值 
	return alpha;						//返回alpha值
	}//if

                   
    if(depth%2==1){										//该层为MIN结点						
		for(i=1;i<9;i++){
			for(j=1;j<9;j++)
				if(judge(i,j,com)){
                                    k=1;                //可下棋 
									saveBoard(temp);				//保存棋盘
									newBoard(i,j,com);			//下棋 建立新棋盘
                                    value=alphabeta(opp,depth-1,alpha,beta);		//搜索下一结点
                                    resetBoard(temp);				//恢复棋盘
                                    if(value>alpha&&value<beta){
                                                                beta=value;
                                                                if(depth==DEPTH){			//如果是初始棋盘 保存下棋坐标
                                                                                maxi=i;
                                                                                maxj=j;
                                                                                  }
                                                                  }
										else if (value<=alpha){				//剪枝
                                                                beta=value;
                                                                flag=1;
                                                                break;
																	}

                                                                      }
             if(flag){			//跳出外层循环
                      flag=0;
                      break;
                        }
			}//for
        if(k==0) return Value(S);  //如果没棋可下 返回当前估值 
		return beta;
    }//if
}//end
                                                                                            
                                                                                                                   
                                                        



int totalCount ()                    //计算当前棋盘棋子总数 
{
    int num=0,i,j;
    for(i=1;i<=8;i++)
		for(j=1;j<=8;j++)
			if(board[i][j]!=0) num++;
    return num;
}    

  
int count (int s)                    //计算当前棋盘s子的个数(s=1黑棋,s=2白棋)
{
    int num=0,i,j;
    for(i=1;i<=8;i++)
		for(j=1;j<=8;j++)
			if(board[i][j]==s) num++;
    return num;
}      

int mobility (int s)                  //计算s子的行动力(可下棋的位置数) 
{
    int move=0,i,j;
    for(i=1;i<=8;i++)
		for(j=1;j<=8;j++)
			if(judge(i,j,s)) move++;
    return move;
}


int preMobility (int s)               //计算s子的潜在行动力(临近对手棋子的空格数) 
{
    int opp=(s==1)?2:1;				//opp是对手棋的颜色
    int preMove=0,i,j;
    for(i=1;i<=8;i++)
		for(j=1;j<=8;j++)
    //判断坐标i,j 是否为空且其8个邻近位置是否含有敌棋 
			if(board[i][j]==0&&(board[i][j-1]==opp||board[i][j+1]==opp||board[i+1][j]==opp||board[i-1][j]==opp||board[i+1][j-1]==opp||board[i+1][j+1]==opp||board[i-1][j-1]==opp||board[i-1][j+1]==opp))   
					preMove++;
    return preMove; 
}

int H_AX(int i,int s)                     //水平方向稳定子个数 
{
    int j,y,nstab=0,count=0,ncom=0;		//nstab为稳定子的个数
    int com,opp;
    com=s;	opp = (s==1)?2:1;
    for(j=1;j<9;j++)					//对于每一行
		if(board[i][j]!=0){
						if(board[i][j]==com) ncom++;		//其中自己棋子的个数
						count++;						//总棋子数
						}								
			else break;

    if(count==8)	return ncom;						//如果一列有8颗棋 则返回自己棋子个数(每个棋子一分)

    for(j=1;j<9;j++)
		if(board[i][j]==com){	//begin if
							y=j;
							while(board[i][--j]==com);         //判断左边 
							if(board[i][j]==8){                //8为棋盘边界 
											j=y;         //恢复坐标             
											nstab++;
											continue;
												}
								else if(board[i][j]==opp){                       //左边有敌棋
														j=y;
														while(board[i][++j]==com);    //判断右边
														if(board[i][j]!=0){           //右边不为空
																		j=y;       //恢复坐标 
																		nstab++;
																		continue;
																			}
                                                           }
                                                           
							j=y;
							while(board[i][++j]==com);        //判断右边
							if(board[i][j]==8){
											j=y;       //恢复坐标 
											nstab++;
											continue;
												}
									else if(board[i][j]==opp){                  //右边有敌棋
															j=y;
															while(board[i][--j]==com);    //判断左边
															if(board[i][j]!=0){           //左边不为空
																			j=y;       //恢复坐标  
																			nstab++;
																			continue;
																				}
																}
							j=y;        //恢复坐标          
								}//end if
    return nstab;
}

int V_AX(int j,int s)                 //垂直方向稳定子个数 
{
    int i,x,nstab=0,count=0,ncom=0;
    int com,opp;
    com=s;opp = (s==1)?2:1;
    for(i=1;i<9;i++)				//对于每一列		
		if(board[i][j]!=0){
						if(board[i][j]==com) ncom++;	//其中自己棋子的个数
						count++;					//总棋子数
							}
			else break;
    if(count==8)	return ncom;		//如果一列有8颗棋 则返回自己棋子个数(每个棋子一分)

    for(i=1;i<9;i++)			
		if(board[i][j]==com){	//begin if
							x=i;
							while(board[--i][j]==com);         //判断上边 
							if(board[i][j]==8){                //8为棋盘边界 
											i=x;         //恢复坐标             
											nstab++;
											continue;
												}
								else if(board[i][j]==opp){                       //上边有敌棋
														i=x;
														while(board[++i][j]==com);    //判断下边
														if(board[i][j]!=0){           //下边不为空
																		i=x;       //恢复坐标 
																		nstab++;
																		continue;
																			}
                                                           }
                                                           
							i=x;
							while(board[++i][j]==com);        //判断下边
							if(board[i][j]==8){
											i=x;       //恢复坐标 
											nstab++;
											continue;
												}
								else if(board[i][j]==opp){                  //下边有敌棋
														i=x;
														while(board[--i][j]==com);    //判断上边
														if(board[i][j]!=0){           //上边不为空
																		i=x;       //恢复坐标  
																		nstab++;
																		continue;
																			}
                                                            }
							i=x;        //恢复坐标          
							}//end if
    return nstab;
}

int BD_AX(int i,int j,int s)          //左上到右下方向稳定子判断 
{
    
    int x,y;
    int com,opp;
    com=s;opp = (s==1)?2:1;
    if(board[i][j]==com){
						x=i;y=j;
						while(board[--i][--j]==com);         //判断左上边 
						if(board[i][j]==8)    return 1;		//如果最邻边是边界 则稳定
							else if(board[i][j]==opp){			//左上边有敌棋
													i=x;j=y;
													while(board[++i][++j]==com);    //判断右下边
													if(board[i][j]!=0)    return 1;      //右下边不为空
														}
                                                           
						i=x;j=y;
						while(board[++i][++j]==com);        //判断右下边
						if(board[i][j]==8)    return 1;
							else if(board[i][j]==opp){			//右下边有敌棋
													i=x;j=y;
													while(board[--i][--j]==com);    //判断左上边
													if(board[i][j]!=0)    return 1;       //左上边不为空
														}
						}
    return 0;
}

int FD_AX(int i,int j,int s)          //右上到左下方向稳定子 判断 
{
    
    int x,y;
    int com,opp;
    com=s;opp = (s==1)?2:1;
    if(board[i][j]==com){
						x=i;y=j;
						while(board[--i][++j]==com);         //判断右上边 
						if(board[i][j]==8)    return 1;
							else if(board[i][j]==opp){                       //右上边有敌棋
													i=x;j=y;
													while(board[++i][--j]==com);    //判断左下边
													if(board[i][j]!=0)    return 1;      //右下边不为空
														}
                                                           
						i=x;j=y;
						while(board[++i][--j]==com);        //判断左下边
						if(board[i][j]==8)    return 1;
							else if(board[i][j]==opp){                    //左下边有敌棋
													i=x;j=y;
													while(board[--i][++j]==com);    //判断右上边
													if(board[i][j]!=0)    return 1;       //右上边不为空
														}
							}
    return 0;
} 


int stab(int s)                       //稳定子分数估值 
{
    int i,j,value=0;
    for(i=1;i<9;i++)
		value+=H_AX(i,s);

    for(j=1;j<9;j++)
		value+=V_AX(j,s);

	for(i=1;i<9;i++)
		for(j=1;j<9;j++)
			value+=BD_AX(i,j,s);

	for(i=1;i<9;i++)
		for(j=1;j<9;j++)
			value+=FD_AX(i,j,s);
                                      
	return value;
      
}

long cornerValue(int s)                                //边角估值
{
    int com,opp,i,j;
    long value=0;
    com=s ;opp=(s==1)?2:1;
    if(board[1][1]==com)      value+=1000;       //角的估值 
    if(board[1][8]==com)      value+=1000;
    if(board[8][1]==com)      value+=1000;
    if(board[8][8]==com)      value+=1000;
    
    if(board[1][1]==opp)      value-=1000;       //角的估值 
    if(board[1][8]==opp)      value-=1000;
    if(board[8][1]==opp)      value-=1000;
    if(board[8][8]==opp)      value-=1000;
    
    if(board[1][1]==0){                                      //如果左上角的棋盘为空 
		if(board[1][2]==com){              //如果(1,2)棋子为己方 
							j=2;
							while(board[1][++j]==com);
							if(board[1][j]==opp) value-=1000;             //在右侧有敌方棋子value减少 
								}
		if(board[2][1]==com){                   //如果在第一列下棋且(2,1)棋子为己方
							i=2;
							while(board[++i][1]==com);
							if(board[i][1]==opp) value-=1000;             //在下侧有敌方棋子value减少
								}
		if(board[2][2]==com){                //如果(2,2)棋子为己方
							i=2;j=2;
							while(board[++i][++j]==com);
							if(board[i][j]==opp) value-=1000;        //在右下侧有敌方棋子 value减少 
								}
                   }
                   
    if(board[1][8]==0){                                      //如果右上角的棋盘为空 
		if(board[1][7]==com){                    //如果(1,7)棋子为己方 
							j=7;
							while(board[1][--j]==com);
							if(board[1][j]==opp) value-=1000;             //在左侧有敌人棋子value减少 
								}
		if(board[2][8]==com){                   //如果在(2,8)棋子为己方
							i=2;
							while(board[++i][1]==com);
							if(board[i][1]==opp) value-=1000;             //在下侧有敌人棋子value减少
								}
		if(board[2][7]==com){                  //如果(2,7)棋子为己方
							i=2;j=7;
							while(board[++i][--j]==com);
							if(board[i][j]==opp) value-=1000;           //在右下侧有敌方棋子 value减少  
								}           
                   }
                   
    if(board[8][1]==0){                                     //左下角                                                           
		if(board[8][2]==com){              
							j=2;
							while(board[8][++j]==com);
							if(board[8][j]==opp) value-=1000;             
								}
		if(board[7][1]==com){                  
							i=7;
							while(board[--i][1]==com);
							if(board[i][1]==opp) value-=1000;             
								}
		if(board[7][2]==com){                  
							i=7;j=2;
							while(board[--i][++j]==com);
							if(board[i][j]==opp) value-=1000;            
								}
                   }
                   
    if(board[8][8]==0){                                     //右下角                                                           
		if(board[8][7]==com){              
							j=7;
							while(board[8][--j]==com);
							if(board[8][j]==opp) value-=1000;             
								}
		if(board[7][8]==com){                  
							i=7;
							while(board[--i][8]==com);
							if(board[i][8]==opp) value-=1000;             
								}
		if(board[7][7]==com){                  
							i=7;j=7;
							while(board[--i][--j]==com);
							if(board[i][j]==opp) value-=1000;            
								}
                   }
    return value;
}               
     
long lineValue (int s)                //行列估值 
{
    int com,opp,i,j,x,y;
    long value=0;
    com=s ;opp=(s==1)?2:1;
    for(x=1;x<=8;x++){
						if(board[x][1]==opp){
											j=1;
											while(board[x][++j]==opp);
											if(board[x][j]==com){
																while(board[x][++j]==com);
																if(board[x][j]==0) value-=100; 
																	}
												}

						if(board[x][8]==opp){
											j=8;
											while(board[x][--j]==opp);
											if(board[x][j]==com){
																while(board[x][--j]==com);
																if(board[x][j]==0) value-=100; 
																	}
												}
                      }
                     
    for(y=1;y<=8;y++){
						if(board[1][y]==opp){
											i=1;
											while(board[++i][y]==opp);
											if(board[i][y]==com){
																while(board[++i][y]==com);
																if(board[i][y]==0) value-=100; 
																	}
												}

						if(board[8][y]==opp){
											i=8;
											while(board[--i][y]==opp);
											if(board[i][y]==com){
																while(board[--i][y]==com);
																if(board[i][y]==0) value-=100; 
																	}
										}
                     }
    return value;
} 


long firstValue (int s)                      //开局估值 
{
    int com,opp;
    long value=0;
    com=s ;opp=(s==1)?2:1;
    value+=30*cornerValue(s)+30*lineValue(s)+100*stab(s); 
    value+=20*(mobility(com)- mobility(opp))+5*(preMobility(com)- preMobility(opp));
    
    return value;
}                                            

long midValue (int s)						//开局估值
{
    int com,opp;
    long value=0;
    com=s ;opp=(s==1)?2:1;
    value+=30*(mobility(com)-mobility(opp))+8*(preMobility(com)-preMobility(opp));
    value+=30*cornerValue(s)+30*lineValue(s)+100*stab(s);
    
    return value;
}                                                                                                                                                                                                                                                             
long lastValue (int com,int opp)            //终局估值 
{
    return count(com)-count(opp);
}

long Value(int s)                           //估值函数
 {
     int com,opp;
     com=s ;opp=(s==1)?2:1;                                
     if(totalCount()<=18)	return firstValue(s);
     if(totalCount()>18&&totalCount()<51)
							return midValue(s);
       else return lastValue(com,opp);
     
                                                   
}


long lastFind(int s,int depth, long alpha,long beta)
{
    int com,opp,temp[10][10],i,j,flag=0,k=0;
    long value;
    com=s ;opp=(s==1)?2:1;
    if(totalCount()==64)   return lastValue(S,S==1?2:1);			//搜索到结束
    
    if(depth%2==0){
		for(i=1;i<9;i++){
			for(j=1;j<9;j++)
				if(judge(i,j,com)){
                                    k=1;                        
									saveBoard(temp);
									newBoard(i,j,com);
									value=alphabeta(opp,depth-1,alpha,beta);
									resetBoard(temp);
									if(value>alpha&&value<beta){
																	alpha=value;
																	if(depth==DEPTH){
																						maxi=i;
																						maxj=j;
																							}
																		}
																		else if (value>=beta){
																								alpha=value;
																								flag=1;
																								break;
																								}
																			}
                                   if(flag){
                                            flag=0;
                                            break;
                                            }
                                   }
                   if(k==0) return Value(S);
                   return alpha;
                   }
                   
    if(depth%2==1){
		for(i=1;i<9;i++){
			for(j=1;j<9;j++)
				if(judge(i,j,com)){
                                    k=1;
									saveBoard(temp);
									newBoard(i,j,com);
									value=alphabeta(opp,depth-1,alpha,beta);
									resetBoard(temp);
									if(value>alpha&&value<beta){
																	beta=value;
																	if(depth==DEPTH){
																						maxi=i;
																						maxj=j;
																						}
																		}
																		else if (value<=alpha){
																								beta=value;
																								flag=1;
																								break;
																									}
																	}
                                   if(flag){
                                            flag=0;
                                            break;
                                            }
                                   }
                   if(k==0) return Value(S);
                   return beta;
                   }
}