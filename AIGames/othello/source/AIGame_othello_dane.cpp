	#include <stdio.h>
#define BLACK 1
#define WHITE -1
#define EMPTY 0

class CBwfind 
{
public:
	//保存棋局
	void SaveBoard(int tb[][8]);
	int outcome;
	int bak;
	//记录64步的棋局，以便反悔
	int save[64][8][8];
	bool preview;
	int stepx,stepy;
	//搜索
	bool search(int tb[][8],int);
	int depth;
	int searchend;
	//计数
	int CountNum();
	int CountWhite();
	int CountBlack();
	void select(int);
	void newboard(int tb[][8],int,int,int);
	bool decide(int,int,int);
	CBwfind();
	int board[8][8];
	virtual ~CBwfind();
	int ComChoice,ManChoice;
    
protected:
	
private:
	//估价函数
	void Corner(int tb[][8],int i,int j,int &value);
	void LineSense(int tb[][8],int chessx,int chessy,int &value);
	int Mobility(int tb[][8],int flag);
	void CornerSense(int tb[][8],int &);
	int valuefirst(int tb[][8]);
	int findfirst(int tb[][8],int &,int &, int);
	//计数
	int white(int tb[][8]);
	int black(int tb[][8]);
	int Total(int tb[][8]);
	bool judge(int tb[][8],int chessx,int chessy,int flag);
	int findlast(int tb[][8], int &,int &,int);
};

//////////////////////////////////////////////////////////////////////

CBwfind::CBwfind()
{
	int i,j;	
	stepx=-1;
	stepy=-1;
	depth=6;
	searchend=51;
	preview=false;
	outcome=0;

	for(i=0;i<8;i++) for(j=0;j<8;j++)
		board[i][j]=EMPTY;

	board[3][3]=WHITE;
	board[4][4]=WHITE;
	board[3][4]=BLACK;
	board[4][3]=BLACK;
}

CBwfind::~CBwfind()
{

}

//决策
bool CBwfind::decide(int chessx, int chessy, int flag)
{
	//判断有效性
	if(chessx>7||chessx<0||chessy>7||chessy<0)
		return false;
	if(board[chessx][chessy]==0)
		return judge(board,chessx,chessy,flag);
	else 
		return false;
}

//判断棋子能否落在当前位置
bool CBwfind::judge(int tb[][8],int chessx, int chessy, int flag)
{
	int x=chessx,y=chessy;
	if(tb[x][y]!=0) return false;
	//左上
	if(x>=2&&y>=2)
		if(tb[x-1][y-1]+flag==0){
			x=x-2;
			y=y-2;
			while(x>=0&&y>=0){
				if(tb[x][y]==flag) 
					return true;
				else if(tb[x][y]==-flag)
				{
					x--;
					y--;
				}
				else {x=-1;y=-1;}
			}
		}
	//上
	x=chessx;
	y=chessy;
	if(x>=2)
		if(tb[x-1][y]+flag==0){
			x=x-2;
			while(x>=0){
				if(tb[x][y]==flag) 
					return true;
				else if(tb[x][y]==-flag) 
					x--;
				else
				{
					x=-1;
				}
			}
		}
	//右上
	x=chessx;
	y=chessy;
	if(x>=2&&y<=5)
		if(tb[x-1][y+1]+flag==0){
			x=x-2;y=y+2;
			while(x>=0&&y<=7){
				if(tb[x][y]==flag) return true;
				else if(tb[x][y]==-flag)
				{
					x--;
					y++;
				}
				else {x=-1;}
				//x--;y++;
			}
		}
	//右
	x=chessx;
	y=chessy;
	if(y<=5)
		if(tb[x][y+1]+flag==0){
			y=y+2;
			while(y<=7){
				if(tb[x][y]==flag) return true;
				else if(tb[x][y]==-flag){y++;}
				else {y=8;}
				//y++;
			}
		}
	//右下
	x=chessx;
	y=chessy;
	if(x<=5&&y<=5)
		if(tb[x+1][y+1]+flag==0){
			x=x+2;y=y+2;
			while(x<=7&&y<=7){
				if(tb[x][y]==flag) return true;
				else if(tb[x][y]==-flag){x++;y++;}
				else {x=8;y=8;}
				//x++;y++;
			}
		}
	//下
	x=chessx;
	y=chessy;
	if(x<=5)
		if(tb[x+1][y]+flag==0){
			x=x+2;
			while(x<=7){
				if(tb[x][y]==flag) return true;
				else if(tb[x][y]==-flag){x++;}
				else {x=8;}
				//x++;
			}
		}
	//左下
	x=chessx;
	y=chessy;
	if(x<=5&&y>=2)
		if(tb[x+1][y-1]+flag==0){
			x=x+2;y=y-2;
			while(x<=7&&y>=0){
				if(tb[x][y]==flag) return true;
				else if(tb[x][y]==-flag){x++;y--;}
				else {y=-1;}
			}
		}
	//左
	x=chessx;
	y=chessy;
	if(y>=2)
		if(tb[x][y-1]+flag==0){
			y=y-2;
			while(y>=0){
				if(tb[x][y]==flag) return true;
				else if(tb[x][y]==-flag){y--;}
				else {y=-1;}
			}
		}
	return false;
			
}


