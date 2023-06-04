#include "shell.h"

/**
 * renumberHistory - renumbers history
 * @info: arguments
 *
 * Return: count
 */
int renumberHistory(p_info *info)
{
	listS *nde = info->history;
	int i = 0;

	while (nde)
	{
		nde->num = i++;
		nde = nde->next;
	}
	return (info->histcount = i);
}

/**
 * writeHistory - creates or appends to file
 * @info: struct
 *
 * Return: 1 or -1
 */
int writeHistory(p_info *info)
{
	ssize_t fdd;
	char *filename = getHistoryFile(info);
	listS *nde = NULL;

	if (!filename)
		return (-1);

	fdd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fdd == -1)
		return (-1);
	for (nde = info->history; nde; nde = nde->next)
	{
		shell_putsFD(nde->str, fdd);
		shell_putFD('\n', fdd);
	}
	shell_putFD(BUF_FLUSH, fdd);
	close(fdd);
	return (1);
}

/**
 * readHistory - reads history
 * @info: struct
 *
 * Return: success, 0
 */
int readHistory(p_info *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fdd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = getHistoryFile(info);

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
			buildHistoryList(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		buildHistoryList(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		shellDelNodeAtIndex(&(info->history), 0);
	renumberHistory(info);
	return (info->histcount);
}

/**
 * getHistoryFile - gets history
 * @info: struct
 *
 * Return: string history
 */

char *getHistoryFile(p_info *info)
{
	char *buff, *dir;

	dir = shellGet_eviron(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (shell_strlen(dir) + shell_strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	shell_strcpy(buff, dir);
	shell_strcat(buff, "/");
	shell_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * buildHistoryList - adds entry to history
 * @info: struct
 * @buf: buffer
 * @linecount: linecount, histcount
 *
 * Return: Always 0
 */
int buildHistoryList(p_info *info, char *buf, int linecount)
{
	listS *nde = NULL;

	if (info->history)
		nde = info->history;
	shellAddNodeEnd(&nde, buf, linecount);

	if (!info->history)
		info->history = nde;
	return (0);
}
