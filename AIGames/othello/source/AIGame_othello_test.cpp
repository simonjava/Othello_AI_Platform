#include "stdio.h"
#include "string.h"
#include "time.h"
#define LEN 8
/*
 *global variables
 */
int Direct[8][2] = {{0, -1}, {0, 1}, { -1, 0}, {1, 0}, { -1, -1}, {1, -1}, { -1, 1}, {1, 1}};
//left,right,up,down,up-left,down-left,up-right,down-right
int valueBoard3[8][8] =
{
    {5, 1, 1, 1, 1, 1, 1, 5},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {5, 1, 1, 1, 1, 1, 1, 5}
};
int valueBoard2[8][8] =
{
    {20, 0, 1, 2, 2, 1, 0, 20} ,
    {0, 0, 3, 3, 3, 3, 0, 0} ,
    {0, 3, 20, 20, 20, 20, 3, 0} ,
    {0, 3, 20, 60, 60, 20, 3, 0} ,
    {0, 3, 20, 60, 60, 20, 3, 0} ,
    {0, 3, 20, 20, 20, 20, 3, 0} ,
    {0, 0, 3, 3, 3, 3, 0, 0} ,
    {20, 0, 1, 2, 2, 1, 0, 20}
};
int valueBoard[8][8] =
{
    {2000, -250, 30, 30, 30, 30, -250, 2000} ,
    { -250, -350, 0, 0, 0, 0, -350, -250} ,
    {30, 0, 1, 2, 2, 1, 0, 30} ,
    {30, 0, 2, 16, 16, 2, 1, 30} ,
    {30, 0, 2, 16, 16, 2, 1, 30}  ,
    {30, 0, 1, 2, 2, 1, 0, 30} ,
    { -250, -350, 0, 0, 0, 0, -350, -250} ,
    {2000, -250, 30, 30, 30, 30, -250, 2000}
};
int originBoard[8][8] =
{
    { -1, -1, -1, -1, -1, -1, -1, -1},
    { -1, -1, -1, -1, -1, -1, -1, -1},
    { -1, -1, -1, -1, -1, -1, -1, -1},
    { -1, -1, -1,  1,  0, -1, -1, -1},
    { -1, -1, -1,  0,  1, -1, -1, -1},
    { -1, -1, -1, -1, -1, -1, -1, -1},
    { -1, -1, -1, -1, -1, -1, -1, -1},
    { -1, -1, -1, -1, -1, -1, -1, -1},
};
int colorComputer = 0;
int colorPerson = 1;
/*
 *function declare
 */
void guess(int board[][LEN], int ans[][LEN], int color);
int isCapable(int board[][LEN], int i, int j, int color);
void allDirection(int board[][LEN], int i, int j, int color, int direction[8]);
void change(int board[][LEN], int i, int j, int color);
int count(int array[][LEN], int thing);
void printBoard(int board[][LEN]);
void cpBoard(int boardA[][LEN], int boardB[][LEN]);
int boardValue(int board[][LEN], int color, int empty);
void AI(int board[][LEN], int steptogo[2]);
int alphaBeta(int board[LEN][LEN], int alpha, int beta, int color, int depth, int empty);
int test(int board[LEN][LEN], int color);
int play(void);
int contest(void);

/*
 * main code
 */
int main(void)
{
    contest();
    // play();
    // int board[LEN][LEN];
    // cpBoard(board, originBoard);
    // printf("%d\n", count(board, 1));
    return 0;
}
int contest(void)
{
    int board[LEN][LEN];//, ans[LEN][LEN], computerStep[2];
    int i, j, p, q, temp;
    for (i = 0; i < LEN; i++)
        for (j = 0; j < LEN; j++)
        {
            scanf("%d", &temp);
            board[i][j] = temp - 1; //now -1 means no chess; 0 means mine; 1 means opponent;
        }
    // printBoard(board);
    // int ans[LEN][LEN];
    // guess(board, ans, colorComputer);
    // printBoard(ans);
    //clock_t t = clock();
    int steptogo[2];
    AI(board, steptogo);
    p = steptogo[0];
    q = steptogo[1];
    printf("%d %d\n", p, q);
    //printf("%ld\n", clock() - t);
    return 0;
}

