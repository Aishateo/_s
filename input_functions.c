#include "shell.h"

/**
 * input_buf - Reads input from the buffer or stdin.
 *
 * @info: The program information.
 * @buf: The buffer to store the input.
 * @len: The length of the buffer.
 * Return: The number of characters read.
 */
ssize_t input_buf(p_info *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*p_free((void **)info->cmdBuf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, shell_handler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = shellGet_line(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->lineCountFlag = 1;
			shell_remove(*buf);
			buildHistoryList(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmdBuf = buf;
			}
		}
	}
	return (r);
}

/**
 * shellGet_input - Retrieves input from the buffer.
 *
 * @info: The program information.
 * Return: The length of the input.
 */
ssize_t shellGet_input(p_info *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	shell_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		checkChain(info, buf, &j, i, len);
		while (j < len)
		{
			if (shell_isChain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmdBufType = CMD_NORM;
		}

		*buf_p = p;
		return (shell_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - Reads input from the file descriptor.
 *
 * @info: The program information.
 * @buf: The buffer to store the input.
 * @i: The current position in the buffer.
 * Return: The number of characters read.
 */
ssize_t read_buf(p_info *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readFD, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * shellGet_line - Reads a line of input from the buffer.
 *
 * @info: The program information.
 * @ptr: The pointer to the input buffer.
 * @length: The length of the input buffer.
 * Return: The length of the input line.
 */
int shellGet_line(p_info *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = shell_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = shell_realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		shell_strncat(new_p, buf + i, k - i);
	else
		shell_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * shell_handler - Signal handler for shell.
 * @sig_num: The signal number.
 */
void shell_handler(__attribute__((unused))int sig_num)
{
	shell_puts("\n");
	shell_puts("$ ");
	shell_putchar(BUF_FLUSH);
}
