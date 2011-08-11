/* Anthony Evans
 * anthonyevans2000@hotmail.com
 * A Sudoku Creator
 */

#include "sudokucreator.h"
#include "smalloc.c"


//Generates a complete and random sudoku pattern.
void * sudokucreator()
{
	sudoku_board * sudoku;
	sudoku = (sudoku_board*) smalloc(sizeof(sudoku_board));
	
	value_filler(sudoku);
	return sudoku;

	//Debug
	//sudoku->board[0][0] = 1;
	//printf("%d",sudoku->board[0][0]);

}	

//Fills the possible value array of the board with values from 1-9.
void value_filler(sudoku_board *board)
{
	int i, j, k;

	for(i=0; i<9; i++)
	{
		for(j=0; j<9; j++)
		{	
			for(k=0; k<9; k++)
			{
				board->values[i][j][k] = (k+1);
			}
		}
	}
}

void random_board(sudoku_board *board)
{

	repeat_while_select_random_space=!null;
	select_random_unfilled_space();
	//will call function to eliminate values that clash with new input
	place_random_valid_value()

}

//Function to print the board to stdout.
void boardprint(sudoku_board *sudoku)
{
	int i, j;
	printf("Sudoku Board\n\n");
	for(j=0;j<9;j++)
	{
		for(i=0;i<9;i++)
		{
			printf("%d ",sudoku->board[i][j]);
		}
		printf("\n");
	}
}


//Fills the board with linear 1-9 integers- It's an invalid arrangement for a sudoku board
//Useful for print testing
void generic_board(sudoku_board *sudoku)
{
	int i, j;
	
	for(j=0;j<9;j++)
	{
		for(i=0;i<9;i++)
		{
			sudoku->board[i][j]=(i+1);
		}
	}

}
