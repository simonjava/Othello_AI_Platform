#include<cstring>
#include<ctime>
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

#define FOR(i,begin,end) for(int i(begin); i != end; ++i)

bool inside(const int &x, const int &y)
{
	return -1 < x && x < 8 && -1 < y && y < 8;
}

bool legalDirect(const int board[][8], int x, int y, const int &dx, const int &dy, const int &color)
{
	const int minus(3 - color);
	x += dx;
	y += dy;
	bool cover(false);
	while(inside(x, y) && board[x][y] == minus)
		x += dx, y += dy, cover = true;
	return cover && inside(x, y) && board[x][y] == color;
}

bool legal(int board[][8], int x, int y, const int &color)
{
	if(board[x][y])
		return false;
	FOR(dx, -1, 2) FOR(dy, -1, 2)
		if((dx || dy) && legalDirect(board, x, y, dx, dy, color))
			return true;
	return false;
}

struct point
{
	int x, y;
		point(int xx = -1, int yy = -1)
		{
			x = xx;
			y = yy;
		}
		void output() const
		{
			cout<<x<<' '<<y<<endl;
		}
		
};

struct ans
{
	int level;
	long long tot, num;
	long long inf;
	
	ans(int lev = 0, long long t = 0, long long n = 0, long long i = 0)
	{
		level = lev;
		tot = t;
		num = n;
		inf = i;
	}
	
	bool operator<(const ans &x) const
	{/*
		if(!level && x.level)
			return true;
		const long long me(tot * x.level), that(x.tot * level);
		return me == that ? level == x.level ? num < x.num : level < x.level : me < that;*/
		//return level == x.level ? inf < x.inf : level < x.level;
		//return inf == x.inf ? x.level < level : inf < x.inf;
		return (level && x.level) ? x.inf < inf : level < x.level;
	}
};

struct state
{
	point trace;
	bool first;
	int level;
	
		int data[8][8];
		state(int a[8][8])
		{
			level = 0;
			first = true;
			memcpy(data, a, sizeof(int) << 6);
		}
		void paint(int x, int y, const int &color)
		{
			if(first)
			{
				first = false;
				trace = point(x, y);
			}
			++level;
			data[x][y] = color;
			const int minus(3 - color);
			FOR(dx,-1,2) FOR(dy,-1,2)
				if((dx || dy) && legalDirect(data, x, y, dx, dy, color))
				{
					int xt(x + dx), yt(y + dy);
					while(data[xt][yt] == minus)
					{
						data[xt][yt] = color;
						xt += dx;
						yt += dy;
					}
				}
		}
		bool operator<(const state &x) const
		{
			return x.count() < count();
		}
		int turn() const
		{
			return (level & 1) ? 2 : 1;
		}
		void output() const
		{
			trace.output();
		}
		long long count() const
		{
			long long ans(0);
			FOR(i, 0, 8) FOR(j, 0, 8)
				//if(data[i][j] == 1)
				if(data[i][j] == 2)
				{
					++ans;
					if(i == 0 || i == 7 || j == 0 || j == 7)
						ans += 50;
				}
			//if(data[0][0] == 1)
			if(data[0][0] == 2)
				ans += 1000;
			//if(data[0][7] == 1)
			if(data[0][7] == 2)
				ans += 1000;
			//if(data[7][0] == 1)
			if(data[7][0] == 2)
				ans += 1000;
			//if(data[7][7] == 1)
			if(data[7][7] == 2)
				ans += 1000;
			return ans;
		}
		void edit(ans a[][8]) const
		{
			ans &curr(a[trace.x][trace.y]);
			/*
			if(curr.level == level)
			{
				curr.tot += count();
				++curr.num;
			}
			else
			{
				curr.level = level;
				curr.num = 1;
				curr.tot = count();
			}
			*/
			/*
			if(curr.level < level)
			{
				curr.level = level;
				curr.inf = count();
			}
			else
				//curr.inf = min(curr.inf, count());
				curr.inf = max(curr.inf, count());
			*/
			curr.level = level;
			curr.inf = max(curr.inf, count());
		}
};

int main()
{
	int board[8][8];
	
	ios::sync_with_stdio(false);
	FOR(i, 0, 8) FOR(j, 0, 8)
		cin>>board[i][j];
	
	queue<state>q;
	q.push(state(board));
	
	const long time_limit((CLOCKS_PER_SEC << 3) / 10);
	
	ans a[8][8];

	while(clock() < time_limit && !q.empty())
	{
		state fuck(q.front());
		const int color(fuck.turn());
		q.pop();
		memcpy(board, fuck.data, sizeof(int) << 6);
		FOR(i, 0, 8) FOR(j, 0, 8)
			if(legal(board, i, j, color))
			{
				state temp = fuck;
				temp.paint(i, j, color);
				temp.edit(a);
				q.push(temp);
			}
	}
	
	int x(0), y(0);
	ans best(0, 0, 0, 0);
	FOR(i, 0, 8) FOR(j, 0, 8)
		if(best < a[i][j])
		{
			x = i;
			y = j;
			best = a[i][j];
		}
	cout<<x<<' '<<y<<endl;
}