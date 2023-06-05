#include "shell.h"

/**
 * getEnviron - Retrieves the environment variables.
 *
 * @info: The program information.
 * Return: The environment variables as an array of strings.
 */
char **getEnviron(p_info *info)
{
	if (!info->environ || info->envChanged)
	{
		info->environ = shellListToStrings(info->env);
		info->envChanged = 0;
	}

	return (info->environ);
}

/**
 * unsetEnv - Unsets an environment variable.
 *
 * @info: The program information.
 * @var: The variable to unset.
 * Return: 1 if the variable was unset, 0 otherwise.
 */
int unsetEnv(p_info *info, char *var)
{
	listS *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = startsWith(node->str, var);
		if (p && *p == '=')
		{
			info->envChanged = shellDelNodeAtIndex(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->envChanged);
}

/**
 * setEnv - Sets a new environment variable.
 *
 * @info: The program information.
 * @var: The variable to set.
 * @value: The value of the variable.
 * Return: 0 on success, 1 if there was an error.
 */
int setEnv(p_info *info, char *var, char *value)
{
	char *buf = NULL;
	listS *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(shell_strlen(var) + shell_strlen(value) + 2);
	if (!buf)
		return (1);
	shell_strcpy(buf, var);
	shell_strcat(buf, "=");
	shell_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = startsWith(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->envChanged = 1;
			return (0);
		}
		node = node->next;
	}
	shellAddNodeEnd(&(info->env), buf, 0);
	free(buf);
	info->envChanged = 1;
	return (0);
}
