#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROW 9
#define COL 9

#define ROWS ROW+2  //为了处理边缘的雷的排查，将棋盘扩大一圈，此法甚秒
#define COLS COL+2

#define EasyCount 10


void test();
void game();
void InialBoard(char board[ROWS][COLS],int rows,int cols);
void DisplayBoard(char board[ROWS][COLS], int rows, int cols);
void SetBoard(char board[ROWS][COLS], int rows, int cols);
void FineBoard(char mines[ROWS][COLS], char shows [ROWS][COLS],int rows, int cols);
int GiveResult(char board[ROWS][COLS], int x, int y);
void FinalResult(char board[ROWS][COLS], char shows[ROWS][COLS],int row, int col, int x, int y);

