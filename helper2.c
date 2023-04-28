#include "headers.h"

/**
 * sfj_hlp - Help information for the builtin help.
 * Return: no return
 */
void sfj_hlp(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _striLength(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, _striLength(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _striLength(help));
}
/**
 * sfj_hlp_alias - Help information for the builtin alias.
 * Return: no return
 */
void sfj_hlp_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _striLength(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _striLength(help));
}
/**
 * sfj_hlp_cd - Help information for the builtin alias.
 * Return: no return
 */
void sfj_hlp_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _striLength(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _striLength(help));
}
