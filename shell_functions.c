#include "shell.h"

/**
 * shellEviron - Prints the list of
 * environment variables.
 *
 * @info: The program information.
 * Return: 0 on success.
 */
int shellEviron(p_info *info)
{
	shellPrintListStr(info->env);
	return (0);
}

/**
 * shellGet_eviron - Retrieves the environment
 * variable with the specified name.
 *
 * @info: The program information.
 * @name: The name of the environment variable to retrieve.
 * Return: A pointer to the value of the
 * environment variable if found, or NULL otherwise.
 */
char *shellGet_eviron(p_info *info, const char *name)
{
	listS *node = info->env;
	char *p;

	while (node)
	{
		p = startsWith(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * shellSetEvison - Sets a new environment variable.
 *
 * @info: The program information.
 * Return: 0 on success, 1 if the number
 * of arguments is incorrect.
 */
int shellSetEvison(p_info *info)
{
	if (info->argc != 3)
	{
		shell_Eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (setEnv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * shellUnsetEnviron - Unsets environment variables.
 *
 * @info: The program information.
 * Return: 0 on success, 1 if too few arguments
 * are provided.
 */
int shellUnsetEnviron(p_info *info)
{
	int i;

	if (info->argc == 1)
	{
		shell_Eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetEnv(info, info->argv[i]);

	return (0);
}

/**
 * shellPopulateEnvList - Populates the environment list
 * from the existing environment variables.
 *
 * @info: The program information.
 * Return: 0 on success.
 */
int shellPopulateEnvList(p_info *info)
{
	listS *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		shellAddNodeEnd(&node, environ[i], 0);
	info->env = node;
	return (0);
}
