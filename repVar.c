#include "headers.h"

/**
 * checkEnv_ - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: input string
 * @data: data structure
 * Return: no return
 */
void checkEnv_(r_var **h, char *in, sh_data *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _striLength(_envr[row] + chr + 1);
				addVarTonode(h, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	addVarTonode(h, j, NULL, 0);
}

/**
 * check_vars - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int check_vars(r_var **h, char *in, char *st, sh_data *data)
{
	int i, lst, lpd;

	lst = _striLength(st);
	lpd = _striLength(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				addVarTonode(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				addVarTonode(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				addVarTonode(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				addVarTonode(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				addVarTonode(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				addVarTonode(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				addVarTonode(h, 0, NULL, 0);
			else
				checkEnv_(h, in + i, data);
		}
	}

	return (i);
}

/**
 * rplce_input - replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *rplce_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int i = 0, j = 0, k;

	indx = *head;
	while (i < nlen)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
		i++;
	}

	return (new_input);
}

/**
 * rplce_var - calls functions to replace string into vars
 * @input: string input
 * @datash: data
 * Return: string replacement
 */
char *rplce_var(char *input, sh_data *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = sfj_itoa(datash->status);
	head = NULL;

	olen = check_vars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = rplce_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	freeVarLi(&head);

	return (new_input);
}
