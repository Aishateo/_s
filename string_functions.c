#include "shell.h"

/**
 * shell_strncat - Concatenates a specified number of characters
 * from the source string to the destination string.
 *
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of characters to concatenate.
 * Return: A pointer to the destination string.
 */
char *shell_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *st = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (st);
}

/**
 * shell_strncpy - Copies a specified number of characters
 * from the source string to the destination string.
 *
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 * Return: A pointer to the destination string.
 */
char *shell_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *st = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (st);
}

/**
 * shell_strchr - Locates the first occurrence of
 * a character in a string.
 *
 * @s: The string to search.
 * @c: The character to locate.
 * Return: A pointer to the first occurrence of the
 * character in the string, or NULL if not found.
 */
char *shell_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
