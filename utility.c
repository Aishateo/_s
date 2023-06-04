#include "shell.h"

/**
 * interact - Checks if the shell is running in an interactive mode.
 *
 * @info: Pointer to the p_info struct.
 * Return: 1 if the shell is running interactively,
 * 0 otherwise.
 */
int interact(p_info *info)
{
	return (isatty(STDIN_FILENO) && info->readFD <= 2);
}

/**
 * isDelim - Checks if a character is a delimiter.
 *
 * @ch: Character to check.
 * @delim: String containing delimiters.
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int isDelim(char ch, char *delim)
{
	while (*delim)
		if (*delim++ == ch)
			return (1);
	return (0);
}

/**
 * shell_atoi - Converts a string to an integer.
 *
 * @s: String to convert.
 * Return: The converted integer value.
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
 * shell_isAlpha - Checks if a character is an alphabetic character.
 *
 * @ch: Character to check.
 * Return: 1 if the character is an alphabetic character,
 * 0 otherwise.
 */
int shell_isAlpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}
