#include<cmath>
#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

int a[8][8], d[3][3] = {0, 1, 2, 3, -1, 4, 5, 6, 7};

struct point 
{
		int x, y;
		int eat;
		int s;
}p[8][8];

int direct(int x, int y, int xx, int yy, int flag)
{
		x += xx;
		y += yy;
		if (x < 0 || x > 7 || y < 0 || y > 7)
				return -10;
		else if (a[x][y] == 2)
		{
				flag = 1;
				return 1 + direct(x, y, xx, yy, flag);
		}
		else if (a[x][y] == 1)
		{
				if (flag)
						return 1;
				return -10;
		}
		return -10;
}

int check (int p, int q)
{
		int i, j, x = 0, y = 0, flag = 0;

		if (a[p][q])
				return 0;
		else
		{
				for (i = -1; i <= 1; ++i)
						for (j = -1; j <= 1; ++j)
						{
								if (j == 0 && i == 0)
										continue;
								flag = 0;
								if (direct(p, q, i, j, flag) > 0)
										y += (1 << d[i + 1][j + 1]);
						}
				return y;
		}
}

int next(int p, int q, int tem)
{
		int b[8][8], c[8][8], i, j, k, s, t;

		for (i = 0; i < 8; ++i)
				for (j = 0; j < 8; ++j)
						b[i][j] = a[i][j];
		b[p][q] = 1;
		for (k = 0; k < 8; ++k)
		{
				if (tem & (1 << k))
				{
						for (i = 0; i < 3; ++i)
						{
								for (j = 0; j < 3; ++j)
										if (d[i][j] == k)
												break;
								if (j != 3)
										break;
						}
						s = p + i - 1;
						t = q + j - 1;
						while (b[s][t] != 1)
						{
								b[s][t] = 1;
								s += i - 1;
								t += j - 1;
						}
				}							
		}
		for (i = 0; i < 8; ++i)
				for (j = 0; j < 8; ++j)
				{
						if (b[i][j] == 1)
								b[i][j] = 2;
						else if (b[i][j] == 2)
								b[i][j] = 1;
				}
		for (i = 0; i < 8; ++i)
				for (j = 0; j < 8; ++j)
				{
						c[i][j] = a[i][j];
						a[i][j] = b[i][j];
				}
		if (check(0, 0) || check(0, 7) || check(7, 0) || check(7, 7))
		{
				for (i = 0; i < 8; ++i)
						for (j = 0; j < 8; ++j)
								a[i][j] = c[i][j];
				return -10;
		}
		else
		{
				for (i = 0; i < 8; ++i)
						for (j = 0; j < 8; ++j)
								a[i][j] = c[i][j];
				return 1;
		}
}

int cmp1(const void *p, const void *q)
{
		point *s, *t;
		s = (point *)p;
		t = (point *)q;
		if (s -> s == t -> s)
				return t -> eat - s -> eat;
		else
				return t -> s - s -> s;
}

int cmp2(const void *p, const void *q)
{
		point *s, *t;
		s = (point *)p;
		t = (point *)q;
		return t -> eat - s -> eat;
}


int main()
{
		int i, j, k, ii, jj, tem, t = 0, sum = 0;     /*tem 用于保存check返回值，t 用于保存与运算tem的某一二进制位后方向上的对方棋子数*/

		for (i = 0;i < 8; ++i)
				for (j = 0; j < 8; ++j)
				{
						cin >> a[i][j];
						p[i][j].x = i;
						p[i][j].y = j;
						p[i][j].eat = 0;
						p[i][j].s = -100;
				}
		p[1][0].eat = p[0][1].eat = p[1][1].eat = p[1][7].eat = p[0][6].eat = p[1][6].eat = p[7][1].eat = p[6][0].eat = p[6][1].eat = p[6][6].eat = p[6][7].eat = p[7][6].eat = -15;
		sum = check(0, 0) ? 1 : 0 + check(7, 7) ? 1 : 0 + check(7, 0) ? 1 : 0 + check(0, 7) ? 1 : 0;
		if (sum < 2)
		{
				if (check(0, 0))
						cout << 0 << ' ' << 0 << endl;
				else if (check(7, 0))
						cout << 7  << ' ' << 0 << endl;
				else if (check(0, 7))
						cout << 0 << ' ' << 7 << endl;
				else if (check(7, 7))
						cout << 7 << ' ' << 7 << endl;
				else
				{
						for (i = 0; i < 8; ++i)
						{
								for (j = 0; j < 8; ++j)
								{
										t = 0;
										tem = check(i, j);
										if (tem)
										{
												for (k = 0; k < 8; ++k)
												{
														if (tem & (1 << k))
														{
																for (ii = 0; ii < 3; ++ii)
																{
																		for (jj = 0; jj < 3; ++jj)
																				if (d[ii][jj] == k)
																						break;
																		if (jj != 3)
																				break;
																}
																t += direct(i, j, ii - 1, jj - 1, 0);														
														}							
												}
												p[i][j].eat += t;
												p[i][j].s = next(i, j, tem);
										}
								}						
						}
						qsort(p, 64, sizeof(p[0][0]), cmp1);
						cout << p[0][0].x << ' ' << p[0][0].y << endl;
				}
		}
		else
		{
				for (i = 0; i < 8; ++i)
						{
								for (j = 0; j < 8; ++j)
								{
										t = 0;
										tem = check(i, j);
										if (tem)
										{
												for (k = 0; k < 8; ++k)
												{
														if (tem & (1 << k))
														{
																for (ii = 0; ii < 3; ++ii)
																{
																		for (jj = 0; jj < 3; ++jj)
																				if (d[ii][jj] == k)
																						break;
																		if (jj != 3)
																				break;
																}
																t += direct(i, j, ii - 1, jj - 1, 0);														
														}							
												}
												p[i][j].eat += t;
										}
								}						
						}
						qsort(p, 64, sizeof(p[0][0]), cmp2);
						cout << p[0][0].x << ' ' << p[0][0].y << endl;
		}

		return 0;
}