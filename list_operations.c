#include "shell.h"

/**
 * shellListLen - Computes the length of a linked list.
 * @h: The head of the linked list.
 * Return: The length of the linked list.
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
 * shellListToStrings - Converts a linked list
 * of strings to an array of strings.
 *
 * @head: The head of the linked list.
 * Return: An array of strings representing the linked list.
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
 * shell_printList - Prints the elements of a linked list.
 * @h: The head of the linked list.
 * Return: The number of elements in the linked list.
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
 * stringStartsWithPrefix - Finds the first node in a linked list
 * whose string starts with a prefix.
 *
 * @node: The head of the linked list.
 * @prefix: The prefix string to search for.
 * @c: The character to compare after the prefix.
 * Return: A pointer to the first matching node, or NULL if not found.
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
 * getNodeIndex - Finds the index of a node in a linked list.
 * @head: The head of the linked list.
 * @node: The node to find the index of.
 * Return: The index of the node, or -1 if not found.
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
