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
}	

//Fills the possible value array of the board with values from 1-9.
void value_filler(sudoku_board *board)
{
	int i, j, k;

	//Fill the linked list values
	for(i=0; i<9; i++)
	{
		for(j=0; j<9; j++)
		{	
			board->values[i][j] = (value_head *) smalloc(sizeof(value_head));
			board->values[i][j]->length = 9;
			board->values[i][j]->first = NULL;
			for(k=9; k>0; k--)
			{
				insert_value(board->values[i][j],k);
			}
		}
	}

	//zero the board
	null_board(board);
}

void insert_value(value_head* head, int val)
{
	value *value_ptr, *first;

	value_ptr = (value *) smalloc(sizeof(value));
	
	first = (value *) head->first;
	head->first = value_ptr;
	value_ptr->next = (value *)first;
	value_ptr->available = val;
}

void delete_value(value_head* head, int val)
{
	value *now, *last;

	last = NULL;
	if(head->first == NULL) return;

	for(now=head->first;now->next != NULL; now= (value *)now->next)
	{	
		if(now->available == val)
		{
			if(last == NULL)
			{
				head->first = (value *) now->next;
			}else
			{
				last->next = (value *) now->next;
			}
			head->length -=1;
			continue;
			//free(now);
		}
		last=now;
	}

}



void random_board(sudoku_board *sudoku)
{
	int value;
	board_position *spot;
	
	for(spot = get_unfilled_space(sudoku);spot!= NULL;spot=get_unfilled_space(sudoku))
	{
		fill_with_random_sudoku_value(spot);
		sudoku->board[spot->i][spot->j] = spot->value;
		remove_invalid(sudoku,spot);
	}

}

void remove_invalid(sudoku_board *sudoku, board_position *spot)
{
	remove_same_from_row(sudoku,spot);
	remove_same_from_column(sudoku,spot);
	remove_same_from_square(sudoku,spot);
}

void remove_same_from_row(sudoku_board *sudoku, board_position *spot)
{
	int i;
	for(i=0;i<9;i++)
	{
		delete_value(sudoku->values[i][spot->j],spot->value);
	}
}


void remove_same_from_column(sudoku_board *sudoku, board_position *spot)
{
	int j;
	for(j=0;j<9;j++)
	{
		delete_value(sudoku->values[spot->i][j],spot->value);
	}
}


void remove_same_from_square(sudoku_board *sudoku, board_position *spot)
{
	int i,j,k,l;
	i = (spot->i)/3;
	j = (spot->j)/3;
	for(k=0;k<3;k++)
	{
		for(l=0;l<3;l++)
		{
			printf("%d %d\n",(i*3)+k,(j*3)+l);
			fflush(stdout);
			delete_value(sudoku->values[(i*3)+k][(j*3)+l],spot->value);
		}
	}
}


void fill_with_random_sudoku_value(board_position *spot)
{
	int i,j;
	value *val;
	i = ((rand()%(spot->values->length))+1);
	printf("in fill\n");
	fflush(stdout);
	val = spot->values->first;
	printf("in fill2 %d\n",spot->values->length);
	fflush(stdout);
	for(j=1;(j<i)&&(val->next !=NULL);j++)
	{	printf("%d\n",j);
		val = (value *) val->next;
	}
	printf("leaving fill\n");
	fflush(stdout);
	spot->value = val->available;
}


void * get_unfilled_space(sudoku_board* sudoku)
{
	board_position *spot;
	int i, j;
	for(i=0; i<9; i++)
	{
		for(j=0; j<9; j++)
		{
		 	if (sudoku->board[i][j]== 0)
			{
				spot = (board_position *) smalloc(sizeof(board_position));
				spot->i=i;
				spot->j=j;
				spot->values = sudoku->values[i][j];
				return spot;
			}
		}
	}
	return NULL;
}

//Function to print the board to stdout.
void boardprint(sudoku_board *sudoku)
{
	int i, j,k;
	value * next;
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

//Fills board with 0's and length 9's, ready for filling.
void null_board(sudoku_board *sudoku)
{
	int i, j;
	
	for(j=0;j<9;j++)
	{
		for(i=0;i<9;i++)
		{
			sudoku->board[i][j]=0;
			sudoku->values[i][j]->length = 9;
		}
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
			sudoku->values[i][j]->length = 0;
		}
	}

}
