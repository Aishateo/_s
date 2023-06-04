#include "shell.h"

/**
 * shell_strlen - length of a string
 * @s: string
 *
 * Return: integer
 */
int shell_strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * shell_strcmp - comparison
 * @s1: first
 * @s2: second
 *
 * Return: negative, positive, zero
 */
int shell_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * shell_strcat - two strings
 * @dest: destination buffer
 * @src: source buffer
 *
 * Return: pointer
 */
char *shell_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * startsWith - starts with haystack
 * @haystack: string
 * @needle: substring
 *
 * Return: address of next char of haystack or NULL
 */
char *startsWith(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
