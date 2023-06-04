#include "shell.h"

/**
 * shellEviron - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int shellEviron(info_t *info)
{
	shellPrintListStr(info->env);
	return (0);
}

/**
 * shellGet_eviron - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *shellGet_eviron(info_t *info, const char *name)
{
	list_t *node = info->env;
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
 * shellSetEvison - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int shellSetEvison(info_t *info)
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
 * shellUnsetEnviron - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int shellUnsetEnviron(info_t *info)
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
 * shellPopulateEnvList - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int shellPopulateEnvList(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		shellAddNodeEnd(&node, environ[i], 0);
	info->env = node;
	return (0);
}

