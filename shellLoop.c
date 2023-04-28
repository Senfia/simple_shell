#include "headers.h"

/**
 * rm_comments - deletes comments from the input
 * @in: string input
 * Return: input
 */
char *rm_comments(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = _reallcmem(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shllLoop - Loop of shell
 * @datash: relevant data
 * Return: nothing.
 */
void shllLoop(sh_data *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = readLine(&i_eof);
		if (i_eof != -1)
		{
			input = rm_comments(input);
			if (input == NULL)
				continue;

			if (check_Synx_err(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rplce_var(input, datash);
			loop = slice_cmds(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
