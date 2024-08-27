#include "search_algos.h"

/**
 * exponential_search - Performs an exponential search algo
 * @array: array to search
 * @size: size of array
 * @value: value to search for
 * Return: First index with Value, or -1
 */
int exponential_search(int *array, size_t size, int value)
{
	size_t high = 1, low = 0;

	if (!array || size == 0)
		return (-1);
	if (value == array[0])
	{
		printf("Value checked array[0] = [%d]\n", value);
		return (0);
	}
	while (high < size && array[high] <= value)
	{
		printf("Value checked array[%ld] = [%d]\n", high, array[high]);
		low = high, high = high * 2;
	}
	if (high >= size)
		high = size - 1;
	printf("Value found between indexes [%ld] and [%ld]\n", low, high);
	return (binary_search(array, low, high, size, value));
}

/**
 * binary_search - Function that searches an array binarily
 * @array: Sorted array to search
 * @min: starting point of search
 * @max: max index to look at
 * @size: size of array
 * @value: value to search for
 * Return: index of value, or -1
 */

int binary_search(int *array, size_t min, size_t max, size_t size, int value)
{
	size_t mid;

	if (array == NULL || size == 0)
		return (-1);

	print_search(array, min, max);

	while (min <= max)
	{
		mid = (min + max) / 2;

		if (array[mid] == value)
			return (mid);
		if (array[mid] > value)
			max = mid - 1;
		else
			min = mid + 1;
		print_search(array, min, max);
	}
	return (-1);
}

/**
 * print_search - prints array to be searched
 * @array: array to print
 * @min: starting size of array
 * @max: max size of array
 */

void print_search(int *array, size_t min, size_t max)
{
	size_t i;

	i = min;
	if (i > max)
		return;

	printf("Searching in array: ");
	for (; i <= max; i++)
	{
		if (i > min)
			printf(", ");
		printf("%d", array[i]);
	}
	printf("\n");
}