void CBwfind::select(int flag)
{
	int step,i,j,cut=1000000,tf=flag;
	int tb[8][8];
	for(i=0;i<8;i++)for(j=0;j<8;j++) tb[i][j]=board[i][j];
	step=CountNum();
	//开局
	if(step<searchend){
		int ss=0;
		findfirst(tb,ss,tf,cut);
	}
	//终局
	else if(step>=searchend){
		preview=true;
		outcome=findlast(tb,step,tf,cut);
	}
}

int CBwfind::CountBlack()
{
	int CB=0;
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			if(board[i][j]== BLACK) CB++;
	return CB;
}

int CBwfind::CountWhite()
{
	int WB=0;
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			if(board[i][j]== WHITE) WB++;
	return WB;
}



int CBwfind::CountNum()
{
	int Number=0,i,j;
	for(i=0;i<8;i++)for(j=0;j<8;j++)
		if(board[i][j]!=0) Number++;
	return Number;
}




int CBwfind::Total(int tb[][8])
{
	int Num=0,i,j;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
			if(tb[i][j]==0) Num++;
	return Num;
}

int CBwfind::black(int tb[][8] )
{
	int Bn=0,i,j;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
			if(tb[i][j]-1==0) Bn++;
	return Bn;
}

int CBwfind::white(int tb[][8] )
{
	int Wn=0,i,j;
		for(i=0;i<8;i++)
		for(j=0;j<8;j++)
			if(tb[i][j]==-1) Wn++;
	return Wn;
}



bool CBwfind::search(int tb[][8] , int flag)
{
	int i,j;
	for(i=0;i<8;i++)for(j=0;j<8;j++)
		if(judge(tb,i,j,flag)) return true;
	return false;
}

int CBwfind::findfirst(int tb[][8] , int &step, int &flag, int cut)
{
	int value=0,max=-100000,min=100000,k=0,i,j;
	int temp[8][8];
	if(step==depth){
		return valuefirst(tb);
	}
	for(i=0;i<8;i++)for(j=0;j<8;j++) temp[i][j]=tb[i][j];
	for(i=0;i<8;i++)for(j=0;j<8;j++){
		if(judge(tb,i,j,flag)){
			int ii,jj;
			value=0;
			k=1;//存在合理的步子
			newboard(tb,i,j,flag);
			flag=-flag;
			step++;
			if(-flag==ComChoice){
				LineSense(tb,i,j,value);
				Corner(tb,i,j,value);
				value+=findfirst(tb,step,flag,max);
			}
			if(-flag==ManChoice){
				Corner(tb,i,j,value);
				LineSense(tb,i,j,value);
				value+=findfirst(tb,step,flag,min);
			}
			step--;
			flag=-flag;
			//恢复棋盘
			for(ii=0;ii<8;ii++)
				for(jj=0;jj<8;jj++) 
					tb[ii][jj]=temp[ii][jj];
			if(flag-ManChoice==0&&value<cut) 
				return value;
			if(flag-ComChoice==0&&value>cut) 
				return value;
			if(flag-ManChoice==0){
				if(value<min){
					min=value;
				}
			}
			if(flag-ComChoice==0){
				if(value>max){
					max=value;
					if(step==0){
						stepx=i;
						stepy=j;
					}
				}
			}
		}//if
	}//for
	//当前没有步可走
	if(k==0){
		flag=-flag;
		if(search(tb,flag)){
			value=findfirst(tb,step,flag,cut);
			flag=-flag;
			return value;
		}
		else{
			flag=-flag;
			return valuefirst(tb);
		}
	}
	//存在合理步
	else{
		if(flag-ManChoice==0) return min;
		else if(flag-ComChoice==0){
			//if
			return max;
		}//if
	}//else
}

