/*
 * Anthony Evans
 * anthonyevans2000@hotmail.com
 * Header file for sudoku-creator.c
 */

void * sudokucreator();

typedef struct sudoku_board_m
{
	int board[9][9];
	int values[9][9][9];
} sudoku_board;
