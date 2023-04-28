#include "headers.h"

/**
 * cpy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 * Return: new env or alias.
 */
char *cpy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _striLength(name);
	len_value = _striLength(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_StirCpy(new, name);
	_StriCat(new, "=");
	_StriCat(new, value);
	_StriCat(new, "\0");

	return (new);
}

/**
 * _setEnv - sets an environment variable
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: no return
 */
void _setEnv(char *name, char *value, sh_data *datash)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; datash->_environ[i]; i++)
	{
		var_env = _striDup(datash->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_StirCmpr(name_env, name) == 0)
		{
			free(datash->_environ[i]);
			datash->_environ[i] = cpy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_environ =
	_reallocmemdp(datash->_environ, i, sizeof(char *) * (i + 2));
	datash->_environ[i] = cpy_info(name, value);
	datash->_environ[i + 1] = NULL;
}

/**
 * _setEnvi - compares env variables names
 * with the name passed.
 * @datash: data relevant (env name and env value)
 * Return: 1 on success.
 */
int _setEnvi(sh_data *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	_setEnv(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetEnvi - deletes a environment variable
 * @datash: data relevant (env name)
 * Return: 1 on success.
 */
int _unsetEnvi(sh_data *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datash->_environ[i]; i++)
	{
		var_env = _striDup(datash->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_StirCmpr(name_env, datash->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; datash->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = datash->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
