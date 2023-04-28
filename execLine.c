#include "headers.h"

/**
 * exec_line - finds builtins and commands
 * @datash: relevant data
 * Return: 1 on success.
 */
int exec_line(sh_data *datash)
{
	int (*builtin)(sh_data *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = get_builtin(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (_exec_cmd(datash));
}
