#include "shell.h"

/**
 * set_zeros - all bytes set to int array to 0
 * @arr: initialized array
 * @size: array size
 * Return: Nothing
 */

void set_zeros(unsigned int *arr, size_t size)
{
	size_t x;

	for (x = 0; x < size; x++)
		arr[x] = 0;
}

/**
 * set_nulls - all characters set to nulls
 * @arr: initialized array
 * @size: array size
 * Return: Nothing
 */

void set_nulls(char *arr, size_t size)
{
	size_t x;

	for (x = 0; x < size; x++)
		arr[x] = '\0';
}
