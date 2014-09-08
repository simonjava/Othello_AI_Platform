#include<stdio.h>
int best_row,best_col;
void make_move(int board[8][8],int row,int col)
{
     int rowde=0,colde=0;
     int x=0,y=0;
     board[row][col]=1;
     for(rowde=-1;rowde<=1;rowde++)
        for(colde=-1;colde<=1;colde++)
         {
             if(row+rowde<0||row+rowde>=8||col+colde<0||col+colde>=8||(rowde==0&&colde==0))
             continue;
             if(board[row+rowde][col+colde]==2)
              {
               x=row+rowde,y=col+colde;
               for(;;)
               {
                 x+=rowde;
                 y+=colde;
                 if(x<0||x>=8||y<0||y>=8)
                  break;
                if(board[x][y]==0)
                break;
                if(board[x][y]==1)
                {
                  while(board[x-=rowde][y-=colde]==2)
                         board[x][y]=1;
                       break;
                }
               }
              }
             }
}
int get_score(int board[8][8])
{
    int score=0,row=0,col=0;
    for(row=0;row<8;row++)
       for(col=0;col<8;col++)
             score+=board[row][col]==1;
          return score;
}
 int valid_moves(int board[8][8],int moves[8][8])
{
    int rowde=0,colde=0;
    int row=0,col=0;
    int x=0,y=0;
    int no_of_moves=0;
    for(row=0;row<8;row++)
       for(col=0;col<8;col++)
         moves[row][col]=0;
    for(row=0;row<8;row++)
       for(col=0;col<8;col++)
          {
            if(board[row][col]!=0)
               continue;
    for(rowde=-1;rowde<=1;++rowde)
       for(colde=-1;colde<=1;++colde)
          {
             if(row+rowde<0||row+rowde>=8||col+colde<0||col+colde>=8||(rowde==0&&colde==0))
             continue;
    if(board[row+rowde][col+colde]==2)
       {
         x=row+rowde,y=col+colde;
         for(;;)
         {
                x+=rowde;
                y+=colde;
                if(x<0||x>=8||y<0||y>=8)
                  break;
                if(board[x][y]==0)
                break;
                if(board[x][y]==1)
                  {
                    moves[row][col]=1;
                    no_of_moves++;
                    break;
                  }
         }
       }
         }
    }
    return no_of_moves;
}    
int best_move(int board[8][8],int moves[8][8])
{
    int row=0,col=0,i=0,j=0;
    int new_board[8][8]={0};
    int score=0,new_score=0;
    for(row=0;row<8;row++)
       for(col=0;col<8;col++)
          {
             if(!moves[row][col])
             continue;
             for(i=0;i<8;i++)
                for(j=0;j<8;j++)
                   new_board[i][j]=board[i][j];
                   make_move(new_board,row,col);
             new_score=get_score(new_board);
             if(score<new_score)
             {
                score=new_score;
                best_row=row;
                best_col=col;
             }
          }
          return score;
}   
 main()
{
       int i,j,row,col,s;
       int a[8][8],vmoves[8][8];
       for(i=0;i<8;i++)
          for(j=0;j<8;j++)
       scanf("%d",&a[i][j]);
       for(i=0;i<8;i++)
          for(j=0;j<8;j++)
          vmoves[i][j]=0;
       valid_moves(a,vmoves);//将有效移动保存到vmove 
       s=best_move(a,vmoves);
       printf("%d %d\n",best_row,best_col);
}
    