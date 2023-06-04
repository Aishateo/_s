#include "shell.h"

/**
 * shell_help - changes the current directory
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int shell_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	shell_puts("help call works. Function not yet implemented \n");
	if (0)
		shell_puts(*arg_array);
	return (0);
}

/**
 * shell_exit - exits
 * @info: Structure containing
 * Return: exits with
 */
int shell_exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = shell_errAtoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			shellPrint_error(info, "Illegal number: ");
			shell_Eputs(info->argv[1]);
			shell_Eputchar('\n');
			return (1);
		}
		info->err_num = shell_errAtoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * shell_cd - changes the current directory
 * @info: Structure for info
 * Return: Always 0
 */
int shell_cd(info_t *info)
{
	char *str, *dir, buffer[1024];
	int chdir_ret;

	str = getcwd(buffer, 1024);
	if (!str)
		shell_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = shellGet_eviron(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = shellGet_eviron(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (shell_strcmp(info->argv[1], "-") == 0)
	{
		if (!shellGet_eviron(info, "OLDPWD="))
		{
			shell_puts(str);
			shell_putchar('\n');
			return (1);
		}
		shell_puts(shellGet_eviron(info, "OLDPWD=")), shell_putchar('\n');
		chdir_ret =
			chdir((dir = shellGet_eviron(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		shellPrint_error(info, "can't cd to ");
		shell_Eputs(info->argv[1]), shell_Eputchar('\n');
	}
	else
	{
		setEnv(info, "OLDPWD", shellGet_eviron(info, "PWD="));
		setEnv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

