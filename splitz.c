#include "headers.h"

/**
 * swpChar - swaps | and & for non-printed chars
 *
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *swpChar(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * addNode_s - add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @input: input string
 * Return: no return
 */
void addNode_s(sperat_list **head_s, lin_list_ss **head_l, char *input)
{
	int i;
	char *line;

	input = swpChar(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			addSepTo_node(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			addSepTo_node(head_s, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swpChar(line, 1);
		addLinTo_node(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * goToNext - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @datash: data structure
 * Return: no return
 */
void goToNext(sperat_list **list_s, lin_list_ss **list_l, sh_data *datash)
{
	int loop_sep = 1;
	sperat_list *ls_s = *list_s;
	lin_list_ss *ls_l = *list_l;

	for (; ls_s != NULL && loop_sep; ls_s = ls_s->next)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		} else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * slice_cmds - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @datash: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int slice_cmds(sh_data *datash, char *input)
{

	sperat_list *head_s, *list_s;
	lin_list_ss *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	addNode_s(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = slice_Line(datash->input);
		loop = exec_line(datash);
		free(datash->args);

		if (loop == 0)
			break;

		goToNext(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	freeSepTo_node(&head_s);
	freeLinTo_node(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * slice_Line - tokenizes the input string
 *
 * @input: input string.
 * Return: string splitted.
 */
char **slice_Line(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOKN_BUFFSIZ;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOKN_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOKN_BUFFSIZ;
			tokens = _reallocmemdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOKN_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