int CBwfind::valuefirst(int tb[][8] )
{
	int flag,minus,corner=0,v,ComMobil,ManMobil,DiffMobil,Num,squre;
	int danger;
	flag=ComChoice;
	ComMobil=Mobility(tb,ComChoice);
	ManMobil=Mobility(tb,ManChoice);
	//DiffMobil=ComMobil*ComMobil-ManMobil*ManMobil;
	//a
	DiffMobil=ComMobil-ManMobil;
	//b
	Num=Total(tb);
	if(flag==1){
		minus=white(tb)-black(tb);
		if(minus>=0) squre=minus*minus;
		else squre=-minus*minus;
		danger=black(tb);
	}
	if(flag==-1){
		minus=black(tb)-white(tb);
		if(minus>=0) squre=minus*minus;
		else squre=-minus*minus;
		danger=white(tb);
	}
	
	if(Num<25){
		v=minus+2*DiffMobil;
	}
	else{
		v=minus+3*DiffMobil;
	}
	if(danger==0) v=-10000;
	return v;
}

int CBwfind::findlast(int tb[][8], int &step, int &flag, int cut)
{
	int value=0,max=-100000,min=100000,k=0,i,j;
	int temp[8][8];
	if(step==64){
		if(ComChoice==1) return(black(tb)-white(tb));
		else return(white(tb)-black(tb));
	}
	for(i=0;i<8;i++)for(j=0;j<8;j++) temp[i][j]=tb[i][j];
	for(i=0;i<8;i++)for(j=0;j<8;j++){
		if(judge(tb,i,j,flag)){
			int ii,jj;
			k=1;//存在合理的步子
			newboard(tb,i,j,flag);
			flag=-flag;
			step++;
			if(-flag==ComChoice){
				value=findlast(tb,step,flag,max);
			}
			if(-flag==ManChoice){
				value=findlast(tb,step,flag,min);
			}
			step--;
			flag=-flag;
			//恢复棋盘
			for(ii=0;ii<8;ii++)for(jj=0;jj<8;jj++) tb[ii][jj]=temp[ii][jj];
			if(flag-ManChoice==0&&value<cut) return value;
			if(flag-ComChoice==0&&value>cut) return value;
			if(flag-ManChoice==0){
				if(value<min){
					min=value;
				}
			}
			if(flag-ComChoice==0){
				if(value>max){
					max=value;
					if(step==CountNum()){
						stepx=i;
						stepy=j;
					}
				}
			}
		}//if
	}//for
	//当前没有步可走
	if(k==0){
		flag=-flag;
		if(search(tb,flag)){
			value=findlast(tb,step,flag,cut);
			flag=-flag;
			return value;
		}
		else{
			flag=-flag;
			if(ComChoice==1) return(black(tb)-white(tb));
			else return(white(tb)-black(tb));
		}
	}
	//存在合理步
	else{
		if(flag-ManChoice==0) return min;
		if(flag-ComChoice==0){
			return max;
		}

	}
}
void CBwfind::newboard(int tb[][8],int chessx, int chessy, int flag)
{
	int x=chessx,y=chessy;
	//左上
	tb[x][y]=flag;
	if(x>=2&&y>=2)
		if(tb[x-1][y-1]+flag==0){
			x=x-2;
			y=y-2;
			while(x>=0&&y>=0){
				if(tb[x][y]==flag){
					for(int i=x,j=y;i!=chessx&&j!=chessy;i++,j++)
						tb[i][j]=flag;
					x=0;y=0;
				}
				else if(tb[x][y]==0){x=-1;y=-1;}
				{x--;y--;}
			}
		}
	//上
	x=chessx;
	y=chessy;
	if(x>=2)
		if(tb[x-1][y]+flag==0){
			x=x-2;
			while(x>=0){
				if(tb[x][y]==flag){
					for(int i=x;i!=chessx;i++)
						tb[i][chessy]=flag;
					x=0;
				} 
				else if(tb[x][y]==0){x=-1;y=-1;}
				x--;
			}
		}
	//右上
	x=chessx;
	y=chessy;
	if(x>=2&&y<=5)
		if(tb[x-1][y+1]+flag==0){
			x=x-2;y=y+2;
			while(x>=0&&y<=7){
				if(tb[x][y]==flag){
					for(int i=x,j=y;i!=chessx&&j!=chessy;i++,j--)
						tb[i][j]=flag;
					x=0;y=7;
				} 
				else if(tb[x][y]==0){x=-1;}
				{x--;y++;}
			}
		}
	//右
	x=chessx;
	y=chessy;
	if(y<=5)
		if(tb[x][y+1]+flag==0){
			y=y+2;
			while(y<=7){
				if(tb[x][y]==flag){
					for(int j=y;j!=chessy;j--)
						tb[chessx][j]=flag;
					y=7;
				}
				else if(tb[x][y]==0){y=8;}
				y++;
			}
		}
	//右下
	x=chessx;
	y=chessy;
	if(x<=5&&y<=5)
		if(tb[x+1][y+1]+flag==0){
			x=x+2;y=y+2;
			while(x<=7&&y<=7){
				if(tb[x][y]==flag){
					for(int i=x,j=y;i!=chessx&&j!=chessy;i--,j--)
						tb[i][j]=flag;
					x=7;y=7;
				}
				
				else if(tb[x][y]==0){x=8;y=8;}
				{x++;y++;}
			}
		}
	//下
	x=chessx;
	y=chessy;
	if(x<=5)
		if(tb[x+1][y]+flag==0){
			x=x+2;
			while(x<=7){
				if(tb[x][y]==flag){
					for(int i=x;i!=chessx;i--)
						tb[i][chessy]=flag;
					x=7;
				}
				else if(tb[x][y]==0){x=8;}
				x++;
			}
		}
	//左下
	x=chessx;
	y=chessy;
	if(x<=5&&y>=2)
		if(tb[x+1][y-1]+flag==0){
			x=x+2;y=y-2;
			while(x<=7&&y>=0){
				if(tb[x][y]==flag){
					for(int i=x,j=y;i!=chessx&&j!=chessy;i--,j++)
						tb[i][j]=flag;
					x=7;y=0;
				}
				else if(tb[x][y]==0){y=-1;}
				{x++;y--;}
			}
		}
	//左
	x=chessx;
	y=chessy;
	if(y>=2)
		if(tb[x][y-1]+flag==0){
			y=y-2;
			while(y>=0){
				if(tb[x][y]==flag){
					for(int j=y;j!=chessy;j++)
						tb[chessx][j]=flag;
					y=0;
				}
				else if(tb[x][y]==0){y=-1;}
				y--;
			}
		}
}



