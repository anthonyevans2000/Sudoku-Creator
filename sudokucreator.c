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
			board->values[i][j]->length = 10;
			board->values[i][j]->first = NULL;
			for(k=1; k<=9; k++)
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

	for(now=head->first ; now != NULL ; now = (value *) now->next)
	{	
		if(now->available == val)
		{
			if(last == NULL)
			{
				head->first = (value *) now->next;
				free(now);
			}else
			{
				last->next = (value *) now->next;
				free(now);
				now = last;
			}
			head->length -=1;
			continue;
		}
		last = now;
		if(now->next == NULL)
		{
			return;
		}
	}

}



int random_board(sudoku_board *sudoku)
{
	int value,i;
	board_position *spot;
	
	for(i=0;i<81;i++)
	{
		spot = (board_position *) get_unfilled_space(sudoku);
		if(spot == NULL) break;
		fill_with_random_sudoku_value(spot);
		sudoku->board[spot->i][spot->j] = spot->value;
		remove_invalid(sudoku,spot);
		free(spot);
		spot=NULL;
	}
	if(i==81)
	{
		return 1;
	}else
	{
		return 0;
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
			delete_value(sudoku->values[(i*3)+k][(j*3)+l],spot->value);
		}
	}
}


void fill_with_random_sudoku_value(board_position *spot)
{
	int i,j;
	value *val;
	if(spot->values->length == 0)
	{
		return;
	}

	i = (int)(rand()%((spot->values->length)+1));
	val = spot->values->first;
	
	for(j=0;(j<i)&&(val->next !=NULL);j++)
	{
		val = (value *) val->next;
	}
	spot->value = val->available;
}


void * get_unfilled_space(sudoku_board* sudoku)
{
	board_position *spot;
	spot = (board_position *) smalloc(sizeof(board_position));
	spot->values = NULL;

	
	int i,j,k,l,x,y,spot_exists=0;
	for(k=0; k<3; k++)
	{
		for(l=0; l<3; l++)
		{
			for(i=0; i<3; i++)
			{
				for(j=0; j<3; j++)
				{	x = i+(k*3);
					y = j+(l*3);
					if ((sudoku->board[x][y]== 0))
					{
						if(spot->values!=NULL)
						{
							if(spot->values->length < sudoku->values[x][y]->length)
							{
								continue;	
							}	
						}else
						{
							spot->i=x;
							spot->j=y;
							spot->values = sudoku->values[x][y];
							spot_exists = 1;
						}
					}
				}
			}
		}
	}
	if(spot_exists)
	{
		return spot;
	}else
	{
		return NULL;
	}
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
