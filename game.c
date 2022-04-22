#include"game.h"

void menu()
{
	printf("***************************\n");
	printf("***** 1   play  ***********\n");
	printf("***** 0   exit  ***********\n");
	printf("***************************\n");
}
void test()
{
	int input = 0;
	do
	{
		menu();
		printf("请选择:");
        scanf_s("%d", &input);
		switch(input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			break;
		}
	}while(input);
}

void InialBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
	int i = 0;
	int j = 0;
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			board[i][j] = set;   //此处set已经是字符变量，无需再使用'set'
		}
	}
}

void DisplayBoard(char board[ROWS][COLS], int rows, int cols)
{
	int i = 0;
	int j = 0;
	for(j = 0;j < cols - 1;j++)
		{
			printf("%d  ",j);
		}
	printf("\n");
	for(i = 1;i < rows-1; i++)
	{
		printf("%d ",i);
		
		for(j = 1;j < cols-1;j++)
		{
			printf(" %c ",board[i][j]);
		}
		printf("\n");
	}
}

void SetBoard(char board[ROWS][COLS], int rows, int cols)
{
	int x = 0;
	int y = 0;
	int count = EasyCount;
	while(count)
	{
		x = rand() % ROW +1;
	    y = rand() % COL +1;
	    if(board[x][y] != '1')
	    {

		    board[x][y] = '1';
		    count--;
	    }
	}
}

int GiveResult(char board[ROWS][COLS], int x, int y)
{
	return board[x-1][y] +
		board[x-1][y-1] +
		board[x][y-1] +
		board[x+1][y-1] +
		board[x+1][y] +
		board[x+1][y+1] +
		board[x][y+1] +
		board[x-1][y+1] - 8*'0';  //'3' -'0' = 3   '1' -'0' = 1    即字符相减，得到整型，根据ASSII表而得
	                                 //3 +'0' = '3'   整型加上字符得到字符
}

void FinalResult(char board[ROWS][COLS], char shows[ROWS][COLS],int row, int col, int x, int y)
{
    while(board[x][y] != '1' && shows[x][y] == '*' && x >= 1 && x <= ROW && y >= 1 && y <= COL) // 注意周围展开时，确认过的格子不再重复确认,不写会导致死循环
    {                                                             //注意x,y的范围限制，因为边上的格子无须再展开了，扩大的一圈不需要向玩家展示
        if(GiveResult(board, x, y) == 0)
        {
            shows[x][y] = ' ';
            FinalResult(board, shows, ROW, COL, x - 1, y);
            FinalResult(board, shows, ROW, COL, x - 1, y - 1);
            FinalResult(board, shows, ROW, COL, x, y - 1);
            FinalResult(board, shows, ROW, COL, x + 1, y - 1);
            FinalResult(board, shows, ROW, COL, x + 1, y);
            FinalResult(board, shows, ROW, COL, x + 1, y + 1);
            FinalResult(board, shows, ROW, COL, x, y + 1);
            FinalResult(board, shows, ROW, COL, x - 1, y + 1);
        }
        else
        {
            shows[x][y] = GiveResult(board, x, y) + '0';
            break;
        }
    }  
}       
  
void FineBoard(char mines[ROWS][COLS], char shows [ROWS][COLS], int rows, int cols)
{
	int x = 0;
	int y = 0;
	int ret = 0;
	//while(ret < ROW * COL - EasyCount)
	//{
		printf("请输入坐标->:");
		scanf_s("%d%d",&x,&y);
		if(x >= 1 && x <= 9 && y >= 1 && y <= 9)
		{
			if(mines[x][y] == '1')
			{
				printf("你被炸死了\n");
				DisplayBoard(mines, ROWS, COLS);  //函数内部调用函数时，mines是传递给DisplayBoard()函数的实参，而mines
				                                  //自身是FineBoard()函数的形参，其实参为FineBoard(mine, show, ROWS, COLS);
				                                  //传递的mine；因而这里是mines形参在函数内部实例化后进行传递的(这里是DisplayBoard的实参是FineBoard的形参)
				//break;
			}
			else
			{
				FinalResult(mines, shows, ROW, COL, x, y);
				
			}
		}
		else
		{
			printf("坐标非法，请重新输入\n");
		}
	//}
	/*if(ret >= ROW * COL - EasyCount )
	{
		printf("你赢了\n");
		DisplayBoard(mines, ROWS, COLS);

	}*/
}




void game()
{
	char mine[ROWS][COLS] = {0};
	char show[ROWS][COLS] = {0};
	InialBoard(mine, ROWS, COLS, '0');  //当使用一个函数满足两个要求时，可通过增加一个参数传递需要满足的内容
	InialBoard(show, ROWS, COLS, '*');

	DisplayBoard(mine, ROWS, COLS);
	DisplayBoard(show, ROWS, COLS);

	SetBoard(mine, ROWS, COLS);
	DisplayBoard(mine, ROWS, COLS);

	FineBoard(mine, show, ROWS, COLS);
	DisplayBoard(show, ROWS, COLS);
}