void CBwfind::CornerSense(int tb[][8], int &value)
{	
	int flag,corner=0;
	//int i,j;
	flag=ComChoice;
	
	if(tb[0][0]-flag!=0){
		if((tb[1][0]-flag==0)||(tb[1][1]-flag==0)||(tb[0][1]-flag==0))
			corner-=1000;
	}
	else if(tb[0][0]==flag)corner+=1000;
	if(tb[0][7]-flag!=0){
		if((tb[0][6]-flag==0)||(tb[1][7]-flag==0)||(tb[1][6]-flag==0))
			corner-=1000;
	}
	else if(tb[0][0]==flag)corner+=1000;
	if(tb[7][0]-flag!=0){
		if((tb[6][0]-flag==0)||(tb[7][1]-flag==0)||(tb[6][1]-flag==0))
			corner-=1000;
	}
	else if(tb[0][0]==flag)corner+=1000;
	if(tb[7][7]-flag!=0){
		if((tb[7][6]-flag==0)||(tb[6][7]-flag==0)||(tb[6][6]-flag==0))
			corner-=1000;
	}
	else if(tb[0][0]==flag)corner+=1000;
	value+=corner;
}





int CBwfind::Mobility(int tb[][8], int flag)
{
	int move=0,i,j;
	for(i=0;i<8;i++)for(j=0;j<8;j++){
		if(judge(tb,i,j,flag)) move++;
	}
	return move;
}

