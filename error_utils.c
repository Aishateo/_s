#include "shell.h"

/**
 * shell_remove - Removes the '#' character
 * and everything after it from a string.
 * @buf: The input string.
 */
void shell_remove(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

/**
 * shell_errAtoi - Converts a string to an integer.
 * @s: The input string.
 * Return: The converted integer value,
 * or -1 if the conversion fails.
 */
int shell_errAtoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * shellPrint_error - Prints an error message
 * to stderr in the specified format.
 * @info: The program information.
 * @estr: The error string.
 */
void shellPrint_error(p_info *info, char *estr)
{
	shell_Eputs(info->fname);
	shell_Eputs(": ");
	shellPrint_decimal(info->lineCount, STDERR_FILENO);
	shell_Eputs(": ");
	shell_Eputs(info->argv[0]);
	shell_Eputs(": ");
	shell_Eputs(estr);
}

/**
 * shellPrint_decimal - Prints an integer to the
 * specified file descriptor.
 *
 * @input: The integer to print.
 * @fd: The file descriptor.
 * Return: The number of characters printed.
 */
int shellPrint_decimal(int input, int fd)
{
	int (*__putchar)(char) = shell_putchar;
	int i, c = 0;
	unsigned int _abs_, curr;

	if (fd == STDERR_FILENO)
		__putchar = shell_Eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		c++;
	}
	else
		_abs_ = input;
	curr = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + curr / i);
			c++;
		}
		curr %= i;
	}
	__putchar('0' + curr);
	c++;

	return (c);
}

/**
 * convertNumber - Converts a number to a string
 * representation in the specified base.
 *
 * @num: The number to convert.
 * @base: The base for the conversion.
 * @flags: Additional conversion flags.
 * Return: A pointer to the string representation of the number.
 */
char *convertNumber(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *p;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buffer[49];
	*p = '\0';

	do	{
		*--p = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--p = sign;
	return (p);
}