void guess(int board[][LEN], int ans[][LEN], int color)
//list all the capble place to put
{
    int i, j;
    for (i = 0; i < LEN; i++)
        for (j = 0; j < LEN; j++)
            ans[i][j] = isCapable(board, i, j, color);
}
int isCapable(int board[][LEN], int i, int j, int color)
//is capable to place the chess
{
    int k, p;
    if (board[i][j] != -1)
        return 0;
    for (p = 0; p < 8; p++)
    {
        if (i + Direct[p][0] >= LEN || i + Direct[p][0] < 0 || j + Direct[p][1] >= LEN || j + Direct[p][1] < 0) continue;
        if (board[i + Direct[p][0]][j + Direct[p][1]] != (!color)) continue;
        for (k = 2; (i + Direct[p][0] * k < LEN) && (i + Direct[p][0] * k >= 0) &&
                (j + Direct[p][1] * k < LEN) && (j + Direct[p][1] * k >= 0); k++)
        {
            if (board[i + Direct[p][0] * k][j + Direct[p][1] * k] == -1) break;
            if (board[i + Direct[p][0] * k][j + Direct[p][1] * k] == color) return 1;
        }
    }
    return 0;
}
void allDirection(int board[][LEN], int i, int j, int color, int direction[8])
//list all the direction that can change color,similar to function isCapable()
{
    int k, p;
    for (p = 0; p < 8; p++) direction[p] = 0;
    for (p = 0; p < 8; p++)
    {
        if (i + Direct[p][0] >= LEN || i + Direct[p][0] < 0 || j + Direct[p][1] >= LEN || j + Direct[p][1] < 0) continue;
        if (board[i + Direct[p][0]][j + Direct[p][1]] != (!color)) continue;
        for (k = 2; (i + Direct[p][0] * k < LEN) && (i + Direct[p][0] * k >= 0) &&
                (j + Direct[p][1] * k < LEN) && (j + Direct[p][1] * k >= 0); k++)
        {
            if (board[i + Direct[p][0] * k][j + Direct[p][1] * k] == -1) break;
            if (board[i + Direct[p][0] * k][j + Direct[p][1] * k] == color) direction[p] = 1;
        }
    }
}
void change(int board[][LEN], int i, int j, int color)
//change the color
{
    int p, k, direction[8];
    board[i][j] = color;
    allDirection(board, i, j, color, direction);
    for (p = 0; p < 8; p++)
    {
        if (direction[p] == 1)
        {
            for (k = 1; board[i + Direct[p][0] * k][j + Direct[p][1] * k] != color; k++)
                board[i + Direct[p][0] * k][j + Direct[p][1] * k] = color;
        }
    }
}
int count(int array[][LEN], int thing)
//count how many 'thing' in the 'array'
{
    int sum;
    int *n = *array + LEN * LEN, *p = *array;
    for (sum = 0; p < n; p++)
    {
        if (*p == thing)sum++;
    }
    return sum;
}
void cpBoard(int boardA[][LEN], int boardB[][LEN])
//copy boradB to boardA
{
    memcpy(boardA, boardB, sizeof(int)*LEN * LEN);
}

void printBoard(int board[][LEN])
{
    int i, j;
    for (i = 1; i >= 0; i--)
    {
        printf("   ");
        for (j = 0; j < LEN; j++) printf("%2c", i ? '0' + j : '-');
        printf("\n");
    }

    for (i = 0; i < LEN; i++)
    {
        printf("%2d|", i);
        for (j = 0; j < LEN; j++)
            if (board[i][j] == -1)printf("  ");
            else printf("%2d", board[i][j]);
        printf("\n");
    }
}

