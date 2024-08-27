#ifndef SEARCH_ALGOS_H
#define SEARCH_ALGOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* MACROS */

#define POSITION(l, h, a, v) \
	(l + (((double)(h - l) / (a[h] - a[l]))) * (v - a[l]))

/*Prototypes*/
int linear_search(int *array, size_t size, int value);
int binary_search(int *array, size_t min, size_t max, size_t size, int value);
void print_search(int *array, size_t min, size_t max);

int interpolation_search(int *array, size_t size, int value);
int exponential_search(int *array, size_t size, int value);

#endif
