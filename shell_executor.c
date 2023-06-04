#include "shell.h"

/**
 * shell_hsh - main shell
 * @info: the parameter
 * @av: the argument vector
 *
 * Return: 0, 1, or error
 */
int shell_hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		shellClear_info(info);
		if (interact(info))
			shell_puts("$ ");
		shell_Eputchar(BUF_FLUSH);
		r = shellGet_input(info);
		if (r != -1)
		{
			shellSet_info(info, av);
			builtin_ret = findBuiltin(info);
			if (builtin_ret == -1)
				find_shellCMD(info);
		}
		else if (interact(info))
			shell_putchar('\n');
		shellFree_info(info, 0);
	}
	writeHistory(info);
	shellFree_info(info, 1);
	if (!interact(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * fork_shellCMD - forks an exec thread
 * @info: the parameter
 *
 * Return: void
 */
void fork_shellCMD(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, getEnviron(info)) == -1)
		{
			shellFree_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				shellPrint_error(info, "Permission denied\n");
		}
	}
}


/**
 * findBuiltin - find
 * @info: the parameter
 *
 * Return: -1, 0, 1, 2
 */
int findBuiltin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", shell_exit},
		{"env", shellEviron},
		{"help", shell_help},
		{"history", shell_history},
		{"setenv", shellSetEvison},
		{"unsetenv", shellUnsetEnviron},
		{"cd", shell_cd},
		{"alias", shell_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (shell_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_shellCMD - find command
 * @info: the parameter
 *
 * Return: void
 */
void find_shellCMD(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!isDelim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_shellPath(info, shellGet_eviron(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_shellCMD(info);
	}
	else
	{
		if ((interact(info) || shellGet_eviron(info, "PATH=")
					|| info->argv[0][0] == '/') && is_shellCMD(info, info->argv[0]))
			fork_shellCMD(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			shellPrint_error(info, "not found\n");
		}
	}
}
