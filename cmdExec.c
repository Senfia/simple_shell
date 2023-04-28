#include "headers.h"

/**
 * _isCdir - checks ":" if is in the current directory.
 * @path: pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int _isCdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _whichCmd - locates a command
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *_whichCmd(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _get_env_var("PATH", _environ);
	if (path)
	{
		ptr_path = _striDup(path);
		len_cmd = _striLength(cmd);
		token_path = _strtok(ptr_path, ":");
		for (i = 0; token_path != NULL; i++, token_path = _strtok(NULL, ":"))
		{
			if (_isCdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _striLength(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_StirCpy(dir, token_path);
			_StriCat(dir, "/");
			_StriCat(dir, cmd);
			_StriCat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}


/**
 * _excutble - determines an executable
 * @datash: data
 * Return: 0 if is not an executable, other number if it does
 */
int _excutble(sh_data *datash)
{
	struct stat st;
	int i;
	char *input;

	input = datash->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	get_error(datash, 127);
	return (-1);
}

/**
 * _chk_err_cmd - verifies user has permissions to access
 * @dir: dest directory
 * @datash: data
 * Return: 1 if there is an error, 0 if not
 */
int _chk_err_cmd(char *dir, sh_data *datash)
{
	if (dir == NULL)
	{
		get_error(datash, 127);
		return (1);
	}

	if (_StirCmpr(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * _exec_cmd - executes command lines
 * @datash: relevant data
 * Return: 1 on success.
 */
int _exec_cmd(sh_data *datash)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = _excutble(datash);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _whichCmd(datash->args[0], datash->_environ);
		if (_chk_err_cmd(dir, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _whichCmd(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];
		execve(dir + exec, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash->status = state / 256;
	return (1);
}
