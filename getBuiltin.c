#include "headers.h"

/**
 * get_builtin - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _Env_ },
		{ "exit", exit_Sh },
		{ "setenv", _setEnvi },
		{ "unsetenv", _unsetEnvi },
		{ "cd", cd_Main },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_StirCmpr(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}