#include "headers.h"

/**
 * cmp_env_name - compares env variables names.
 * @nenv: name of the environment variable
 * @name: name passed
 * Return: 0 if not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i = 0;

	while (nenv[i] != '=')
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
		i++;
	}

	return (i + 1);
}

/**
 * _get_env_var - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 * Return: environment variable value if found. returns NULL if not found.
 */
char *_get_env_var(const char *name, char **_environ)
{
	char *ptr_env = NULL;
	int i = 0, mov = 0;

	while (_environ[i])
	{
		mov = cmp_env_name(_environ[i], name);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
		i++;
	}

	return (ptr_env + mov);
}


/**
 * _Env_ - prints the evironment variables
 * @datash: relevant data.
 * Return: 1 on success.
 */
int _Env_(sh_data *datash)
{
	int i, j;

	for (i = 0; datash->_environ[i]; i++)
	{

		for (j = 0; datash->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
