#include "shell.h"

/**
 * shell_Eputs - Writes a string to the standard error output.
 * @str: The string to write.
 */
void shell_Eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		shell_Eputchar(str[i]);
		i++;
	}
}

/**
 * shell_Eputchar - Writes a character to the standard error output.
 *
 * @c: The character to write.
 * Return: 1 on success.
 */
int shell_Eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * shell_putFD - Writes a character to the specified file descriptor.
 *
 * @c: The character to write.
 * @fd: The file descriptor to write to.
 * Return: 1 on success.
 */
int shell_putFD(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * shell_putsFD - Writes a string to the specified file descriptor.
 *
 * @str: The string to write.
 * @fd: The file descriptor to write to.
 * Return: The number of characters written.
 */
int shell_putsFD(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += shell_putFD(*str++, fd);
	}
	return (i);
}
