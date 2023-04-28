#include "headers.h"

/**
 * cd_Dot - changes to the parent directory
 * @datash: data relevant (environ)
 * Return: no return
 */
void cd_Dot(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _striDup(pwd);
	_setEnv("OLDPWD", cp_pwd, datash);
	dir = datash->args[1];
	if (_StirCmpr(".", dir) == 0)
	{
		_setEnv("PWD", cp_pwd, datash);
		free(cp_pwd);
		return;
	}
	if (_StirCmpr("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	_rvString(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			_rvString(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		_setEnv("PWD", cp_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		_setEnv("PWD", "/", datash);
	}
	datash->status = 0;
	free(cp_pwd);
}

/**
 * cd_Tot - changes to a directory given
 * by the user
 * @datash: data relevant (directories)
 * Return: no return
 */
void cd_Tot(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = datash->args[1];
	if (chdir(dir) == -1)
	{
		get_error(datash, 2);
		return;
	}

	cp_pwd = _striDup(pwd);
	_setEnv("OLDPWD", cp_pwd, datash);

	cp_dir = _striDup(dir);
	_setEnv("PWD", cp_dir, datash);

	free(cp_pwd);
	free(cp_dir);

	datash->status = 0;

	chdir(dir);
}

/**
 * cd_prev - changes to the previous directory
 * @datash: data relevant (environ)
 * Return: no return
 */
void cd_prev(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _striDup(pwd);

	p_oldpwd = _get_env_var("OLDPWD", datash->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _striDup(p_oldpwd);

	_setEnv("OLDPWD", cp_pwd, datash);

	if (chdir(cp_oldpwd) == -1)
		_setEnv("PWD", cp_pwd, datash);
	else
		_setEnv("PWD", cp_oldpwd, datash);

	p_pwd = _get_env_var("PWD", datash->_environ);

	write(STDOUT_FILENO, p_pwd, _striLength(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datash->status = 0;

	chdir(p_pwd);
}

/**
 * cd_To_Home - changes to home directory
 * @datash: data relevant (environ)
 * Return: no return
 */
void cd_To_Home(data_shell *datash)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _striDup(pwd);

	home = _get_env_var("HOME", datash->_environ);

	if (home == NULL)
	{
		_setEnv("OLDPWD", p_pwd, datash);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datash, 2);
		free(p_pwd);
		return;
	}

	_setEnv("OLDPWD", p_pwd, datash);
	_setEnv("PWD", home, datash);
	free(p_pwd);
	datash->status = 0;
}
