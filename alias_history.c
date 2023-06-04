#include "shell.h"

/**
 * shell_history - Displays the shell history.
 * @info: Pointer to the p_info structure.
 * Return: 0 on success.
 */
int shell_history(p_info *info)
{
	shell_printList(info->history);
	return (0);
}

/**
 * unset_alias - Unsets an alias by removing it from the alias list.
 * @info: Pointer to the p_info structure.
 * @str: String containing the alias to unset.
 * Return: 1 if the alias was not found, otherwise 0.
 */
int unset_alias(p_info *info, char *str)
{
	char *p, c;
	int ret;

	p = shell_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = shellDelNodeAtIndex(&(info->alias),
		getNodeIndex(info->alias, stringStartsWithPrefix(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - Sets an alias by adding it to the alias list.
 * @info: Pointer to the p_info structure.
 * @str: String containing the alias to set.
 * Return: 1 if the alias format is incorrect
 * or unset_alias fails, otherwise 0.
 */
int set_alias(p_info *info, char *str)
{
	char *p;

	p = shell_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (shellAddNodeEnd(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints the alias in the specified node.
 * @node: Pointer to the alias node to print.
 * Return: 0 on success, otherwise 1.
 */
int print_alias(listS *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = shell_strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		shell_putchar(*a);
		shell_putchar('\'');
		shell_puts(p + 1);
		shell_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * shell_alias - Displays the shell aliases.
 * @info: Pointer to the p_info structure.
 * Return: 0 on success.
 */
int shell_alias(p_info *info)
{
	int i = 0;
	char *p = NULL;
	listS *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = shell_strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(stringStartsWithPrefix(info->alias, info->argv[i], '='));
	}

	return (0);
}
