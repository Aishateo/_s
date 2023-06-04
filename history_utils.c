#include "shell.h"

/**
 * renumber_history - renumbers history
 * @info: arguments
 *
 * Return: count
 */
int renumber_history(info_t *info)
{
	list_t *nde = info->history;
	int i = 0;

	while (nde)
	{
		nde->num = i++;
		nde = nde->next;
	}
	return (info->histcount = i);
}

/**
 * write_history - creates or appends to file
 * @info: struct
 *
 * Return: 1 or -1
 */
int write_history(info_t *info)
{
	ssize_t fdd;
	char *filename = get_history_file(info);
	list_t *nde = NULL;

	if (!filename)
		return (-1);

	fdd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fdd == -1)
		return (-1);
	for (nde = info->history; nde; nde = nde->next)
	{
		_putsfd(nde->str, fdd);
		_putfd('\n', fdd);
	}
	_putfd(BUF_FLUSH, fdd);
	close(fdd);
	return (1);
}

/**
 * read_history - reads history
 * @info: struct
 *
 * Return: success, 0
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fdd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fdd = open(filename, O_RDONLY);
	free(filename);
	if (fdd == -1)
		return (0);
	if (!fstat(fdd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fdd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fdd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * get_history_file - gets history
 * @info: struct
 *
 * Return: string history
 */

char *get_history_file(info_t *info)
{
	char *buff, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * build_history_list - adds entry to history
 * @info: struct
 * @buf: buffer
 * @linecount: linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *nde = NULL;

	if (info->history)
		nde = info->history;
	add_node_end(&nde, buf, linecount);

	if (!info->history)
		info->history = nde;
	return (0);
}
