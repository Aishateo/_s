#include "shell.h"

/**
 * p_free - Frees the memory pointed
 * to by ptr and sets it to NULL.
 *
 * @ptr: A pointer to a pointer to be freed.
 * Return: 1 if the memory was freed successfully,
 * 0 otherwise.
 */
int p_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
