#include "shell.h"

/**
 * shellAddNodeEnd - adds a node to end
 * @head: address
 * @str: str
 * @num: node index
 *
 * Return: size of list
 */
list_t *shellAddNodeEnd(list_t **head, const char *str, int num)
{
	list_t *new_nde, *nde;

	if (!head)
		return (NULL);

	nde = *head;
	new_nde = malloc(sizeof(list_t));
	if (!new_nde)
		return (NULL);
	shell__memset((void *)new_nde, 0, sizeof(list_t));
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
 * shellFreeList - frees list
 * @head_ptr: address
 *
 * Return: void
 */
void shellFreeList(list_t **head_ptr)
{
	list_t *nde, *next_nde, *head;

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
 * shellPrintListStr - prints str element
 * @h: pointer
 *
 * Return: size
 */
size_t shellPrintListStr(const list_t *h)
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
 * shellDelNodeAtIndex - deletes node
 * @head: address
 * @index: index of node
 *
 * Return: success or failure
 */
int shellDelNodeAtIndex(list_t **head, unsigned int index)
{
	list_t *nde, *prev_nde;
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
 * hellAddNode - adds a node
 * @head: address
 * @str: str field
 * @num: node index
 *
 * Return: size
 */
list_t *hellAddNode(list_t **head, const char *str, int num)
{
	list_t *new_hd;

	if (!head)
		return (NULL);
	new_hd= malloc(sizeof(list_t));
	if (!new_hd)
		return (NULL);
	shell__memset((void *)new_hd, 0, sizeof(list_t));
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
