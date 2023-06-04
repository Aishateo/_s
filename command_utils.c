#include "shell.h"

/**
 * checkChain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void checkChain(p_info *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmdBufType == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmdBufType == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * shell_isChain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int shell_isChain(p_info *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmdBufType = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmdBufType = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmdBufType = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * replaceAlias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceAlias(p_info *info)
{
	int i;
	listS *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = stringStartsWithPrefix(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = shell_strchr(node->str, '=');
		if (!p)
			return (0);
		p = shell_strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replaceVariables - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceVariables(p_info *info)
{
	int i = 0;
	listS *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!shell_strcmp(info->argv[i], "$?"))
		{
			replaceString(&(info->argv[i]),
					shell_strdup(convertNumber(info->status, 10, 0)));
			continue;
		}
		if (!shell_strcmp(info->argv[i], "$$"))
		{
			replaceString(&(info->argv[i]),
					shell_strdup(convertNumber(getpid(), 10, 0)));
			continue;
		}
		node = stringStartsWithPrefix(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replaceString(&(info->argv[i]),
					shell_strdup(shell_strchr(node->str, '=') + 1));
			continue;
		}
		replaceString(&info->argv[i], shell_strdup(""));

	}
	return (0);
}

/**
 * replaceString - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceString(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
