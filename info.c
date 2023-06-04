#include "shell.h"

/**
 * shellFree_info - frees info
 * @info: address
 * @all: fields
 */
void shellFree_info(info_t *info, int all)
{
	s_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			shellFreeList(&(info->env));
		if (info->history)
			shellFreeList(&(info->history));
		if (info->alias)
			shellFreeList(&(info->alias));
		s_free(info->environ);
			info->environ = NULL;
		p_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		shell_putchar(BUF_FLUSH);
	}
}

/**
 * shellSet_info - initializes struct
 * @info: address
 * @av: vector
 */
void shellSet_info(info_t *info, char **av)
{
	int it = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = splits_strToWrd(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = shell_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (it = 0; info->argv && info->argv[it]; it++)
			;
		info->argc = it;

		replaceAlias(info);
		replaceVariables(info);
	}
}

/**
 * shellClear_info - initializes info_t struct
 * @info: struct address
 */
void shellClear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
