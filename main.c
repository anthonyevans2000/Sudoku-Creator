
#include "sudokucreator.c"
#include <stdio.h>
int main()
{
	sudoku_board * f;
	f = (sudoku_board *) sudokucreator();
	generic_board(f);
	boardprint(f);
	return 0;
}
