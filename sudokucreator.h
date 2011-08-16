/*
 * Anthony Evans
 * anthonyevans2000@hotmail.com
 * Header file for sudoku-creator.c
 */

typedef struct value_m
{
	struct value *next;
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
	//Points to a linked list of possible values, 
	//contains an int of this list's size.
	value_head * values[9][9];

} sudoku_board;

typedef struct board_position_m
{
	int i;
	int j;
	int value;
	value_head *values;
} board_position;

void * sudokucreator();
void boardprint(sudoku_board *board);
void value_filler(sudoku_board *board);
void null_board(sudoku_board *board);
void * get_unfilled_space(sudoku_board *board);
void fill_with_random_sudoku_value(board_position *spot );
void remove_invalid(sudoku_board *sudoku, board_position *spot);
void remove_same_from_row(sudoku_board *sudoku, board_position *spot);
void remove_same_from_column(sudoku_board *sudoku, board_position *spot);
void remove_same_from_square(sudoku_board *sudoku, board_position *spot);
void insert_value(value_head *head, int k);




