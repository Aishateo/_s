#include "shell.h"

/**
 * shellListLen - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t shellListLen(const listS *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * shellListToStrings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **shellListToStrings(listS *head)
{
	listS *node = head;
	size_t i = shellListLen(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(shell_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = shell_strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * shell_printList - prints all elements of a listS linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t shell_printList(const listS *h)
{
	size_t i = 0;

	while (h)
	{
		shell_puts(convertNumber(h->num, 10, 0));
		shell_putchar(':');
		shell_putchar(' ');
		shell_puts(h->str ? h->str : "(nil)");
		shell_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * stringStartsWithPrefix - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
listS *stringStartsWithPrefix(listS *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = startsWith(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getNodeIndex - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t getNodeIndex(listS *head, listS *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
