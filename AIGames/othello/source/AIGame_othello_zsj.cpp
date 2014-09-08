/*
* author: SJ Zhu
* refer: http://shaofei.name/OthelloAI/othello.html
*/
#include "stdio.h"
#include "string.h"
#include "time.h"
#define SIZE 64
#define LEN 8
#define Infinity 9999

int computer_color = 1;
int orignboard[SIZE] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 2, 0, 0, 0,
    0, 0, 0, 2, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,

};

int directions[8] = { -9, -8, -7, -1, 1, 7, 8, 9 };
int directions2[8][2] = { { -1, -8}, {0, -8}, {1, -8}, { -1, 0}, {1, 0}, { -1, 8}, {0, 8}, {1, 8} };

void guess(int board[], int ans[], int color);
int available(int board[], int i, int color);
void change(int board[], int i, int color);
int count(int array[], int thing);
void cpBoard(int boardA[], int boardB[]);
int computer(int board[], int depth, int exact_depth);
int calculate(int board[], int color);
int exact(int board[], int color);
int exact_search(int board[], int alpha, int beta, int color);
int search(int board[], int alpha, int beta, int depth, int color);
int contest(void);
int play(void);

void guess(int board[], int ans[], int color)
//list all the capble place to put
{
    int i, sum;
    for (i = 0, sum = 0; i < SIZE; i++)
    {
        ans[i] = available(board, i, color);
        //if (ans[i])sum++;
    }
    //return sum;
}

int available(int board[], int i, int color)
//is capable to place the chess
{
    int k, p;

    if (board[i] != 0)
        return 0;

    for (p = 0; p < 8; p++)
    {
        if (((i % LEN + directions2[p][0]) > LEN - 1)
                || ((i % LEN + directions2[p][0]) < 0)
                || (i + directions2[p][1] < 0 )
                || (i + directions2[p][1] >= 64))
            continue;
        if (board[i + directions[p]] == color || board[i + directions[p]] == 0 ) continue;
        for (k = 2; ((i % LEN + directions2[p][0] * k) < LEN)
                && ((i % LEN + directions2[p][0] * k) >= 0)
                && (i + directions2[p][1] * k >= 0)
                && (i + directions2[p][1] * k < SIZE); k++)
        {
            if (board[i + directions[p] * k] == 0) break;
            if (board[i + directions[p] * k] == color) return 1;
        }
    }
    return 0;
}

void change(int board[], int i, int color)
{
    board[i] = color;
    int p, k;
    for (p = 0; p < 8; p++)
    {
        if (((i % LEN + directions2[p][0]) > LEN - 1)
                || ((i % LEN + directions2[p][0]) < 0)
                || (i + directions2[p][1] < 0 )
                || (i + directions2[p][1] >= 64))
            continue;
        if (board[i + directions[p]] == color || board[i + directions[p]] == 0 ) continue;
        int temp_i = i + directions[p];
        for (; ((temp_i % LEN + directions2[p][0]) < LEN)
                && ((temp_i % LEN + directions2[p][0]) >= 0)
                && (temp_i + directions2[p][1] >= 0)
                && (temp_i + directions2[p][1] < SIZE); temp_i += directions[p])
        {
            if (board[temp_i] == 0) break;
            if (board[temp_i] == color)
            {

                while (temp_i != i)
                {
                    board[temp_i] = color;
                    temp_i -= directions[p];
                }
                break;
            }
        }
    }
}

int count(int array[], int thing)
//count how many 'thing' in the 'array'
{
    int i, sum;
    for (i = 0, sum = 0; i < SIZE; i++)
        if (array[i] == thing)
            sum++;
    return sum;
}

void cpBoard(int boardA[], int boardB[])
//boardA = boardB
{
    memcpy(boardA, boardB, sizeof(int)*SIZE);
}

int computer(int board[], int depth, int exact_depth)
{
    int ans[SIZE], step, val, i;
    int max = -Infinity;
    guess(board, ans, computer_color);
    for (i = 0; i < SIZE; i++)
        if (ans[i])
        {
            step = i;
            break;
        }
    for (i = 0; i < SIZE; i++)
        if (ans[i])
        {
            int board_tmp[SIZE], moves;
            cpBoard(board_tmp, board);
            change(board_tmp, i, computer_color);
            moves = 64 - count(board, 0);
            if (moves + exact_depth >= 64)
                val = -exact_search(board_tmp, -Infinity, Infinity, computer_color);
            else if (i == 9 || i == 14 || i == 54 || i == 49)
                val = -search(board, -Infinity, Infinity, depth + 1, computer_color);
            else
                val = -search(board, -Infinity, Infinity, depth, computer_color);
            if (val > max)
            {
                max = val;
                step = i;
            }
        }
    return step;
}

