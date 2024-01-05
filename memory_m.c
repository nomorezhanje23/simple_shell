#include "shell.h"
/**
 * _memset - memory filler od same byte
 * @s: memory area pointer
 * @b: byte
 * @n: bytes number
 * Return: pointer -s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * free_vector - memory to be freed
 * @vec: the vector
 * Return: Nothing.
 */

void free_vector(char **vec)
{
	char **ptr = vec;

	if (!vec)
		return;
	while (*vec)
		free(*vec++);

	free(ptr);
}

/**
 * _realloc - the reallocation of memory
 * @ptr: previous memory block pointer
 * @old_size: previous block byte size
 * @new_size: new block byte size
 * Return: old block pointer
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	p = malloc(new_size);
	if (!p)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

/**
 * bfree - pointer is freed
 * @ptr: pointer address to be freed
 * Return: 1 if successful, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
