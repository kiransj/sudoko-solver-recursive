#include <stdio.h>
#include <stdlib.h>
#include "sudo.h"
int dependency_block[81][4] = {
	{ 10,  11,  19,  20}, /* 00 */
	{  9,  11,  18,  20}, /* 01 */
	{  9,  10,  18,  19}, /* 02 */
	{ 13,  14,  22,  23}, /* 03 */
	{ 12,  14,  21,  23}, /* 04 */
	{ 12,  13,  21,  22}, /* 05 */
	{ 16,  17,  25,  26}, /* 06 */
	{ 15,  17,  24,  26}, /* 07 */
	{ 15,  16,  24,  25}, /* 08 */
	{  1,   2,  19,  20}, /* 09 */
	{  0,   2,  18,  20}, /* 10 */
	{  0,   1,  18,  19}, /* 11 */
	{  4,   5,  22,  23}, /* 12 */
	{  3,   5,  21,  23}, /* 13 */
	{  3,   4,  21,  22}, /* 14 */
	{  7,   8,  25,  26}, /* 15 */
	{  6,   8,  24,  26}, /* 16 */
	{  6,   7,  24,  25}, /* 17 */
	{  1,   2,  10,  11}, /* 18 */
	{  0,   2,   9,  11}, /* 19 */
	{  0,   1,   9,  10}, /* 20 */
	{  4,   5,  13,  14}, /* 21 */
	{  3,   5,  12,  14}, /* 22 */
	{  3,   4,  12,  13}, /* 23 */
	{  7,   8,  16,  17}, /* 24 */
	{  6,   8,  15,  17}, /* 25 */
	{  6,   7,  15,  16}, /* 26 */
	{ 37,  38,  46,  47}, /* 27 */
	{ 36,  38,  45,  47}, /* 28 */
	{ 36,  37,  45,  46}, /* 29 */
	{ 40,  41,  49,  50}, /* 30 */
	{ 39,  41,  48,  50}, /* 31 */
	{ 39,  40,  48,  49}, /* 32 */
	{ 43,  44,  52,  53}, /* 33 */
	{ 42,  44,  51,  53}, /* 34 */
	{ 42,  43,  51,  52}, /* 35 */
	{ 28,  29,  46,  47}, /* 36 */
	{ 27,  29,  45,  47}, /* 37 */
	{ 27,  28,  45,  46}, /* 38 */
	{ 31,  32,  49,  50}, /* 39 */
	{ 30,  32,  48,  50}, /* 40 */
	{ 30,  31,  48,  49}, /* 41 */
	{ 34,  35,  52,  53}, /* 42 */
	{ 33,  35,  51,  53}, /* 43 */
	{ 33,  34,  51,  52}, /* 44 */
	{ 28,  29,  37,  38}, /* 45 */
	{ 27,  29,  36,  38}, /* 46 */
	{ 27,  28,  36,  37}, /* 47 */
	{ 31,  32,  40,  41}, /* 48 */
	{ 30,  32,  39,  41}, /* 49 */
	{ 30,  31,  39,  40}, /* 50 */
	{ 34,  35,  43,  44}, /* 51 */
	{ 33,  35,  42,  44}, /* 52 */
	{ 33,  34,  42,  43}, /* 53 */
	{ 64,  65,  73,  74}, /* 54 */
	{ 63,  65,  72,  74}, /* 55 */
	{ 63,  64,  72,  73}, /* 56 */
	{ 67,  68,  76,  77}, /* 57 */
	{ 66,  68,  75,  77}, /* 58 */
	{ 66,  67,  75,  76}, /* 59 */
	{ 70,  71,  79,  80}, /* 60 */
	{ 69,  71,  78,  80}, /* 61 */
	{ 69,  70,  78,  79}, /* 62 */
	{ 55,  56,  73,  74}, /* 63 */
	{ 54,  56,  72,  74}, /* 64 */
	{ 54,  55,  72,  73}, /* 65 */
	{ 58,  59,  76,  77}, /* 66 */
	{ 57,  59,  75,  77}, /* 67 */
	{ 57,  58,  75,  76}, /* 68 */
	{ 61,  62,  79,  80}, /* 69 */
	{ 60,  62,  78,  80}, /* 70 */
	{ 60,  61,  78,  79}, /* 71 */
	{ 55,  56,  64,  65}, /* 72 */
	{ 54,  56,  63,  65}, /* 73 */
	{ 54,  55,  63,  64}, /* 74 */
	{ 58,  59,  67,  68}, /* 75 */
	{ 57,  59,  66,  68}, /* 76 */
	{ 57,  58,  66,  67}, /* 77 */
	{ 61,  62,  70,  71}, /* 78 */
	{ 60,  62,  69,  71}, /* 79 */
	{ 60,  61,  69,  70}, /* 80 */
};


int get_dependency_list(int num, Dependency *d)
{
	int count = 0, tmp, i;
	d->array[count++] = dependency_block[num][0]; 
	d->array[count++] = dependency_block[num][1]; 
	d->array[count++] = dependency_block[num][2]; 
	d->array[count++] = dependency_block[num][3];
	tmp = ((int)(num/9))*9;
	for(i = tmp; i < (tmp+9); i++)
	{
		if(i != num)
		d->array[count++] = i;
	}

	tmp = num%9;
	for(i = tmp; i < 81; i+=9)
	{
		if(i != num)
		d->array[count++] = i;
	}
	return count;
}

int validate_sudoko(SudokoBoard *sudo)
{
	int ret = 0;
	int i, j;
	Dependency d;

	for(j = 0; j < 81; j++)
	{
		if(sudo->node[j].value)
		{
			if(20 != get_dependency_list(j, &d)) abort();

			for(i = 0; i < 20; i++)
			{
				if(sudo->node[d.array[i]].value == sudo->node[j].value)
				{
					return -1;
				}
			}
		}
		else
		{
			ret = 1; 
		}
	}
	return ret;
}

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
