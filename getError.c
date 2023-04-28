#include "headers.h"

/**
 * get_error - calls the error according the builtin, syntax or permission
 * @datash: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int get_error(sh_data *datash, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = errmsg_env(datash);
		break;
	case 126:
		error = errmsg_path_denied(datash);
		break;
	case 127:
		error = errmsg_notFound(datash);
		break;
	case 2:
		if (_StirCmpr("exit", datash->args[0]) == 0)
			error = errmsg_exit_sh(datash);
		else if (_StirCmpr("cd", datash->args[0]) == 0)
			error = errmsg_get_cd(datash);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _striLength(error));
		free(error);
	}

	datash->status = eval;
	return (eval);
}
