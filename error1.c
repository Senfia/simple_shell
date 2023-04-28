#include "headers.h"

/**
 * errmsg_strcat - function that concatenates the message for cd error
 * @datash: data relevant (directory)
 * @msg: message to print
 * @error: output message
 * @ver_str: counter lines
 * Return: error message
 */
char *errmsg_strcat(sh_data *datash, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	_StirCpy(error, datash->av[0]);
	_StriCat(error, ": ");
	_StriCat(error, ver_str);
	_StriCat(error, ": ");
	_StriCat(error, datash->args[0]);
	_StriCat(error, msg);
	if (datash->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datash->args[1][1];
		illegal_flag[2] = '\0';
		_StriCat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_StriCat(error, datash->args[1]);
	}

	_StriCat(error, "\n");
	_StriCat(error, "\0");
	return (error);
}

/**
 * errmsg_get_cd - error message for cd command in get_cd
 * @datash: data relevant (directory)
 * Return: Error message
 */
char *errmsg_get_cd(sh_data *datash)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = sfj_itoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _striLength(datash->args[1]);
	}

	length = _striLength(datash->av[0]) + _striLength(datash->args[0]);
	length += _striLength(ver_str) + _striLength(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = errmsg_strcat(datash, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * errmsg_notFound - generic error message for command not found
 * @datash: data relevant (counter, arguments)
 * Return: Error message
 */
char *errmsg_notFound(sh_data *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = sfj_itoa(datash->counter);
	length = _striLength(datash->av[0]) + _striLength(ver_str);
	length += _striLength(datash->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_StirCpy(error, datash->av[0]);
	_StriCat(error, ": ");
	_StriCat(error, ver_str);
	_StriCat(error, ": ");
	_StriCat(error, datash->args[0]);
	_StriCat(error, ": not found\n");
	_StriCat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * errmsg_exit_sh - generic error message for exit in get_exit
 * @datash: data relevant (counter, arguments)
 * Return: Error message
 */
char *errmsg_exit_sh(sh_data *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = sfj_itoa(datash->counter);
	length = _striLength(datash->av[0]) + _striLength(ver_str);
	length += _striLength(datash->args[0]) + _striLength(datash->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_StirCpy(error, datash->av[0]);
	_StriCat(error, ": ");
	_StriCat(error, ver_str);
	_StriCat(error, ": ");
	_StriCat(error, datash->args[0]);
	_StriCat(error, ": Illegal number: ");
	_StriCat(error, datash->args[1]);
	_StriCat(error, "\n\0");
	free(ver_str);

	return (error);
}
