#include "shell.h"

/**
 **_strncat - concate strings
 *@dest: 1st string
 *@src: 2d string
 *@n: amount of bytes
 *Return: string
 */
char *_strncat(char *dest, char *src, int n)
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
 **_strncpy - string cp
 *@dest: destination
 *@src: source
 *@n: amount
 *Return: string
 */
char *_strncpy(char *dest, char *src, int n)
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
 **_strchr - locates a character
 *@s: string
 *@c: character
 *Return: pointer to the memory
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

