#include "headers.h"

/**
 * addSepTo_node - adds a separator found at the end
 * of a sperat_list.
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
sperat_list *addSepTo_node(sperat_list **head, char sep)
{
	sperat_list *new, *temp;

	new = malloc(sizeof(sperat_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * freeSepTo_node - frees a sperat_list
 * @head: head of the linked list.
 * Return: no return.
 */
void freeSepTo_node(sperat_list **head)
{
	sperat_list *temp;
	sperat_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * addLinTo_node - adds a command line at the end
 * of a lin_list_ss.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
lin_list_ss *addLinTo_node(lin_list_ss **head, char *line)
{
	lin_list_ss *new, *temp;

	new = malloc(sizeof(lin_list_ss));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * freeLinTo_node - frees a lin_list_ss
 * @head: head of the linked list.
 * Return: no return.
 */
void freeLinTo_node(lin_list_ss **head)
{
	lin_list_ss *temp;
	lin_list_ss *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
