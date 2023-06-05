#include "shell.h"

/**
 * main - Entry point of the shell program.
 *
 * @ac: The number of command-line arguments.
 * @av: An array of command-line argument strings.
 * Return: The exit status of the program.
 */
int main(int ac, char **av)
{
	p_info info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				shell_Eputs(av[0]);
				shell_Eputs(": 0: Can't open ");
				shell_Eputs(av[1]);
				shell_Eputchar('\n');
				shell_Eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readFD = fd;
	}
	shellPopulateEnvList(info);
	readHistory(info);
	shell_hsh(info, av);
	return (EXIT_SUCCESS);
}
