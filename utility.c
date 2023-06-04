#include "shell.h"

/**
 * interact - interact mode
 * @info: struct for info
 *
 * Return: 1 if interact mode
 */
int interact(p_info *info)
{
	return (isatty(STDIN_FILENO) && info->readFD <= 2);
}

/**
 * isDelim - checks  delimeter
 * @ch: char
 * @delim: the delimeter
 * Return: 1 if true, 0 if false
 */
int isDelim(char ch, char *delim)
{
	while (*delim)
		if (*delim++ == ch)
			return (1);
	return (0);
}

/**
 * shell_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string
 */

int shell_atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * shell_isAlpha - checks for alphabetic character
 * @ch: The character
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int shell_isAlpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}
