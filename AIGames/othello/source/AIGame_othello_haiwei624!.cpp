#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define MST(a,b) memset(a,b,sizeof(a))
#define MAXN 10
int fx[8]={-1,0,1,1,1,0,-1,-1};
int fy[8]={1,1,1,0,-1,-1,-1,0};
int g0[MAXN][MAXN];
int val[8][8]={
{40,-5,4,2,2,4,-5,40},
{-5,-10,-1,-1,-1,-1,-10,-5},
{4,-1,2,2,2,2,-1,4},
{2,-1,2,1,1,2,-1,2},
{2,-1,2,1,1,2,-1,2},
{4,-1,2,2,2,2,-1,4},
{-5,-10,-1,-1,-1,-1,-10,-5},
{40,-5,4,2,2,4,-5,40}
};
int timelimit;
int tots;
void init()
{
    FOR(i,0,7)FOR(j,0,7)scanf("%d",&g0[i][j]);
    tots=0;
    FOR(i,0,7)FOR(j,0,7)if(g0[i][j])tots++;
    timelimit=8;
    if(tots<=54)timelimit=6;
    if(tots<=40)timelimit=4;
}

int dfs(int k,int g0[MAXN][MAXN],int &ansi,int &ansj)
{
    if(k==timelimit+1)
    {
        int ans=0;
        FOR(i,0,7)FOR(j,0,7)
        {
            if(g0[i][j]==1)ans+=1;
            if(g0[i][j]==2)ans-=1;
        }
        return ans;
    }
    /*printf("%d:\n",k);
    FOR(i,0,7)
    {
        FOR(j,0,7)printf("%d ",g0[i][j]);
        printf("\n");
    }*/
    int maxS=-2000,maxi=0,maxj=0;
    int tried=0;
    FOR(x,0,7)FOR(y,0,7)
    if(g0[x][y]==0)
    {
        int g[MAXN][MAXN];
        FOR(i,0,7)FOR(j,0,7)g[i][j]=g0[i][j];
        g[x][y]=1;
        int legal=0;
        int tot,stx[MAXN],sty[MAXN];
        FOR(p,0,7)
        {
            int xt=x+fx[p],yt=y+fy[p];
            tot=0;
            while( xt>=0 && yt>=0 && xt<=7 && yt<=7 && g[xt][yt]==2)
            {
                tot++;
                stx[tot]=xt;
                sty[tot]=yt;
                xt=xt+fx[p];
                yt=yt+fy[p];
            }
            if(xt>=0 && yt>=0 && xt<=7 && yt<=7 && g[xt][yt]==1 && tot>0)
            {
                legal=1;
                FOR(i,1,tot)g[stx[i]][sty[i]]=1;
            }
        }
        if(legal==0)continue;
        tried=1;
        if(k<timelimit)
        {
            int ans,t1,t2;
            FOR(i,0,7)FOR(j,0,7)
            {
                if(g[i][j]==1)g[i][j]=2;
                else if(g[i][j]==2)g[i][j]=1;
            }
            ans=-dfs(k+1,g,t1,t2);
            if(ans>=maxS)
            {
                maxS=ans;
                maxi=x;
                maxj=y;
            }
        }
        if(k==timelimit)
        {
            int ans=0;
            FOR(i,0,7)FOR(j,0,7)
            {
                if(g[i][j]==1)ans+=val[i][j];
                if(g[i][j]==2)ans-=val[i][j];
            }
            if(ans>=maxS)
            {
                if((rand()*rand())%(64*64*64)<=64*64*64-(64-tots)*(64-tots)*(64-tots) || maxS==-2000){
                maxS=ans;
                maxi=x;
                maxj=y;}
            }
        }
    }

    ansi=maxi;
    ansj=maxj;
    if(tried==0)
    {
        int g[MAXN][MAXN];
        FOR(i,0,7)FOR(j,0,7)
        {
            if(g0[i][j]==1)g[i][j]=2;
                else if(g0[i][j]==2)g[i][j]=1;
                else g[i][j]=0;
            }
        maxS=-dfs(k+1,g,ansi,ansj);
    }
    //printf("%d %d %d %d\n",k,maxS,ansi,ansj);
    return maxS;
}
void work()
{
    int ansi,ansj;
    dfs(1,g0,ansi,ansj);
    printf("%d %d\n",ansi,ansj);
}
int main()
{

    init();
    work();
}
