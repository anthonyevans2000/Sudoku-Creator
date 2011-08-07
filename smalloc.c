//smalloc.c
//a safer, though simple, version of malloc

#include <stdlib.h>
#include <stdio.h>
#include "smalloc.h"


void *
smalloc(size_t size)
{
	void *p = malloc(size);
	if(p == NULL){
		fprintf(stderr,"There was not enough space on the heap. "
		"Aborting.\n");
		exit(EXIT_FAILURE);
	}
	return p;
}