void CBwfind::LineSense(int tb[][8], int chessx, int chessy, int &value)
{
	int line=0;
	int i,j;
	if(tb[0][0]==ManChoice){
		if(chessx==0){
			j=0;
			while(tb[0][j]==ManChoice) j++;
			if(tb[0][j]==ComChoice){
				while(j<8&&tb[0][j]==ComChoice) j++;
				if(j<8&&tb[0][j]==0) line-=1000;
			}
		}
		if(chessy=0){
			i=0;
			while(tb[i][0]==ManChoice) i++;
			if(tb[i][0]==ComChoice){
				while(i<8&&tb[i][0]==ComChoice) i++;
				if(i<8&&tb[i][0]==0) line-=1000;
			}
		}
	}
	if(tb[0][7]==ManChoice){
		if(chessx==0){
			j=7;
			while(tb[0][j]==ManChoice) j--;
			if(tb[0][j]==ComChoice){
				while(j>=0&&tb[0][j]==ComChoice) j--;
				if(j>=0&&tb[0][j]==0) line-=1000;
			}
		}
		if(chessy=7){
			i=0;
			while(tb[i][7]==ManChoice) i++;
			if(tb[i][7]==ComChoice){
				while(i<8&&tb[i][7]==ComChoice) i++;
				if(i<8&&tb[i][7]==0) line-=1000;
			}
		}
	}
	if(tb[7][0]==ManChoice){
		if(chessx==7){
			j=0;
			while(tb[0][j]==ManChoice) j++;
			if(tb[0][j]==ComChoice){
				while(j<8&&tb[0][j]==ComChoice) j++;
				if(j<8&&tb[0][j]==0) line-=1000;
			}
		}
		if(chessy=0){
			i=7;
			while(tb[i][0]==ManChoice) i--;
			if(tb[i][0]==ComChoice){
				while(i>=0&&tb[i][0]==ComChoice) i--;
				if(i>=0&&tb[i][0]==0) line-=1000;
			}
		}
	}
	if(tb[7][7]==ManChoice){
		if(chessx==7){
			j=7;
			while(tb[0][j]==ManChoice) j--;
			if(tb[0][j]==ComChoice){
				while(j>=0&&tb[7][j]==ComChoice) j--;
				if(j>=0&&tb[7][j]==0) line-=1000;
			}
		}
		if(chessy=7){
			i=7;
			while(tb[i][7]==ManChoice) i--;
			if(tb[i][7]==ComChoice){
				while(i<8&&tb[i][7]==ComChoice) i--;
				if(i>=0&&tb[i][7]==0) line-=1000;
			}
		}
	}
	value+=line;

}

void CBwfind::SaveBoard(int tb[][8])
{
	int i,j;
	bak++;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++) 
			save[bak][i][j]=tb[i][j];
}


