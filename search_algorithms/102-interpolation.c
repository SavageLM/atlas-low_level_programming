#include "search_algos.h"

/**
 * interpolation_search - Finds value using interpolation search algo
 * @array: sorted array to search
 * @size: size of array
 * @value: value to search for
 * Return: Index of value or -1
 */
int interpolation_search(int *array, size_t size, int value)
{
	size_t high = size - 1, low = 0, pos = 0;

	if (!array)
		return (-1);
	pos = POSITION(low, high, array, value);
	while (low < high && value <= array[high] && value >= array[low])
	{
		printf("Value checked array[%ld] = [%d]\n", pos, array[pos]);
		if (array[pos] == value)
			return (pos);
		else if (array[pos] < value)
		{
			low = pos + 1;
			pos = POSITION(low, high, array, value);
		}
		else if (array[pos] > value)
		{
			high = pos--;
			pos = POSITION(low, high, array, value);
		}
	}
	printf("Value checked array[%ld] is out of range\n", pos);
	return (-1);
}
