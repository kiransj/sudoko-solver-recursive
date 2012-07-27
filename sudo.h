#ifndef __SUDO_H
#define __SUDO_H

#include <stdio.h>
#include <string.h>

#define LOG_INFO(format, args...)   fprintf(stdout, format "\n", ## args)
#define LOG_ERROR(format, args...)  fprintf(stderr, format "\n", ## args)
typedef unsigned char uint8_t;

typedef struct
{
	uint8_t value;
	uint8_t hints[10];
	int num_hints;
}Node;
typedef struct
{
	Node node[81];
	int num_solved;
	int unsolved;
}SudokoBoard;

typedef struct
{
	int array[20];
}Dependency;

int get_dependency_list(int num, Dependency *d);
int validate_sudoko(SudokoBoard *sudo);
void print_sudoko(SudokoBoard *su);
#endif
