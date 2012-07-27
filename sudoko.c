#include <stdio.h>
#include <stdlib.h>
#include "sudo.h"

SudokoBoard solve_sudoko(SudokoBoard sudo)
{
	if(validate_sudoko(&sudo) != 0)
	{
		printf("\n invalid game\n");
	}
return sudo;
}


int main(int argc, char *argv[])
{
	int i;
	FILE *fp;
	SudokoBoard sudo;

	if(argc == 1)
	{
		LOG_ERROR("usage : %s filename", argv[0]);
		return 0;
	}

	fp = fopen(argv[1], "r");
	if(NULL == fp)
	{
		LOG_ERROR("fopen('%s') failed", argv[1]);
		return 1;
	}
	memset(&sudo, 0, sizeof(SudokoBoard));
	for(i = 0; i < 81; i++)
	{
		int ch = fgetc(fp);	

		if(ch == EOF)
		{
			LOG_ERROR("could not read 81 bytes of data");
			fclose(fp);
			return 1;
		}
		if(ch == '\n')
		{
			i--;
			continue;
		}
		if(isdigit(ch) && (ch >= '1') && (ch <= '9'))
		{
			sudo.node[i].value = ch - '0';
			sudo.num_solved++;
		}
		else
		{
			int k;
			for(k = 0; k <= 9; k++)
			sudo.node[i].hints[k] = k;
			sudo.node[i].num_hints = 9;
		}
	}	
	fclose(fp);
	sudo = solve_sudoko(sudo);
	if(sudo.unsolved)
	{
		printf("this sudoko is unsolvable");
	}
	print_sudoko(&sudo);
	return 0;
}
