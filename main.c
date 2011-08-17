
#include "sudokucreator.c"
#include <stdio.h>
int main()
{
	board_position *spot;
	value *now;
	int i,j;
	sudoku_board * f;
	f = (sudoku_board *) sudokucreator();
	srand(time(NULL));

	random_board(f);
	
	
	//generic_board(f);
	//spot = (board_position *) get_unfilled_space(f);
	//fill_with_random_sudoku_value(spot);
	//remove_same_from_row(f,spot);
	
	
	
	
	
	/*for(i=0;i<10000000;i++)
	{
		fill_with_random_sudoku_value(spot);
		j = spot->value+j;
	}

	printf("j/%lf = %lf",i,j/i);
	fflush(stdout);
	*/
	
	/*
	printf("\nRemoving %d\n",spot->value);
	for(i=0;i<9;i++)
	{
		printf("\n %d  ",i);
		for(now=f->values[i][spot->j]->first; now != NULL; now = (value *) now->next)
		{
			printf("%d",now->available);
		}
	}
	*/
	//generic_board(f);
	boardprint(f);
	
	return 0;
}
