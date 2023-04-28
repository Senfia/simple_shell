#include "headers.h"

/**
 * errmsg_env - error message for env in get_env.
 * @datash: relevant data
 * Return: error msg.
 */
char *errmsg_env(sh_data *datash)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = sfj_itoa(datash->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _striLength(datash->av[0]) + _striLength(ver_str);
	length += _striLength(datash->args[0]) + _striLength(msg) + 4;
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
	_StriCat(error, msg);
	_StriCat(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * errmsg_path_denied - error message for path and failure denied permission.
 * @datash: relevant data
 * Return: The error string.
 */
char *errmsg_path_denied(sh_data *datash)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = sfj_itoa(datash->counter);
	length = _striLength(datash->av[0]) + _striLength(ver_str);
	length += _striLength(datash->args[0]) + 24;
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
	_StriCat(error, ": Permission denied\n");
	_StriCat(error, "\0");
	free(ver_str);
	return (error);
}
