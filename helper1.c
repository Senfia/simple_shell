#include "headers.h"

/**
 * sfj_hlp_env - Helps information for the builtin env
 * Return: nothing
 */
void sfj_hlp_env(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, _striLength(help));
	help = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, help, _striLength(help));

}
/**
 * sfj_hlp_setenv - Helps information for the builtin setenv
 * Return: nothing
 */
void sfj_hlp_setenv(void)
{

	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, _striLength(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, _striLength(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, _striLength(help));
}
/**
 * sfj_hlp_unsetenv - Help information for the builtin unsetenv
 * Return: nothing
 */
void sfj_hlp_unsetenv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, _striLength(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, _striLength(help));
}


/**
 * sfj_hlp_gen - Entry point.
 * Return: nothing
 */
void sfj_hlp_gen(void)
{
	char *help = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, _striLength(help));
	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, _striLength(help));
	help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, _striLength(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, _striLength(help));
	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, _striLength(help));
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, _striLength(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, _striLength(help));
}
/**
 * sfj_hlp_exit - information fot the builint exit
 * Return: nothing
 */
void sfj_hlp_exit(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, _striLength(help));
	help = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, _striLength(help));
	help = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, help, _striLength(help));
}
