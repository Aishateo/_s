#include "shell.h"

/**
 * p_free - frees pointer
 * @ptr: address
 *
 * Return: 1 or 0.
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
