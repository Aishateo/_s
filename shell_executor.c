#include "shell.h"

/**
 * shell_hsh - Executes the shell program.
 * @info: Pointer to the program information struct.
 * @av: Array of command-line arguments.
 * Return: The return value of the last executed built-in command.
 */
int shell_hsh(p_info *info, char **av)
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
 * fork_shellCMD - Forks a child process
 * to execute a shell command.
 * @info: Pointer to the program information struct.
 */
void fork_shellCMD(p_info *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
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
 * findBuiltin - Finds and executes a built-in command.
 * @info: Pointer to the program information struct.
 * Return: The return value of the executed built-in command,
 * or -1 if not found.
 */
int findBuiltin(p_info *info)
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
			info->lineCount++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_shellCMD - Finds and executes a shell command.
 * @info: Pointer to the program information struct.
 */
void find_shellCMD(p_info *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->lineCountFlag == 1)
	{
		info->lineCount++;
		info->lineCountFlag = 0;
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
