/*
 * Anthony Evans
 * anthonyevans2000@hotmail.com
 * Header file for sudoku-creator.c
 */

typedef struct value_m
{
	value *next;
	int available;
} value;

typedef struct value_head_m
{
	value *first;
	int length;
} value_head;



typedef struct sudoku_board_m
{
	int board[9][9];
	//will implement a pointer array to a circular linked list- which will list
	//available values for the position to hold.
	int values[9][9][9];
	//value *values

} sudoku_board;

typedef struct board_position_m
{
	int i;
	int j;
	//value *values;
} board_position;

void * sudokucreator();
void boardprint(sudoku_board *board);
void value_filler(sudoku_board *board);

