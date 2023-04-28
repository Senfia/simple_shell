#include "headers.h"

/**
 * _reaptChar - counts the repetitions of a char
 * @input: input string
 * @i: index
 * Return: repetitions
 */
int _reaptChar(char *input, int i)
{
	if (*(input - 1) == *input)
		return (_reaptChar(input - 1, i + 1));

	return (i);
}

/**
 * err_find_synx - finds syntax errors
 * @input: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int err_find_synx(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (err_find_synx(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = _reaptChar(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = _reaptChar(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (err_find_synx(input + 1, i + 1, *input));
}

/**
 * index_Char - finds index of the first char
 * @input: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int index_Char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * printSynx_err - prints when a syntax error is found
 * @datash: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void printSynx_err(data_shell *datash, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = sfj_itoa(datash->counter);
	length = _striLength(datash->av[0]) + _striLength(counter);
	length += _striLength(msg) + _striLength(msg2) + _striLength(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_StirCpy(error, datash->av[0]);
	_StriCat(error, ": ");
	_StriCat(error, counter);
	_StriCat(error, msg2);
	_StriCat(error, msg);
	_StriCat(error, msg3);
	_StriCat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * check_Synx_err - intermediate function to
 * find and print a syntax error
 * @datash: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_Synx_err(data_shell *datash, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = index_Char(input, &begin);
	if (f_char == -1)
	{
		printSynx_err(datash, input, begin, 0);
		return (1);
	}

	i = err_find_synx(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		printSynx_err(datash, input, begin + i, 1);
		return (1);
	}

	return (0);
}
