#include "headers.h"

/**
 * get_help - function that retrieves help messages according builtin
 * @datash: data structure (args and input)
 * Return: Return 0
*/
int get_help(data_shell *datash)
{

	if (datash->args[1] == 0)
		sfj_hlp_gen();
	else if (_StirCmpr(datash->args[1], "setenv") == 0)
		sfj_hlp_setenv();
	else if (_StirCmpr(datash->args[1], "env") == 0)
		sfj_hlp_env();
	else if (_StirCmpr(datash->args[1], "unsetenv") == 0)
		sfj_hlp_unsetenv();
	else if (_StirCmpr(datash->args[1], "help") == 0)
		sfj_hlp();
	else if (_StirCmpr(datash->args[1], "exit") == 0)
		sfj_hlp_exit();
	else if (_StirCmpr(datash->args[1], "cd") == 0)
		sfj_hlp_cd();
	else if (_StirCmpr(datash->args[1], "alias") == 0)
		sfj_hlp_alias();
	else
		write(STDERR_FILENO, datash->args[0],
		      _striLength(datash->args[0]));

	datash->status = 0;
	return (1);
}
