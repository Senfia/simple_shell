#include "headers.h"

/**
 * free_data - frees
 * @datash: data
 * Return: nothing
 */
void free_data(sh_data *datash)
{
	unsigned int i;

	for (i = 0; datash->_environ[i]; i++)
	{
		free(datash->_environ[i]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_data - Initialize data structure
 * @datash: data
 * @av: argument
 * Return: nothing
 */
void set_data(sh_data *datash, char **av)
{
	unsigned int i;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	datash->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		datash->_environ[i] = _striDup(environ[i]);
	}

	datash->_environ[i] = NULL;
	datash->pid = sfj_itoa(getpid());
}

/**
 * main - Entry point
 * @ac: arg count
 * @av: arg vector
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	sh_data datash;
	(void) ac;

	signal(SIGINT, _get_signal);
	set_data(&datash, av);
	shllLoop(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