void CBwfind::Corner(int tb[][8], int chessx, int chessy, int &value)
{
	int flag=ComChoice;
	int corner=0;
	int i=chessx,j=chessy;
	if(i==0&&j==0&&tb[0][0]==flag) value+=2000;//return;
	if(i==0&&j==7&&tb[0][7]==flag) value+=2000;//return;
	if(i==7&&j==0&&tb[7][0]==flag) value+=2000;//return;
	if(i==7&&j==7&&tb[7][7]==flag) value+=2000;//return;
	if(tb[0][0]==0){
		//if(i==0&&tb[0][1]==flag){
		if(tb[0][1]==flag){
			j=1;
			while(j<8&&tb[0][j]==flag) j++;
			if(j<8&&tb[0][j]==-flag) value-=5000;
		}
		//if(j==0&&tb[1][0]==flag){
		if(tb[1][0]==flag){
			i=1;
			while(i<8&&tb[i][0]==flag) i++;
			if(i<8&&tb[i][0]==-flag) value-=5000;
		}
	}
	i=chessx;j=chessy;
	if(tb[0][7]==0){
		//if(i==0&&tb[0][6]==flag){
		if(tb[0][6]==flag){
			j=6;
			while(j>=0&&tb[0][j]==flag) j--;
			if(j>=0&&tb[0][j]==-flag) value-=5000;
		}
		//if(j==7&&tb[1][7]==flag){
		if(tb[1][7]==flag){
			i=1;
			while(i<8&&tb[i][7]==flag) i++;
			if(i<8&&tb[i][7]==-flag) value-=5000;
		}
	}
	i=chessx;j=chessy;
	if(tb[7][0]==0){
		//if(i==7&&tb[7][1]==flag){
		if(tb[7][1]==flag){
			j=1;
			while(j<8&&tb[7][j]==flag) j++;
			if(j<8&&tb[7][j]==-flag) value-=5000;
		}
		//if(j==0&&tb[6][0]==flag){
		if(tb[6][0]==flag){
			i=6;
			while(i>=0&&tb[i][0]==flag) i--;
			if(i>=0&&tb[i][0]==-flag) value-=5000;
		}
	}
	i=chessx;j=chessy;
	if(tb[7][7]==0){
		//if(i==7&&tb[7][6]==flag){
		if(tb[7][6]==flag){
			j=6;
			while(j>=0&&tb[7][j]==flag) j--;
			if(j>=0&&tb[7][j]==-flag) value-=5000;
		}
		//if(j==7&&tb[6][7]==flag){
		if(tb[6][7]==flag){
			i=6;
			while(i>=0&&tb[i][7]==flag) i--;
			if(i>=0&&tb[i][7]==-flag) value-=5000;
		}
	}
	//
	i=chessx;j=chessy;
	if(i==1&&j==1&&tb[0][0]-flag!=0&&tb[i][j]==flag)
		value-=2000;
	if(i==1&&j==6&&tb[0][7]-flag!=0&&tb[i][j]==flag)
		value-=2000;
	if(i==6&&j==1&&tb[7][0]-flag!=0&&tb[i][j]==flag)
		value-=2000;
	if(i==6&&j==6&&tb[7][7]-flag!=0&&tb[i][j]==flag)
		value-=2000;
}

int main()
{
	CBwfind m_find;
	m_find.depth=6;
	m_find.preview=false;
	m_find.bak=0;

	m_find.ComChoice=BLACK;
	m_find.ManChoice=WHITE;
	int ComChoice = BLACK;
	int ManChoice=WHITE;;

	int tb[8][8];
	int i,j;
	for(i=0;i<8;i++)
		for( j=0;j<8;j++)
			scanf("%d",&tb[i][j]);
	for(i=0;i<8;i++)
		for(j=0;j<8;j++) 
			if(tb[i][j] == 2)
			{
				m_find.board[i][j] = -1;
				tb[i][j] = -1;
			}
			else
				m_find.board[i][j] = tb[i][j];
	int x,y;
	if(m_find.search(tb, ComChoice))
	{
		m_find.select(ComChoice);
		x=m_find.stepx;
		y=m_find.stepy;
		m_find.newboard(tb,x,y,ComChoice);

	}
	printf("%d %d",x,y);
	return 0;
}
