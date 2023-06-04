#include "shell.h"

/**
 * shell_strdup - Duplicates a string.
 *
 * @str: The string to duplicate.
 * Return: Pointer to a newly allocated memory
 * block containing the duplicated string.
 * NULL is returned if str is NULL
 * or if memory allocation fails.
 */
char *shell_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * shell_strcpy - Copies a string from source to destination.
 *
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination string (dest).
 */
char *shell_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * shell_puts - Writes a string to the standard output.
 *
 * @str: Pointer to the string to be written.
 * Return: None.
 */
void shell_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		shell_putchar(str[i]);
		i++;
	}
}

/**
 * shell_putchar - Writes a character to the standard output.
 *
 * @c: The character to be written.
 *
 * Return: 1 on success.
 */
int shell_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
