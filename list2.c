#include "headers.h"

/**
 * addVarTonode - adds a variable at the end
 * @head:  linked list head.
 * @lvar: variable length.
 * @val: variable value.
 * @lval:  value length.
 * Return: address head.
 */
r_var *addVarTonode(r_var **head, int lvar, char *val, int lval)
{
	r_var *new, *temp;

	new = malloc(sizeof(r_var));
	if (new == NULL)
		return (NULL);

	new->len_var = lvar;
	new->val = val;
	new->len_val = lval;

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
 * freeVarLi - frees a r_var list
 * @head: linked list head.
 * Return: nothing.
 */
void freeVarLi(r_var **head)
{
	r_var *temp;
	r_var *curr;

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
