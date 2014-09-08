#include <stdio.h>
#include <stdlib.h>
//#include <sys/time.h>
#define OPPOSITE(x) ((~x) & 3)
#define VALID_CELL(x,y) ((x > -1) && (x < 8) && (y > -1) && (y < 8))
int weight[8][8] =
  { {512,   4, 128, 256, 256, 128,   4, 512},
    {  4,   2,   8,  16,  16,   8,   2,   4},
    {128,   8,  64,  32,  32,  64,   8, 128},
    {256,  16,  32,   2,   2,  32,  16, 256},
    {256,  16,  32,   2,   2,  32,  16, 256},
    {128,   8,  64,  32,  32,  64,   8, 128},
    {  4,   2,   8,  16,  16,   8,   2,   4},
    {512,   4, 128, 256, 256, 128,   4, 512}
  };
int moves_x[1830];
int moves_y[1830];
int moves_next = 0;
int moves_stack_block[60];
int moves_stack_next = 0;
int flips_x[1520];
int flips_y[1520];
int flips_next = 0;
int flips_stack_block[60];
int flips_stack_who[60];
int flips_stack_next = 0;
int board[8][8], best_x, best_y;
int empties(void);
void get_all(int);
void get_move(int, int);
int legalDirect(int, int, int, int, int, int);
int legal(int, int, int);
void make_move(int, int, int);
void undo_move(void);
void unget_all(void);
int weigh_move(int, int, int, int, int);
int main()
{
	int i, j;
	for (i = 0; i < 8; ++i)
		for (j = 0; j < 8; ++j)
		scanf("%d", &board[i][j]);
    get_move(1, 6); /*调用AI，得到我的结果，‘1’表示是‘我’走这步，‘5’表示我的搜索深度是5*/
    printf("%d %d\n", best_x, best_y);
    return 1;
}

/*
**获取某人的所有可能步法，并储存
*/
void get_all(int who)
{
	int i, j;
	moves_stack_block[moves_stack_next] = 0;
	for(i = 0; i < 8; i++)
		for(j = 0; j < 8; j++)
			if(legal(i, j, who))
			{
				moves_x[moves_next] = i;
				moves_y[moves_next] = j;
				moves_next++;
				moves_stack_block[moves_stack_next]++;
			}
	moves_stack_next++;
}

/*
**回溯
*/
void unget_all(void)
{
	moves_next -= moves_stack_block[--moves_stack_next];
}

int legalDirect(int x, int y, int xoffest, int yoffset, int flag, int who)
{
    int oppo = OPPOSITE(who);
	x += xoffest;
	y += yoffset;
	if (x < 0 || x >= 8 || y < 0 || y >= 8)// 超出棋盘范围
	{
		return 0;
	}
	if (board[x][y] == oppo)
	{
		/* (x,y)某个方向的有相邻的对手棋子,继续检查这个方向是否
		*  可以吃对方子,递归调用
		*/
		flag = 1;
		return legalDirect(x, y, xoffest, yoffset, flag, who);
	}
	else if (board[x][y] == who)
	{
		/* 遇到自己的棋子,判断这个方向之前的棋子是否全为反方的即 legal=1*/
		return flag;
	}
	else
		return 0;
	return 0;
}
/*
**判断是否合法，改编自示例代码，增加了对不同人的处理
*/
int legal(int x, int y, int who)
{
	if (board[x][y]!=0)
		return 0;
	int i, j, flag;
	/* 检测(x,y)坐标点八个方向*/
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)// (x,y)点忽略
			{
				continue;
			}
			flag = 0;
			if (legalDirect(x, y, i, j, flag, who))
			{
				return 1;
			}
		}
	}
	return 0;
}

/*
**走这一步
*/
void make_move(int x, int y, int who)
{
  int dx, dy, i, j, opp = OPPOSITE(who);
  board[x][y] = who;
  flips_x[flips_next] = x;
  flips_y[flips_next] = y;
  flips_next++;
  flips_stack_block[flips_stack_next] = 1;
  flips_stack_who[flips_stack_next] = who;
  for(dx = -1; dx < 2; dx++)
    for(dy = -1; dy < 2; dy++)
    {
      i = x + dx;
      j = y + dy;
      /* branch in each direction */
      if((dx || dy) && VALID_CELL(i, j) && board[i][j] == opp)
      {
        do
        {
          i += dx;
          j += dy;
        }
        while(VALID_CELL(i, j) && (board[i][j] == opp));
        /* if this direction is to be flipped */
        if(VALID_CELL(i, j) && (board[i][j] == who))
        {
          i -= dx;
          j -= dy;
          /* go back and flip each piece */
          while(board[i][j] == opp)
          {
            board[i][j] = who;
            flips_x[flips_next] = i;
            flips_y[flips_next] = j;
            flips_next++;
            flips_stack_block[flips_stack_next]++;
            i -= dx;
            j -= dy;
          };
        }
      }
	}
	flips_stack_next++;
}

/*
**AI的核心，得到当前走法的权重
*/
int weigh_move(int x, int y, int who, int max_depth, int add)
{
	int bottom, top, i, move_weight = 0, depth_weight = 0, temp;
	bottom = flips_next;
	make_move(x, y, who);
	top = flips_next;
	for (i = bottom; i < top; ++i)
		move_weight += (add ? 1 : (-1)) * weight[flips_x[i]][flips_y[i]];
	if (max_depth && empties())
	{
		who = OPPOSITE(who);
		add = !add;
		bottom = moves_next;
		get_all(who);
		top = moves_next;
		for(i = bottom; i < top; ++i)
		{
			temp = weigh_move(moves_x[i], moves_y[i], who, max_depth - 1, add);
			if(temp < depth_weight)
				depth_weight = temp;
		}
		unget_all();
    }
    undo_move();
    return move_weight + depth_weight;
}

void undo_move(void)
{
	int i, who, top = flips_next;
	flips_next -= flips_stack_block[--flips_stack_next];
	board[flips_x[flips_next]][flips_y[flips_next]] = 0;
	who = OPPOSITE(flips_stack_who[flips_stack_next]);
	for(i = flips_next + 1; i < top; i++)
		board[flips_x[i]][flips_y[i]] = who;
}
/*
**计算当前空白个数
*/
int empties(void)
{
    int i, j, blocks = 64;
    for (i = 0; i < 8; ++i)
        for (j = 0; j < 8; ++j)
            if (board[i][j]) --blocks;
    return blocks;
}

/*
**AI的入口，得到最终最优解
*/
void get_move(int who, int deep)
{
    int bottom, top, i, move_weight, best_weight;
    if (!empties()) return;
    if ((empties() < 11) && deep) deep = 13; /*快结束时加大搜索力度*/
    bottom = moves_next; /*起点*/
    get_all(who); /*得到当前所有可能步骤*/
    top = moves_next; /*终点*/
    if (bottom == top)
	{
		unget_all();
		return;
	}
    /*初始化各值*/
    best_x = moves_x[bottom];
    best_y = moves_y[bottom];
    best_weight = weigh_move(best_x, best_y, who, deep, 1);
    /*
    **初始化结束
    **开始测试各值
    */
    for (i = bottom + 1; i < top; ++i)
	{
		move_weight = weigh_move(moves_x[i], moves_y[i], who, deep, 1);
		if (move_weight > best_weight || ((move_weight == best_weight) && rand() % 2)) /*如果找到更优解*/
		{
			best_x = moves_x[i];
			best_y = moves_y[i];
			best_weight = move_weight;
		}
	}
	unget_all();
}
