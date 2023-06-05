#include "shell.h"

/**
 * shell_memorySet - Fills a block of memory
 * with a specified value.
 *
 * @s: Pointer to the memory block to fill.
 * @b: Value to be set (as an unsigned char).
 * @n: Number of bytes to be set to the value.
 *
 * Return: Pointer to the memory block
 * after setting the values.
 */
char *shell_memorySet(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * s_free - Frees the memory allocated for
 * an array of strings.
 *
 * @pp: Pointer to the array of strings (char**)
 * to be freed.
 * Return: None.
 */
void s_free(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * shell_realloc - Reallocates memory for
 * a given block with a new size.
 *
 * @ptr: Pointer to the memory block to be reallocated.
 * @old_size: Current size of the memory block.
 * @new_size: New size of the memory block.
 *
 * Return: Pointer to the reallocated memory block.
 * NULL is returned if memory allocation fails
 * or if new_size is 0.
 */
void *shell_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
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
