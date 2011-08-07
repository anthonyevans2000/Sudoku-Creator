/* Anthony Evans
 * anthonyevans2000@hotmail.com
 * A Sudoku Creator
 */

#include "sudokucreator.h"
#include "smalloc.c"
#include <stdio.h>

//Generates a complete and random sudoku pattern.
void * sudokucreator()
{
	sudoku_board * sudoku;
	sudoku = (sudoku_board*) smalloc(sizeof(sudoku_board));
	
	sudoku->board[0][0] = 1;
	printf("%d",sudoku->board[0][0]);

}

