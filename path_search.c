#include "shell.h"

/**
 * is_shellCMD - Checks if the given path
 * corresponds to a shell command.
 *
 * @info: Pointer to the p_info struct.
 * @path: Path to check.
 * Return: 1 if the path corresponds to a regular file,
 * 0 otherwise.
 */
int is_shellCMD(p_info *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_shellChars - Creates a duplicate string containing
 * a portion of the original string.
 *
 * @pathstr: Original string.
 * @start: Start position of the portion to duplicate.
 * @stop: Stop position of the portion to duplicate.
 * Return: Pointer to the duplicate string.
 */
char *dup_shellChars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_shellPath - Searches for the executable file
 * in the specified shell path.
 *
 * @info: Pointer to the p_info struct.
 * @pathstr: Shell path.
 * @cmd: Command to search for.
 * Return: Pointer to the path of the executable
 * file if found, NULL otherwise.
 */
char *find_shellPath(p_info *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((shell_strlen(cmd) > 2) && startsWith(cmd, "./"))
	{
		if (is_shellCMD(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_shellChars(pathstr, curr_pos, i);
			if (!*path)
				shell_strcat(path, cmd);
			else
			{
				shell_strcat(path, "/");
				shell_strcat(path, cmd);
			}
			if (is_shellCMD(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