int test(int board[LEN][LEN], int color)
{
    int sum = 0, i, j, k;

    for (j = 0; j < LEN; j++)
    {
        if (board[0][j] == color)
        {
            for (k = 0; board[k][j] == color && k < LEN; k++)
                if (j == 0)sum += 10;
                else sum++;
        }
    }
    for (j = 0; j < LEN; j++)
    {
        if (board[LEN - 1][j] == color)
        {
            for (k = LEN - 1; board[k][j] == color && k >= 0; k--)
                if (j == 0)sum += 10;
                else sum++;
        }
    }
    for (i = 0; i < LEN; i++)
    {
        if (board[i][0] == color)
        {
            for (k = 0; board[i][k] == color && k < LEN; k++)
                if (i == 0)sum += 10;
                else sum++;
        }
    }
    for (i = 0; i < LEN; i++)
    {
        if (board[i][LEN - 1] == color)
        {
            for (k = LEN - 1; board[i][k] == color && k >= 0; k--)
                if (i == 0)sum += 10;
                else sum++;
        }
    }
    return sum;
}

int boardValue(int board[][LEN], int color, int empty)
{
    int i, j, n, sum = 0;
    int ans[LEN][LEN], sign[2];
    //empty = count(board, -1);
    sign[colorComputer] = 1;
    sign[colorPerson] = -1;

    sum = count(board, color);
    if (empty > 30) sum *= 2;
    else if (empty < 10) sum *= 10;
    else sum *= 6;

    if (empty > 55)
    {
        for (i = 0; i < LEN; i++)
            for (j = 0; j < LEN; j++)
                if (board[i][j] != -1)
                    sum += valueBoard2[i][j] * sign[board[i][j]];
    }
    else if (empty > 13)
    {
        for (i = 0; i < LEN; i++)
            for (j = 0; j < LEN; j++)
                if (board[i][j] != -1)
                    sum += valueBoard[i][j] * sign[board[i][j]];
    }
    else
    {
        // for (i = 0; i < LEN; i++)
        //     for (j = 0; j < LEN; j++)
        //         if (board[i][j] != -1)
        //             sum += valueBoard3[i][j] * sign[board[i][j]];
        sum += test(board, color) * 10;
        sum -= test(board, !color) * 10;
    }

    guess(board, ans, color);
    n = count(ans, 1);
    sum += n * 2;
    if (n == 0) sum -= 30;
    if (n == 0 && empty < 14) sum -= 300;
    guess(board, ans, !color);
    n = count(ans, 1);
    sum -= n * 2;
    if (n == 0) sum += 30;
    if (n == 0 && empty < 14) sum += 300;

    if (empty > 55)
    {
        for (i = 0; i < LEN; i++)
            for (j = 0; j < LEN; j++)
                if (ans[i][j] == 1)
                    sum -= valueBoard2[i][j];
    }
    else if (empty > 13)
    {
        for (i = 0; i < LEN; i++)
            for (j = 0; j < LEN; j++)
                if (ans[i][j] == 1)
                    sum -= valueBoard[i][j];
    }
    else
    {
        for (i = 0; i < LEN; i++)
            for (j = 0; j < LEN; j++)
                if (ans[i][j] == 1)
                    sum -= valueBoard3[i][j];
    }
    return sum;
}


void AI(int board[][LEN], int steptogo[2])
{
    //clock_t t = clock();
    int ans[LEN][LEN];
    int i, j, val, empty, depth, n;
    int max = -9999;
    empty = count(board, -1);
    guess(board, ans, colorComputer);
    for (i = 0; i < LEN; i++)
        for (j = 0; j < LEN; j++)
            if (ans[i][j] == 1)
            {
                steptogo[0] = i;
                steptogo[1] = j;
            }
    n = count(ans, 1);
    //printf("%d %d\n", n, empty);
    depth = 4;
    if (n < 5 && empty < 15)depth = 6;
    if (empty < 14)depth = 8;

    for (i = 0; i < LEN; i++)
        for (j = 0; j < LEN; j++)
            if (ans[i][j] == 1)
            {

                int board2[LEN][LEN];
                cpBoard(board2, board);
                change(board2, i, j, colorComputer);
                val = -1 * alphaBeta(board2, -9999, 9999, !colorComputer, depth, empty);
                //printf("%d %d %d\n", val, i, j);
                if (val > max)
                {
                    max = val;
                    steptogo[0] = i;
                    steptogo[1] = j;
                }
            }
}

