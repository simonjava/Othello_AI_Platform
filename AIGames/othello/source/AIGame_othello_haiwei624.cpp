		
		#include <stdio.h>

int t,tmpt, x, y,ans =0;

int f[ 10][ 10 ], g[ 10 ][ 10 ];
int tx [ 8 ]= { -1,-1,-1,0,0,1,1,1};
int ty [ 8 ]= { -1,0,1,-1,1,-1,0,1};

int jd ( int a, int b ) {
    int i, j ;
    for (i=0;i<8;i++) if (g[ a+tx[i] ][ b+ty[i] ]==2) 
        for (j=2;a+tx[i]*j>=0&&a+tx[i]*j<8&&b+ty[i]*j>=0&&b+ty[i]*j<8;j++) {
            if (g[a+tx[i]*j][b+ty[i]*j]==1) return 1;
            if (g[a+tx[i]*j][b+ty[i]*j]==0) break;
        }
    return 0;
}

void  count ( int i, int j ) {
      if ((i==0||i==7)&&(j==0||j==7)) tmpt+=10;
      if ((i==1&&j==1)||(i==6&&j==6)||(i==1&&j==6)||(i==6&&j==1)) tmpt-=6;
}
        
int deal ( int a, int b ) {
    int i, j, k, t=0;
    for (i=0;i<8;i++)
    for (j=0;j<8;j++) f[i][j]=g[ i][j ]; 
    for (i=0;i<8;i++) if (f[ a+tx[i] ][ b+ty[i] ]==2) 
        for (j=2;a+tx[i]*j>=0&&a+tx[i]*j<8&&b+ty[i]*j>=0&&b+ty[i]*j<8;j++) {
            if (f[a+tx[i]*j][b+ty[i]*j]==1) for (k=0;k<j;k++) {
               f[a+tx[i]*k][b+ty[i]*k]=1;
               count( a+tx[i]*k, b+ty[i]*k ) ;
            }
            if (f[a+tx[i]*j][b+ty[i]*j]!=2) break;
        }
    for (i=0;i<8;i++)
    for (j=0;j<8;j++) if (f[ i][j ]==1) ++t; 
    return t+tmpt ;
}
            

int main () {
    int i, j;
    for (i=0;i<8;i++)
    for (j=0;j<8;j++) scanf("%d",&g[i][j]);
    for (i=0;i<8;i++)
    for (j=0;j<8;j++) if ((!g[i][j])&&jd (i, j) ) {
        t= deal ( i, j) ;
        //if ((i==0||i==7)&&(j==0||j==7)) t-=10;
        //if ((i==1&&j==1)||(i==6&&j==6)||(i==1&&j==6)||(i==6&&j==1)) t-=6;
        if (ans <=t ) {x=i;y=j;ans=t;}
    }
    printf("%d %d\n",x,y);
    //while (1 );
    return 0;
}