int calculate(int board[], int color)
{
    int  sum = 0;
    if (board[0])sum += ((board[0] == color) ? 1 : -1) * 30;
    else if (board[9])sum += ((board[9] == color) ? -1 : 1) * 25;
    if (board[7])sum += ((board[7] == color) ? 1 : -1) * 30;
    else if (board[14])sum += ((board[14] == color) ? -1 : 1) * 25;
    if (board[56])sum += ((board[56] == color) ? 1 : -1) * 30;
    else if (board[4])sum += ((board[14] == color) ? -1 : 1) * 25;
    if (board[63])sum += ((board[63] == color) ? 1 : -1) * 30;
    else if (board[14])sum += ((board[14] == color) ? -1 : 1) * 25;
    return sum;
}

int exact(int board[], int color)
{
    int i, array[3] = {0, 0, 0};
    for (i = 0; i < SIZE; i++)
        array[board[i]]++;
    if (array[color] == 0)
        return -64;
    else if (array[3 - color] == 0)
        return 64;
    else
        return array[color] - array[3 - color];
}

int exact_search(int board[], int alpha, int beta, int color)
{
    if (count(board, 0) == 0)
        return exact(board, color);

    int max = -Infinity, val, ans[SIZE], i;

    guess(board, ans, color);
    if (count(ans, 1) == 0)
    {
        guess(board, ans, 3 - color);
        if (count(ans, 1) == 0) return exact(board, color);
        else return -exact_search(board, -beta, -alpha, 3 - color);
    }

    for (i = 0; i < SIZE; i++)
        if (ans[i] == 1)
        {
            int temp_board[SIZE];
            cpBoard(temp_board, board);
            change(temp_board, i, color);
            val = -exact_search(temp_board, -beta, -alpha, 3 - color);
            if (val > alpha)
            {
                if (val >= beta)return val;
                alpha = val;
            }
            if (val > max)max = val;
        }
    return max;
}

int search(int board[], int alpha, int beta, int depth, int color)
{
    if (depth == 0)
        return calculate(board, color);

    int max = -Infinity, val, ans[SIZE], i;

    guess(board, ans, color);
    if (count(ans, 1) == 0)
    {
        guess(board, ans, 3 - color);
        if (count(ans, 1) == 0) return exact(board, color);
        else return -search(board, -beta, -alpha, 3 - color, depth);
    }

    for (i = 0; i < SIZE; i++)
        if (ans[i] == 1)
        {
            int temp_board[SIZE];
            cpBoard(temp_board, board);
            change(temp_board, i, color);
            val = -search(temp_board, -beta, -alpha, 3 - color, depth - 1);
            if (val > alpha)
            {
                if (val >= beta)return val;
                alpha = val;
            }
            if (val > max)max = val;
        }
    return max;
}

int contest(void)
{
    int board[SIZE];
    int i, step;
    for (i = 0; i < SIZE; i++)
        scanf("%d", &board[i]);
    step = computer(board, 3, 10);
    printf("%d %d\n", step / LEN, step % LEN);
    return 0;
}

void printBoard(int board[])
{
    int i;
    printf("  ");
    for (i = 0; i < 8; i++)
        printf("%d ", i);
    printf("\n");
    for (i = 0; i < SIZE; i++)
    {
        if (i % 8 == 0)printf("%d ", i / 8);
        if (board[i] == 0)printf("  ");
        else printf("%d ", board[i]);
        if ((i + 1) % 8 == 0)printf("\n");
    }
}

int play(void)
{
    int board[SIZE], ans[SIZE];
    int colorCurrent, colorWinner, countComputer, countPerson, colorPerson = 1, colorComputer = 2, countStep;
    //    int i, j;
    //    for(i = 0; i < LEN; i++)
    //        for(j = 0; j < LEN; j++)
    //            scanf("%d", &board[i][j]);
    cpBoard(board, orignboard);

    printf("++++\n");
    printf("color for Person %d\ncolor for Computer %d\n", colorPerson, colorComputer);
    colorCurrent = colorComputer;

    int flag = 0;
    while (1)
    {
        int p, q, step;

        printBoard(board);
        printf("++++\n");

        if (colorCurrent == colorPerson) printf("Person\n");
        else printf("Computer\n");

        guess(board, ans, colorCurrent);
        countStep = count(ans, 1);
        printf("available step counts:%d\n", countStep);

        if (countStep == 0)
        {
            if (flag == 0)
            {
                flag++;
                colorCurrent = 3 - colorCurrent;
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

        if (colorCurrent == colorComputer)
            //That colorCurrent is 0 means it's Computer's turn.
        {
            step = computer(board, 3, 10);
            p = step / 8;
            q = step % 8;
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
                step = p * 8 + q;
                if (ans[step] != 1) printf("False,again\n");
                else break;
            }
        }

        printf("++++\n");
        change(board, step, colorCurrent);
        countComputer = count(board, colorComputer);
        countPerson = count(board, colorPerson);


        //Judge who is winner

        if (countComputer + countPerson == SIZE)
        {
            break;
        }

        //Change the current player
        colorCurrent = 3 - colorCurrent;
    }
    colorWinner = (countComputer > countPerson ? countComputer : countPerson);
    if (countComputer == countPerson)colorWinner = -2;
    if (colorWinner == -2)printf("Draw\n");

    else printf("Winner : %s\n", (colorWinner == colorPerson ? "Person" : "Computer"));
    return 0;
}