int alphaBeta(int board[LEN][LEN], int alpha, int beta, int color, int depth, int empty)
{
    int max, val, i, j;
    int sign[2], ans[LEN][LEN];
    max = -9999;
    sign[colorComputer] = 1;
    sign[colorPerson] = -1;

    if (depth <= 0) return sign[color] * boardValue(board, colorComputer, empty);

    guess(board, ans, color);
    //printBoard(board);
    //printf("%d %d\n",count(ans,1),color);
    if (count(ans, 1) == 0)
    {
        guess(board, ans, !color);
        if (count(ans, 1) == 0) return sign[color] * boardValue(board, colorComputer, empty);
        else return -1 * alphaBeta(board, -1 * beta, -1 * alpha, !color, depth, empty);
    }
    for (i = 0; i < LEN; i++)
    {
        for (j = 0; j < LEN; j++)
        {
            if (ans[i][j] == 1)
            {
                int board2[LEN][LEN];
                cpBoard(board2, board);
                change(board2, i, j, color);
                val = -1 * alphaBeta(board2, -1 * beta, -1 * alpha, !color, depth - 1, empty);
                if (val > alpha)
                {
                    if (val >= beta)return val;
                    alpha = val;
                }
                if (val > max)max = val;
            }
        }
    }
    return max;
}

int play(void)
{
    int board[LEN][LEN], ans[LEN][LEN];
    int colorCurrent, colorWinner, countComputer, countPerson, countStep;
    //    int i, j;
    //    for(i = 0; i < LEN; i++)
    //        for(j = 0; j < LEN; j++)
    //            scanf("%d", &board[i][j]);
    cpBoard(board, originBoard);

    printf("++++\n");
    printf("color for Person %d\ncolor for Computer %d\n", colorPerson, colorComputer);
    colorCurrent = colorComputer;

    int flag = 0;
    while (1)
    {
        int p, q;

        printBoard(board);
        printf("++++\n");

        if (colorCurrent == 1) printf("Person\n");
        else printf("Computer\n");

        guess(board, ans, colorCurrent);
        countStep = count(ans, 1);
        printf("available step counts:%d\n", countStep);

        if (countStep == 0)
        {
            if (flag == 0)
            {
                flag++;
                colorCurrent = colorCurrent ^ 1;
                continue;
            }
            else
            {
                break;
            }
        }
        else
        {
            flag = 0;
        }

        //printBoard(ans);
        printf("input step\n");

        if (colorCurrent == 0)
            //That colorCurrent is 0 means it's Computer's turn.
        {
            int steptogo[2];
            AI(board, steptogo);
            p = steptogo[0];
            q = steptogo[1];
            printf("%d %d\n", p, q);
        }
        else
            //It's Person's turn
        {
            //int i,j;
            //for(i=0; i<8; i++)
            //    for(j=0; j<8; j++)
            //        if(ans[i][j]==1)
            //            printf("%d %d %d\n",i,j,pointValue[i][j]);
            while (1)
            {
                scanf("%d%d", &p, &q);
                if (ans[p][q] != 1) printf("False,again\n");
                else break;
            }
        }

        printf("++++\n");
        board[p][q] = colorCurrent;
        change(board, p, q, colorCurrent);
        countComputer = count(board, colorComputer);
        countPerson = count(board, colorPerson);


        //Judge who is winner

        if (countComputer + countPerson == LEN * LEN)
        {
            break;
        }

        //Change the current player
        colorCurrent = !colorCurrent;
    }
    colorWinner = (countComputer > countPerson ? countComputer : countPerson);
    if (countComputer == countPerson)colorWinner = -2;
    if (colorWinner == -2)printf("Draw\n");

    else printf("Winner : %s\n", (colorWinner == colorPerson ? "Person" : "Computer"));
    return 0;
}
