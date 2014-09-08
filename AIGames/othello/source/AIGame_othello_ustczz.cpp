#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int board[8][8]={0};
int store[64][2];
int score[8][8]={{50,10,30,30,30,30,10,50},
				{10,15,20,20,20,20,15,10},
                {30,20,45,40,40,45,20,30},
                {30,20,40,45,45,40,20,30},
                {30,20,40,45,45,40,20,30},
                {30,20,45,40,40,45,20,30},
                {10,15,20,20,20,20,15,10},
                {50,10,30,30,30,30,10,50}};

int legalDirect(int x,int y,int xoffest,int yoffset,int flag){
	x+=xoffest;
	y+=yoffset;
	if(x<0||x>=8||y<0||y>=8){
		return 0;
	}
	if(board[x][y]==2){
		flag=1;
		return legalDirect(x,y,xoffest,yoffset,flag);
	}
	else if (board[x][y] == 1){
		if(flag==1){
			return 1;
		}
		return 0;
	}
	else
		return 0;
	return 0;
}

int legal(int x, int y){
	if(board[x][y]!=0)
		return 0;
	int i,j,flag;
	for(i=-1;i<=1;i++){
		for(j=-1;j<=1;j++){
			if(i==0&&j==0){
				continue;
			}
			flag=0;
			if(legalDirect(x,y,i,j,flag)){
				return 1;
			}
		}
	}
	return 0;
}

int main(){
	int i=0,j=0,k=0,temp=0;
	int temp2;
	//freopen("test.txt","r",stdin );
	memset(store,99,sizeof(store));
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			scanf("%d",&board[i][j]);
		}
	}
	if(board[0][0]==1){board[0][1]=30;board[1][0]=30;board[1][1]=35;}
	if(board[0][7]==1){board[0][6]=30;board[1][6]=35;board[1][7]=30;}
	if(board[7][0]==1){board[7][1]=30;board[6][0]=30;board[6][1]=35;}
	if(board[7][7]==1){board[7][6]=30;board[6][7]=30;board[6][6]=35;}
	for(j=0;j<8;j++){
		for(i=0;i<8;i++){
            //printf("i=%d j=%d \n",i,j);
			if(temp2=legal(i,j)){
                //printf("i=%d j=%d temp2=\n",i,j,temp2);
				store[k][0]=i*10+j;
				store[k][1]=score[i][j];
				k++;
			}
		}
	}
	for(i=0,j=0;i<k;i++){
        //printf("%d %d\n",store[i][0],store[i][1]);
		if(store[i][1]>j){
			temp=store[i][0];
			j=store[i][1];
		}
	}
	printf("%d %d\n",temp/10,temp%10);
	return 0;
}











