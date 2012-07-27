#include <stdio.h>
#include "sudo.h"

void print_sudoko(SudokoBoard *su)
{
    int i;
	printf("\n|-----------------------------|\n|");
	for(i = 0; i < 81; i++)
	{
		if(i && i % 3 == 0)
		{
			if(i % 27 == 0)
			{
				printf("|\n|-----------------------------");
			}
			if(i % 9 == 0)
			{
				printf("|\n");				
			}
			printf("|");
		}
		if(su->node[i].value != 0)
			printf(" %d ", su->node[i].value);
		else
			printf(" * ");

	}
	printf("|\n|-----------------------------|\n\n");
}
