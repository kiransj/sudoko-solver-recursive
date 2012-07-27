#include <stdio.h>
#include <stdlib.h>
#include "sudo.h"

int update_hints(SudokoBoard *sudo, int num)
{
	int i;
	Dependency d;

	if(sudo->node[num].value == 0)
	{
		if(20 != get_dependency_list(num, &d)) abort();

		for(i = 0; i < 20; i++)
		{
			if(sudo->node[d.array[i]].value != 0)
			{
				if(sudo->node[num].hints[sudo->node[d.array[i]].value] != 0)
				{
					sudo->node[num].hints[sudo->node[d.array[i]].value] = 0;
					sudo->node[num].num_hints--;

					if(sudo->node[num].num_hints <= 0) abort();
				}
			}
		}

		if(sudo->node[num].num_hints == 1)
		{
			for(i = 1; i <= 9; i++)
			{
				if(sudo->node[num].hints[i])
				{
					sudo->node[num].value = sudo->node[num].hints[i];
					sudo->node[num].hints[i] = 0;
					sudo->node[num].num_hints--;
					return 1;
				}
			}
			abort();
		}
	}
	return 0;
}
SudokoBoard solve_sudoko(SudokoBoard sudo)
{
	int i, flag;
	do
	{
		flag = 0;
		for(i = 0; i < 81; i++)
		{
			flag += update_hints(&sudo, i);
		}
		if(0 != flag)
		{
			print_sudoko(&sudo);
		}
	}
	while(0 != flag);
	if(validate_sudoko(&sudo) != 0)
	{
		sudo.unsolved = 1;
		return sudo;
	}

	sudo.unsolved = 0;
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
	print_sudoko(&sudo);
	if(validate_sudoko(&sudo) != 0)
	{
		printf("\n invalid game\n");
	}
	else
	{
		sudo = solve_sudoko(sudo);
	}
	if(sudo.unsolved)
	{
		printf("this sudoko is unsolvable");
	}
	print_sudoko(&sudo);
	return 0;
}
