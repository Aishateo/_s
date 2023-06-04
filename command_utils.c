#include "shell.h"

/**
 * checkChain - Checks the command buffer
 * type and updates the index.
 *
 * @info: Pointer to the program information.
 * @buf: Pointer to the command buffer.
 * @p: Pointer to the current index.
 * @i: The current index.
 * @len: The length of the buffer.
 * Return: None.
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
 * shell_isChain - Checks if a chain operator
 * is present in the command buffer.
 *
 * @info: Pointer to the program information.
 * @buf: Pointer to the command buffer.
 * @p: Pointer to the current index.
 * Return: 1 if a chain operator is found, 0 otherwise.
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
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmdBufType = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * replaceAlias - Replaces the command with
 * its alias if available.
 *
 * @info: Pointer to the program information.
 * Return: 1 if the alias is replaced, 0 otherwise.
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
 * replaceVariables - Replaces variables in the
 * command with their corresponding values.
 *
 * @info: Pointer to the program information.
 * Return: 0 (placeholder return value).
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
 * replaceString - Replaces a string with a new string.
 *
 * @old: Pointer to the old string to be replaced.
 * @new: Pointer to the new string.
 * Return: 1 on success.
 */
int replaceString(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
