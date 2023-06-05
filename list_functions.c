#include "shell.h"

/**
 * shellAddNodeEnd - Adds a new node at the end of a linked list.
 *
 * @head: A pointer to the head of the linked list.
 * @str: The string to be stored in the new node.
 * @num: An integer value to be stored in the new node.
 * Return: A pointer to the newly added node.
 */
listS *shellAddNodeEnd(listS **head, const char *str, int num)
{
	listS *new_nde, *nde;

	if (!head)
		return (NULL);

	nde = *head;
	new_nde = malloc(sizeof(listS));
	if (!new_nde)
		return (NULL);
	shell__memset((void *)new_nde, 0, sizeof(listS));
	new_nde->num = num;
	if (str)
	{
		new_nde->str = shell_strdup(str);
		if (!new_nde->str)
		{
			free(new_nde);
			return (NULL);
		}
	}
	if (nde)
	{
		while (nde->next)
			nde = nde->next;
		nde->next = new_nde;
	}
	else
		*head = new_nde;
	return (new_nde);
}

/**
 * shellFreeList - Frees the memory occupied by a linked list.
 *
 * @head_ptr: A pointer to the head of the linked list.
 */
void shellFreeList(listS **head_ptr)
{
	listS *nde, *next_nde, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	nde = head;
	while (nde)
	{
		next_nde = nde->next;
		free(nde->str);
		free(nde);
		nde = next_nde;
	}
	*head_ptr = NULL;
}

/**
 * shellPrintListStr - Prints the strings stored in a linked list.
 *
 * @h: A pointer to the head of the linked list.
 * Return: The number of nodes in the linked list.
 */
size_t shellPrintListStr(const listS *h)
{
	size_t it = 0;

	while (h)
	{
		shell_puts(h->str ? h->str : "(nil)");
		shell_puts("\n");
		h = h->next;
		it++;
	}
	return (it);
}

/**
 * shellDelNodeAtIndex - Deletes a node at a specific index in a linked list.
 *
 * @head: A pointer to the head of the linked list.
 * @index: The index of the node to be deleted.
 * Return: 1 if the node is successfully deleted, 0 otherwise.
 */
int shellDelNodeAtIndex(listS **head, unsigned int index)
{
	listS *nde, *prev_nde;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nde = *head;
		*head = (*head)->next;
		free(nde->str);
		free(nde);
		return (1);
	}
	nde = *head;
	while (nde)
	{
		if (i == index)
		{
			prev_nde->next = nde->next;
			free(nde->str);
			free(nde);
			return (1);
		}
		i++;
		prev_nde = nde;
		nde = nde->next;
	}
	return (0);
}

/**
 * hellAddNode - Adds a new node at the beginning of a linked list.
 *
 * @head: A pointer to the head of the linked list.
 * @str: The string to be stored in the new node.
 * @num: An integer value to be stored in the new node.
 * Return: A pointer to the newly added node.
 */
listS *hellAddNode(listS **head, const char *str, int num)
{
	listS *new_hd;

	if (!head)
		return (NULL);
	new_hd = malloc(sizeof(listS));
	if (!new_hd)
		return (NULL);
	shell__memset((void *)new_hd, 0, sizeof(listS));
	new_hd->num = num;
	if (str)
	{
		new_hd->str = shell_strdup(str);
		if (!new_hd->str)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->next = *head;
	*head = new_hd;
	return (new_hd);
}
