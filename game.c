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
		printf("��ѡ��:");
        scanf_s("%d", &input);
		switch(input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("�˳���Ϸ\n");
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
			board[i][j] = set;   //�˴�set�Ѿ����ַ�������������ʹ��'set'
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
		board[x-1][y+1] - 8*'0';  //'3' -'0' = 3   '1' -'0' = 1    ���ַ�������õ����ͣ�����ASSII�����
	                                 //3 +'0' = '3'   ���ͼ����ַ��õ��ַ�
}

void FinalResult(char board[ROWS][COLS], char shows[ROWS][COLS],int row, int col, int x, int y)
{
    while(board[x][y] != '1' && shows[x][y] == '*' && x >= 1 && x <= ROW && y >= 1 && y <= COL) // ע����Χչ��ʱ��ȷ�Ϲ��ĸ��Ӳ����ظ�ȷ��,��д�ᵼ����ѭ��
    {                                                             //ע��x,y�ķ�Χ���ƣ���Ϊ���ϵĸ���������չ���ˣ������һȦ����Ҫ�����չʾ
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
		printf("����������->:");
		scanf_s("%d%d",&x,&y);
		if(x >= 1 && x <= 9 && y >= 1 && y <= 9)
		{
			if(mines[x][y] == '1')
			{
				printf("�㱻ը����\n");
				DisplayBoard(mines, ROWS, COLS);  //�����ڲ����ú���ʱ��mines�Ǵ��ݸ�DisplayBoard()������ʵ�Σ���mines
				                                  //������FineBoard()�������βΣ���ʵ��ΪFineBoard(mine, show, ROWS, COLS);
				                                  //���ݵ�mine�����������mines�β��ں����ڲ�ʵ��������д��ݵ�(������DisplayBoard��ʵ����FineBoard���β�)
				//break;
			}
			else
			{
				FinalResult(mines, shows, ROW, COL, x, y);
				
			}
		}
		else
		{
			printf("����Ƿ�������������\n");
		}
	//}
	/*if(ret >= ROW * COL - EasyCount )
	{
		printf("��Ӯ��\n");
		DisplayBoard(mines, ROWS, COLS);

	}*/
}




void game()
{
	char mine[ROWS][COLS] = {0};
	char show[ROWS][COLS] = {0};
	InialBoard(mine, ROWS, COLS, '0');  //��ʹ��һ��������������Ҫ��ʱ����ͨ������һ������������Ҫ���������
	InialBoard(show, ROWS, COLS, '*');

	DisplayBoard(mine, ROWS, COLS);
	DisplayBoard(show, ROWS, COLS);

	SetBoard(mine, ROWS, COLS);
	DisplayBoard(mine, ROWS, COLS);

	FineBoard(mine, show, ROWS, COLS);
	DisplayBoard(show, ROWS, COLS);
}