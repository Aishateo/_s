#include "shell.h"

/**
 * shell_strlen - Computes the length of a string.
 * @s: The input string.
 * Return: The length of the string.
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
 * shell_strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 * Return: An integer less than, equal to,
 * or greater than zero if s1 is found,
 * respectively, to be less than, to match, or be greater than s2.
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
 * shell_strcat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 * Return: A pointer to the resulting string.
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
 * startsWith - Checks if a string starts with another string.
 * @haystack: The string to search within.
 * @needle: The string to search for.
 * Return: A pointer to the first occurrence
 * of the needle within the haystack,
 * or NULL if the needle is not found.
 */
char *startsWith(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
